/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PowerToClimbWheelsCommand.h"
#include "Robot.h"

PowerToClimbWheelsCommand::PowerToClimbWheelsCommand() {
    Requires(&Robot::m_climbSubsystem);
}

// Called just before this Command runs the first time
void PowerToClimbWheelsCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PowerToClimbWheelsCommand::Execute() {
    Robot::m_climbSubsystem.PowerToClimbWheels();
}

// Make this return true when this Command no longer needs to run execute()
bool PowerToClimbWheelsCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void PowerToClimbWheelsCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PowerToClimbWheelsCommand::Interrupted() {}
