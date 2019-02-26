/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ExtendCargoArmCommand.h"
#include "subsystems/CargoArmPositions.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include "subsystems/HatchSubsystem.h"
#include "Robot.h"
#include "commands/MoveCargoTowardRearCommand.h"

ExtendCargoArmCommand::ExtendCargoArmCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_cargoArmSubsystem);
  Requires(&Robot::m_hatchSubsystem);
}

// Called just before this Command runs the first time
void ExtendCargoArmCommand::Initialize()
{
  Robot::m_hatchSubsystem.RetractMechanism();
}

// Called repeatedly when this Command is scheduled to run
void ExtendCargoArmCommand::Execute() 
{
  // keep feeding the target position, in case we could only go part way
  if (Robot::m_liftAndShuttleSubsystem.CurrentShuttlePosition() >= 0)
  {
    bool atFront = Robot::m_liftAndShuttleSubsystem.IsShuttleAtPosition(kShuttleFrontPosition);

    // try to extend arm
    Robot::m_cargoArmSubsystem.MoveCargoArmToPosition(kArmFrontPosition, atFront);

    // start wheels, once at front
    if (atFront && Robot::m_cargoControlSubsystem.CargoIn() == false)
    {
      auto ptr = new MoveCargoTowardRearCommand();
      ptr->Start();
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendCargoArmCommand::IsFinished()
{
  return Robot::m_cargoArmSubsystem.IsArmAtPosition(kArmFrontPosition);
}

// Called once after isFinished returns true
void ExtendCargoArmCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendCargoArmCommand::Interrupted()
{
  Robot::m_cargoArmSubsystem.StopAtCurrentPosition();
}
