/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveCargoTowardRearCommand.h"
#include "Robot.h"

MoveCargoTowardRearCommand::MoveCargoTowardRearCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_cargoControlSubsystem);
}

// Called just before this Command runs the first time
void MoveCargoTowardRearCommand::Initialize()
{
  Robot::m_cargoControlSubsystem.CargoBallTowardsRear();
}

// Called repeatedly when this Command is scheduled to run
void MoveCargoTowardRearCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool MoveCargoTowardRearCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void MoveCargoTowardRearCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveCargoTowardRearCommand::Interrupted() {}
