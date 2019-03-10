/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RetractMechanismCommand.h"
#include "Robot.h"

RetractMechanismCommand::RetractMechanismCommand(double timeout)
 : TimedCommand(timeout)
{
  Requires(&Robot::m_hatchSubsystem);
}

// Called just before this Command runs the first time
void RetractMechanismCommand::Initialize() {
  Robot::m_hatchSubsystem.SafetyExtend();
}

// Called repeatedly when this Command is scheduled to run
void RetractMechanismCommand::Execute() {
}

// Called once after isFinished returns true
void RetractMechanismCommand::End() {
   Robot::m_hatchSubsystem.RetractMechanism();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractMechanismCommand::Interrupted() {}
