/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/StopCargoControlWheelsCommand.h"
#include "Robot.h"

StopCargoControlWheelsCommand::StopCargoControlWheelsCommand(double timeout, double targetSpeedSwitch, double targetSpeedEnd)
    : TimedCommand(timeout)
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_cargoControlSubsystem);
  m_targetSpeedSwitch = targetSpeedSwitch;
  m_targetSpeedEnd = targetSpeedEnd;
}

// Called just before this Command runs the first time
void StopCargoControlWheelsCommand::Initialize()
{
  Robot::m_cargoControlSubsystem.ChangeWheelsSpeed(m_targetSpeedSwitch);
}

// Called repeatedly when this Command is scheduled to run
void StopCargoControlWheelsCommand::Execute() {}

// Called once after isFinished returns true
void StopCargoControlWheelsCommand::End()
{
  Robot::m_cargoControlSubsystem.ChangeWheelsSpeed(m_targetSpeedEnd);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopCargoControlWheelsCommand::Interrupted()
{
  End();
}
