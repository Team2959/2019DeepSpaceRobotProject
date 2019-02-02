/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ExtendCargoArmRearCommand.h"
#include "Robot.h"
#include "commands/MoveCargoTowardFrontCommand.h"

ExtendCargoArmRearCommand::ExtendCargoArmRearCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_cargoArmSubsystem);
}

// Called just before this Command runs the first time
void ExtendCargoArmRearCommand::Initialize()
{
  Robot::m_cargoArmSubsystem.ArmExtendRear();
  if (Robot::m_cargoControlSubsystem.CargoIn() == false)
  {
    auto ptr = new MoveCargoTowardFrontCommand();
    ptr->Start();
  }
}

// Called repeatedly when this Command is scheduled to run
void ExtendCargoArmRearCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ExtendCargoArmRearCommand::IsFinished()
{
  return Robot::m_cargoArmSubsystem.ArmAtPosition();
}

// Called once after isFinished returns true
void ExtendCargoArmRearCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendCargoArmRearCommand::Interrupted() {}
