/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ExtendCargoArmFrontCommand.h"
#include "Robot.h"
#include "commands/MoveCargoTowardRearCommand.h"
#include "subsystems/CargoArmPositions.h"
#include "subsystems/LiftAndShuttlePositions.h"

ExtendCargoArmFrontCommand::ExtendCargoArmFrontCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_cargoArmSubsystem);
}

// Called just before this Command runs the first time
void ExtendCargoArmFrontCommand::Initialize()
{
  Robot::m_cargoArmSubsystem.MoveCargoArmToPosition(kArmFrontPosition,
      Robot::m_liftAndShuttleSubsytem.IsShuttleAtPosition(kShuttleFrontPosition));

  if (Robot::m_cargoControlSubsystem.CargoIn() == false)
  {
    auto ptr = new MoveCargoTowardRearCommand();
    ptr->Start();
  }
}

// Called repeatedly when this Command is scheduled to run
void ExtendCargoArmFrontCommand::Execute()
{
  // keep feeding the target position, in case we could only go part way
  Robot::m_cargoArmSubsystem.MoveCargoArmToPosition(kArmFrontPosition,
      Robot::m_liftAndShuttleSubsytem.IsShuttleAtPosition(kShuttleFrontPosition));
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendCargoArmFrontCommand::IsFinished()
{
  return Robot::m_cargoArmSubsystem.IsArmAtPosition(kArmFrontPosition);
}

// Called once after isFinished returns true
void ExtendCargoArmFrontCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendCargoArmFrontCommand::Interrupted() 
{
    Robot::m_cargoArmSubsystem.StopAtCurrentPosition();
}
