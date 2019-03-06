/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ShuttleTargetCommand.h"
#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

ShuttleTargetCommand::ShuttleTargetCommand(bool front) {
  m_bFront = front;
}

// Called just before this Command runs the first time
void ShuttleTargetCommand::Initialize()
{
  // set the target shuttle direction based on input variable
  Robot::m_oi.m_shuttleTargetFront = m_bFront;
  frc::SmartDashboard::PutBoolean("ShuttleForward", m_bFront);
}

// Called repeatedly when this Command is scheduled to run
void ShuttleTargetCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ShuttleTargetCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ShuttleTargetCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShuttleTargetCommand::Interrupted() {}
