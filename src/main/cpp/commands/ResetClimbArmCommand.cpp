/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ResetClimbArmCommand.h"
#include "Robot.h"

ResetClimbArmCommand::ResetClimbArmCommand()
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_climbSubsystem);
}

// Called just before this Command runs the first time
void ResetClimbArmCommand::Initialize() 
{
  Robot::m_climbSubsystem.SetArmCurrentLimitLow();
  Robot::m_climbSubsystem.SetArmPercentOutputLow();
}

// Called repeatedly when this Command is scheduled to run
void ResetClimbArmCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ResetClimbArmCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void ResetClimbArmCommand::End() 
{
  Robot::m_climbSubsystem.StopAndZero();
  Robot::m_climbSubsystem.SetArmCurrentLimitHigh();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetClimbArmCommand::Interrupted()
{
  End();
}
