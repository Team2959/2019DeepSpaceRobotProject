/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveToPortTapeCommand.h"
#include "../../include/Robot.h"
#include "../../../../../2019RaspPIRoboRioShared/Shared.hpp"

// Constructor
DriveToPortTapeCommand::DriveToPortTapeCommand() : m_networkTable{ Robot::m_networkTable },
  m_driveTrainSubsystem{ Robot::m_driveTrainSubsystem }
{
  Requires(&m_driveTrainSubsystem);
}

// Called just before this Command runs the first time
void DriveToPortTapeCommand::Initialize() 
{
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

  // If we don't have enough result values, then we have nothing to drive to.
  if(results.size() < 4)
  {
    StopDriveMotion();  // Make sure that we aren't moving
    return;             // Exit the function.  We are still looking for tape targets, so Execute may be called again
  }

  double  leftRPMs;     // Will hold the speeds for the two sides
  double  rightRPMs;

  // Compute the RPMs to use, passing in the left tape X and right tape X centers
  std::tie(leftRPMs, rightRPMs) = ComputeRpms(results[0], results[2]);

  // If RPMs for both left and right are zero, then we have reached target and have nothing more to do
  m_isFinished = (leftRPMs == 0.0)&&(rightRPMs == 0.0);

  // Send the RPMs to the hardware
  m_driveTrainSubsystem.TankDrive(leftRPMs, rightRPMs);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveToPortTapeCommand::IsFinished() { return m_isFinished; }

// Called once after isFinished returns true
void DriveToPortTapeCommand::End()
{
  StopDriveMotion();  // Ensure that the drive is stopped
  LookForTape(false); // Tell the Raspberry PI that we don't want it to look for port tape
}

// Called when another command which requires one or more of the same subsystems is scheduled to run
void DriveToPortTapeCommand::Interrupted()
{
  End();
}

// Stop all drive motion
void DriveToPortTapeCommand::StopDriveMotion() { m_driveTrainSubsystem.TankDrive(0.0, 0.0); }

// Given left/right tape X positions, compute the RPMs to use
std::tuple<double, double> DriveToPortTapeCommand::ComputeRpms(double leftTapeX, double rightTapeX)
{
  const double  StandardRotationSpeed{ 4.0 }; // This is a common speed factor.  ADJUST THIS WITH TESTING.
  const double  FullForwardSpeed{ 4.0 };      // The speed to drive when we are far from the tape.  ADJUST THIS WITH TESTING
  const double  CenterRadius{ 0.05 };         // If the tape center is within this radius, we drive forward
  const double  SeparationLimit{ 0.35 };      // If the two tape X centers are separated by more than this value, then we are close enough

  auto  middleX{ (rightTapeX + leftTapeX) / 2 };  // Compute the mid point between left X and right X
  auto  separationX{ rightTapeX - leftTapeX };    // Compute the separation between left X and right X

  // If the tape middle is on the right side of the frame, then we need to turn to the right
  if(middleX > (0.5 + CenterRadius))
  {
    auto  rotationSpeed{ StandardRotationSpeed * (middleX - 0.5) }; // Compute our rotation speed
    return std::make_tuple(rotationSpeed, -rotationSpeed);          // Return the result
  }

  // If the tape middle is on the left side of the frame, then we need to turn to the left
  if(middleX < (0.5 - CenterRadius))
  {
    auto  rotationSpeed{ StandardRotationSpeed * (0.5 - middleX) }; // Compute our rotation speed
    return std::make_tuple(-rotationSpeed, rotationSpeed);          // Return the result
  }

  // If the tapes are separated by less than this, we must drive forward
  if(separationX < SeparationLimit)
  {
    auto  driveSpeed{ FullForwardSpeed * (SeparationLimit - separationX) / SeparationLimit }; // Compute our drive speed
    return std::make_tuple(driveSpeed, driveSpeed);   // Return the result
  }

  // Otherwise, the tape center is in the middle of frame, and the tape Xs are far enough apart...we are done
  return std::make_tuple(0.0, 0.0);
}

void DriveToPortTapeCommand::LookForTape(bool flag)
{
  // If flag is set, Tell the Raspberry PI that we want it to look for port tape.  Otherwise, clear the flag on the Raspberry PI
  m_networkTable->PutNumber(Rpi2959Shared::Keys::FrontTargets,
    flag ? static_cast<double>(Rpi2959Shared::ProcessingTargets::PortTape) : 0.0);
}
