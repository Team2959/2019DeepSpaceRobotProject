/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbSolenoidEngageCommand.h"
#include "Robot.h"

ClimbSolenoidEngageCommand::ClimbSolenoidEngageCommand()
{
	// Intentionally skipping the Requires to not interrupt driving climb wheels
	// with the driver while held button, which requires the climb subsystem
  //Requires(&Robot::m_climbSubsystem);
}

// Called just before this Command runs the first time
void ClimbSolenoidEngageCommand::Initialize()
{
    Robot::m_climbSubsystem.ClimbSolenoidEngage();
}

// Called repeatedly when this Command is scheduled to run
void ClimbSolenoidEngageCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ClimbSolenoidEngageCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimbSolenoidEngageCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbSolenoidEngageCommand::Interrupted() {}
