/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToVisionTargetCommand.h"
#include "../../include/Robot.h"
#include "../../../../../2019RaspPIRoboRioShared/Shared.hpp"

ToVisionTargetCommand::ToVisionTargetCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_driveTrainSubsystem);
}

// Called just before this Command runs the first time
void ToVisionTargetCommand::Initialize() 
{
    Robot::m_networkTable->PutNumber(Rpi2959Shared::Keys::FrontTargets, static_cast<double>(Rpi2959Shared::ProcessingTargets::PortTape)); 
    m_isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void ToVisionTargetCommand::Execute()
{
  // If we have already marked as finished, do nothing
  if( m_isFinished )
    return;
  auto Results = Robot::m_networkTable->GetNumberArray(Rpi2959Shared::Keys::FrontPortTapeResults, std::vector<double>{});

  if(Results.size() == 0)
  {
    m_isFinished = true;
    return;
  }

  auto  LeftX = Results[0];   // in [0,1]
  auto  RightX = Results[1];
  auto Middle = (RightX + LeftX) / 2;
  auto result = ComputeRpms(Middle, RightX - LeftX);
  if((std::get<0>(result) == 0.0)&&(std::get<1>(result) == 0.0))
    m_isFinished = true;
  Robot::m_driveTrainSubsystem.TankDrive(std::get<0>(result),std::get<1>(result));
}

  std::tuple<double, double> ToVisionTargetCommand::ComputeRpms(double middle, double separation)
  {
    if(middle > 0.55)    // Turn right
    {
      auto  rotationSpeed = 2.0 * (middle - 0.5); // Need to change speed with testing
      return std::make_tuple(rotationSpeed,-rotationSpeed);
    }
    else if(middle < 0.45)  // Turn left
    {
      auto  rotationSpeed = 2.0 * (0.5 - middle); // Need to change speed with testing
      return std::make_tuple(-rotationSpeed,rotationSpeed);
    }
    else if(separation < 0.4) // Drive forward...0.4 should be fairly close to brushing up against the spacecraft
    {
      auto  rotationSpeed = (0.5 - separation) / 2.0; // Need to change speed with testing
      return std::make_tuple(rotationSpeed,rotationSpeed);
    }
    else
    {
      m_isFinished = true;
      return std::make_tuple(0,0);
    }
  }

// Make this return true when this Command no longer needs to run execute()
bool ToVisionTargetCommand::IsFinished() { return m_isFinished; }

// Called once after isFinished returns true
void ToVisionTargetCommand::End() 
{
   Robot::m_networkTable->PutNumber(Rpi2959Shared::Keys::FrontTargets, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToVisionTargetCommand::Interrupted() {}
