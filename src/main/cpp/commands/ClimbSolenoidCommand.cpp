/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbSolenoidCommand.h"
#include "Robot.h"

ClimbSolenoidCommand::ClimbSolenoidCommand(bool engage) {
  Requires(&Robot::m_climbSubsystem);
  m_bEngage = engage;
}

// Called just before this Command runs the first time
void ClimbSolenoidCommand::Initialize() {
  if (m_bEngage)
  {
    Robot::m_climbSubsystem.ClimbSolenoidEngage();
  }
  else
  {
    Robot::m_climbSubsystem.ClimbSolenoidDisengage();
  }
}

// Called repeatedly when this Command is scheduled to run
void ClimbSolenoidCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ClimbSolenoidCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ClimbSolenoidCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbSolenoidCommand::Interrupted() {}
