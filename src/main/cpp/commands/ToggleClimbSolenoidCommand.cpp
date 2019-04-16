/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleClimbSolenoidCommand.h"
#include "Robot.h"

ToggleClimbSolenoidCommand::ToggleClimbSolenoidCommand() {
  Requires(&Robot::m_climbSubsystem);
  m_bEngage = true;
}

// Called just before this Command runs the first time
void ToggleClimbSolenoidCommand::Initialize()
{
  if (m_bEngage)
  {
    Robot::m_climbSubsystem.ClimbSolenoidEngage();
  }
  else
  {
    Robot::m_climbSubsystem.ClimbSolenoidDisengage();
  }
  m_bEngage = !m_bEngage;
}

// Called repeatedly when this Command is scheduled to run
void ToggleClimbSolenoidCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ToggleClimbSolenoidCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ToggleClimbSolenoidCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleClimbSolenoidCommand::Interrupted() {}
