/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ReconfigureLiftForClimbCommand.h"
#include "Robot.h"

ReconfigureLiftForClimbCommand::ReconfigureLiftForClimbCommand() {
  Requires(&Robot::m_liftAndShuttleSubsystem);
}

// Called just before this Command runs the first time
void ReconfigureLiftForClimbCommand::Initialize()
{
  Robot::m_liftAndShuttleSubsystem.ReconfigureLiftForClimb();
}

// Called repeatedly when this Command is scheduled to run
void ReconfigureLiftForClimbCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ReconfigureLiftForClimbCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ReconfigureLiftForClimbCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReconfigureLiftForClimbCommand::Interrupted() {}
