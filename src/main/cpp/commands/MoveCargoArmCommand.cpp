/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveCargoArmCommand.h"
#include "Robot.h"
#include "commands/StopCargoControlWheelsCommand.h"
#include "subsystems/CargoArmPositions.h"

MoveCargoArmCommand::MoveCargoArmCommand(double targetCargoArmPosition) {
  Requires(&Robot::m_cargoArmSubsystem);
  Requires(&Robot::m_cargoControlSubsystem);
  m_targetCargoArmPosition = targetCargoArmPosition;
}

// Called just before this Command runs the first time
void MoveCargoArmCommand::Initialize()
{
  double dCargoWheelSpeed = 0;
  if(Robot::m_cargoControlSubsystem.CargoIn())
  {
	  dCargoWheelSpeed = kHoldCargoWhileMovingSpeed;
  }
  Robot::m_cargoControlSubsystem.ChangeWheelsSpeed(dCargoWheelSpeed);

  Robot::m_cargoArmSubsystem.MoveCargoArmToPosition(m_targetCargoArmPosition);
}

// Called repeatedly when this Command is scheduled to run
void MoveCargoArmCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool MoveCargoArmCommand::IsFinished()
{
  return Robot::m_cargoArmSubsystem.IsArmAtPosition(m_targetCargoArmPosition);
}

// Called once after isFinished returns true
void MoveCargoArmCommand::End()
{
  double dCargoWheelSpeed = 0;
  if(Robot::m_cargoControlSubsystem.CargoIn())
  {
	  dCargoWheelSpeed = kHoldCargoSpeed;
  }
  Robot::m_cargoControlSubsystem.ChangeWheelsSpeed(dCargoWheelSpeed);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveCargoArmCommand::Interrupted()
{
  Robot::m_cargoArmSubsystem.StopAtCurrentPosition();
  End();
}
