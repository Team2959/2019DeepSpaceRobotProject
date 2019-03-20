/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ResetCargoArmCommand.h"
#include "Robot.h"

ResetCargoArmCommand::ResetCargoArmCommand() {
  Requires(&Robot::m_cargoArmSubsystem);
}

// Called just before this Command runs the first time
void ResetCargoArmCommand::Initialize() {
  Robot::m_cargoArmSubsystem.SetArmCurrentLimitLow();
  Robot::m_cargoArmSubsystem.SetArmPercentOutputLow();
}

// Called repeatedly when this Command is scheduled to run
void ResetCargoArmCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ResetCargoArmCommand::IsFinished() {return false;}

// Called once after isFinished returns true
void ResetCargoArmCommand::End()
{
  Robot::m_cargoArmSubsystem.StopAndZero();
  Robot::m_cargoArmSubsystem.SetArmCurrentLimitHigh();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetCargoArmCommand::Interrupted()
{
  End();
}
