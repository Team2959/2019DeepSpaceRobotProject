/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LiftLimitSwitchBottomCommand.h"
#include "Robot.h"
#include "subsystems/LiftAndShuttleSubsystem.h"

LiftLimitSwitchBottomCommand::LiftLimitSwitchBottomCommand() {
  // Use Requires() here to declare subsystem dependencies
  Requires(&Robot::m_liftAndShuttleSubsystem);
}

// Called just before this Command runs the first time
void LiftLimitSwitchBottomCommand::Initialize() 
{
Robot::m_liftAndShuttleSubsystem.LiftBottomReset();
}

// Called repeatedly when this Command is scheduled to run
void LiftLimitSwitchBottomCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool LiftLimitSwitchBottomCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void LiftLimitSwitchBottomCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftLimitSwitchBottomCommand::Interrupted() {}
