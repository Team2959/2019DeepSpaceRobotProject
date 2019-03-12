/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoArmSubsystem.h"
#include "subsystems/CargoArmPositions.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include "commands/TiltCargoArmCommand.h"
#include "Robot.h"

TiltCargoArmCommand::TiltCargoArmCommand() {
    Requires(&Robot::m_cargoArmSubsystem);
}

// Called just before this Command runs the first time
void TiltCargoArmCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TiltCargoArmCommand::Execute()
{
  // try to tilt arm forward
  Robot::m_cargoArmSubsystem.MoveCargoArmToPosition(kArmTiltForwardPosition);
}

// Make this return true when this Command no longer needs to run execute()
bool TiltCargoArmCommand::IsFinished()
{
  return Robot::m_cargoArmSubsystem.IsArmAtPosition(kArmTiltForwardPosition);
}

// Called once after isFinished returns true
void TiltCargoArmCommand::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TiltCargoArmCommand::Interrupted()
{
  Robot::m_cargoArmSubsystem.StopAtCurrentPosition();
}
