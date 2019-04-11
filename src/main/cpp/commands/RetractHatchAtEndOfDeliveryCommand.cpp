/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RetractHatchAtEndOfDeliveryCommand.h"
#include "Robot.h"

RetractHatchAtEndOfDeliveryCommand::RetractHatchAtEndOfDeliveryCommand()
{
  Requires(&Robot::m_hatchSubsystem);
}

// Called just before this Command runs the first time
void RetractHatchAtEndOfDeliveryCommand::Initialize()
{
   Robot::m_hatchSubsystem.RetractMechanism();
}

// Called repeatedly when this Command is scheduled to run
void RetractHatchAtEndOfDeliveryCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool RetractHatchAtEndOfDeliveryCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void RetractHatchAtEndOfDeliveryCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractHatchAtEndOfDeliveryCommand::Interrupted() {}
