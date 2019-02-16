/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CargoShuttleStopAtFrontCommand.h"
#include "subsystems/LiftAndShuttleSubsystem.h"
#include "Robot.h"

CargoShuttleStopAtFrontCommand::CargoShuttleStopAtFrontCommand() {
  // Use Requires() here to declare subsystem dependencies
 Requires(&Robot::m_liftAndShuttleSubsytem);
}

// Called just before this Command runs the first time
void CargoShuttleStopAtFrontCommand::Initialize()
{
  Robot::m_liftAndShuttleSubsytem.CargoShuttleFrontStop();
}

// Called repeatedly when this Command is scheduled to run
void CargoShuttleStopAtFrontCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CargoShuttleStopAtFrontCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void CargoShuttleStopAtFrontCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CargoShuttleStopAtFrontCommand::Interrupted() {}
