/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveToPortTapeCommand.h"
#include "Robot.h"
#include "../../../../../2019RaspPIRoboRioShared/Shared.hpp"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

constexpr double kForward = 1500.0;
constexpr double kRotation = 300.0;
constexpr double kAccelDecel = 100.0;
constexpr double kSeparation = 0.3;
constexpr double kCenterRadius = 0.05;         // If the tape center is within this radius, we drive forward

// Constructor
DriveToPortTapeCommand::DriveToPortTapeCommand() :
 m_currentLeftSpeed{ 0.0 },
 m_currentRightSpeed{ 0.0 },
 m_maxForwardSpeed{ kForward },
 m_maxRotationSpeed{ kRotation },
 m_accelDecel{ kAccelDecel },
 m_separationLimit{ kSeparation },
 m_accelDecelRotation{ kAccelDecel / 2.0 }
{
  Requires(&Robot::m_driveTrainSubsystem);
}

// Called just before this Command runs the first time
void DriveToPortTapeCommand::Initialize() 
{
  m_networkTable = Robot::m_networkTable;

  if (frc::SmartDashboard::GetBoolean("Debug Drive", false))
  {
    m_maxForwardSpeed = frc::SmartDashboard::GetNumber("Auto Forward", kForward);
    m_maxRotationSpeed = frc::SmartDashboard::GetNumber("Auto Rotation", kRotation);
    m_accelDecel = frc::SmartDashboard::GetNumber("Accel", kAccelDecel);
    m_separationLimit = frc::SmartDashboard::GetNumber("Separation Limit", kSeparation);
    m_accelDecelRotation = m_accelDecel / 2.0;
  }
  m_currentLeftSpeed = 0.0;
  m_currentRightSpeed = 0.0;

  // Tell the Raspberry PI that we want it to look for port tape
  LookForTape(true);

  // Not done yet
  m_isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void DriveToPortTapeCommand::Execute()
{
  // If we have already marked as finished, do nothing
  if( m_isFinished )
    return;

  // Get results from the Raspberry PI
  auto  results{ m_networkTable->GetNumberArray(Rpi2959Shared::Keys::FrontPortTapeResults, std::vector<double>{}) };

  // If we don't have enough result values, then decelerate
  if(results.size() < 4)
  {
    if(m_currentLeftSpeed < 0.0)
      m_currentLeftSpeed = std::min(m_currentLeftSpeed + m_accelDecel, 0.0);
    else if(m_currentLeftSpeed > 0.0)
      m_currentLeftSpeed = std::max(m_currentLeftSpeed - m_accelDecel, 0.0);
    if(m_currentRightSpeed < 0.0)
      m_currentRightSpeed = std::min(m_currentRightSpeed + m_accelDecel, 0.0);
    else if(m_currentRightSpeed > 0.0)
      m_currentRightSpeed = std::max(m_currentRightSpeed - m_accelDecel, 0.0);

    // std::cout << "**** NO SOLUTION ***\n";
    // std::cout << "NewLeft = " << m_currentLeftSpeed << '\n';
    // std::cout << "NewRight = " << m_currentRightSpeed << '\n';

    Robot::m_driveTrainSubsystem.TankDrive(m_currentLeftSpeed, m_currentRightSpeed);
    return;             // Exit the function.  We are still looking for tape targets, so Execute may be called again
  }

  double  leftRPMs;     // Will hold the speeds for the two sides
  double  rightRPMs;

  // Compute the RPMs to use, passing in the left tape X and right tape X centers
  std::tie(leftRPMs, rightRPMs) = ComputeRpms(results[0], results[2]);

  // std::cout << "NewLeft = " << leftRPMs << '\n';
  // std::cout << "NewRight = " << rightRPMs << '\n';

  // If RPMs for both left and right are zero, then we have reached target and have nothing more to do
  m_isFinished = (leftRPMs == 0.0)&&(rightRPMs == 0.0);

  // if(m_isFinished)
  //   std::cout << "!!! Marked Done !!!\n";
  // Send the RPMs to the hardware
  Robot::m_driveTrainSubsystem.TankDrive(leftRPMs, rightRPMs);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveToPortTapeCommand::IsFinished() 
{
  // std::cout << "IsFinished = " << m_isFinished << '\n';
   return m_isFinished; 
}

// Called once after isFinished returns true
void DriveToPortTapeCommand::End()
{
  // std::cout << "End\n";
  StopDriveMotion();  // Ensure that the drive is stopped
  LookForTape(false); // Tell the Raspberry PI that we don't want it to look for port tape
}

// Called when another command which requires one or more of the same subsystems is scheduled to run
void DriveToPortTapeCommand::Interrupted()
{
  End();
}

// Stop all drive motion
void DriveToPortTapeCommand::StopDriveMotion() { Robot::m_driveTrainSubsystem.TankDrive(0.0, 0.0); }

// Given left/right tape X positions, compute the RPMs to use
std::tuple<double, double> DriveToPortTapeCommand::ComputeRpms(double leftTapeX, double rightTapeX)
{
  auto  middleX{ (rightTapeX + leftTapeX) / 2 };  // Compute the mid point between left X and right X
  auto  separationX{ rightTapeX - leftTapeX };    // Compute the separation between left X and right X

  // std::cout << "MiddleX = " << middleX << '\n';
  // std::cout << "SeparationX = " << separationX << '\n';

  auto rotation = m_maxRotationSpeed;
  if (separationX < m_separationLimit - 0.05)
  {
    rotation *= 0.6;
  }

  // If the tape middle is on the right side of the frame, then we need to turn to the right
  if(middleX > (0.5 + kCenterRadius))
  {
    m_currentLeftSpeed = std::min(m_currentLeftSpeed + m_accelDecelRotation, rotation);
    m_currentRightSpeed = std::max(m_currentRightSpeed - m_accelDecelRotation, -rotation);

    return std::make_tuple(m_currentLeftSpeed, m_currentRightSpeed);          // Return the result
  }

  // If the tape middle is on the left side of the frame, then we need to turn to the left
  if(middleX < (0.5 - kCenterRadius))
  {
    m_currentLeftSpeed = std::max(m_currentLeftSpeed - m_accelDecelRotation, -rotation);
    m_currentRightSpeed = std::min(m_currentRightSpeed + m_accelDecelRotation, rotation);

    return std::make_tuple(m_currentLeftSpeed, m_currentRightSpeed);          // Return the result
  }

  // std::cout << "SeparationX = " << separationX << '\n';

  // If the tapes are separated by less than this, we must drive forward
  if(separationX < m_separationLimit)
  {
    auto  newSpeed{std::min(std::max((m_currentLeftSpeed + m_currentRightSpeed) / 2.0 + m_accelDecel, 0.0), m_maxForwardSpeed) };
    m_currentLeftSpeed = newSpeed;
    m_currentRightSpeed = newSpeed;

    return std::make_tuple(m_currentLeftSpeed, m_currentRightSpeed);   // Return the result
  }

  m_currentLeftSpeed = 0.0;
  m_currentRightSpeed = 0.0;

  // Otherwise, the tape center is in the middle of frame, and the tape Xs are far enough apart...we are done
  return std::make_tuple(0.0, 0.0);
}

void DriveToPortTapeCommand::LookForTape(bool flag)
{
  // If flag is set, Tell the Raspberry PI that we want it to look for port tape.  Otherwise, clear the flag on the Raspberry PI
  m_networkTable->PutNumber(Rpi2959Shared::Keys::FrontTargets,
    flag ? static_cast<double>(Rpi2959Shared::ProcessingTargets::PortTape) : 0.0);
}
