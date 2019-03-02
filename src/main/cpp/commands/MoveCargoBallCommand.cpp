/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveCargoBallCommand.h"
#include "Robot.h"

MoveCargoBallCommand::MoveCargoBallCommand(bool bFront, bool bDeliver)
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_cargoControlSubsystem);

  m_bFront = bFront;
  m_bDeliver = bDeliver;
}

// Called just before this Command runs the first time
void MoveCargoBallCommand::Initialize()
{
  Robot::m_cargoControlSubsystem.MoveCargoBall(m_bFront, m_bDeliver);
}

// Called repeatedly when this Command is scheduled to run
void MoveCargoBallCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool MoveCargoBallCommand::IsFinished()
{
  return Robot::m_cargoControlSubsystem.CargoIn() == false;
}

// Called once after isFinished returns true
void MoveCargoBallCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveCargoBallCommand::Interrupted() {}
