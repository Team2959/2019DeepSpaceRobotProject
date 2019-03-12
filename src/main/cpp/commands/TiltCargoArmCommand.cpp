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
  if (Robot::m_liftAndShuttleSubsystem.IsShuttleAtPosition(kShuttleFrontPosition) == true)
  {
    // try to tilt arm forward
    Robot::m_cargoArmSubsystem.MoveCargoArmToPosition(kArmTiltForwardPosition, true);
  }
  else //if (Robot::m_liftAndShuttleSubsystem.IsShuttleAtPosition(kShuttleRearPosition) == true)
  {
    // try to tilt arm backwards
    Robot::m_cargoArmSubsystem.MoveCargoArmToPosition(kArmTiltBackwardPosition, true);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool TiltCargoArmCommand::IsFinished()
{
  if (Robot::m_liftAndShuttleSubsystem.IsShuttleAtPosition(kShuttleFrontPosition) == true &&
      Robot::m_cargoArmSubsystem.IsArmAtPosition(kArmTiltForwardPosition))
  {
    return true;
  }
  else if (//Robot::m_liftAndShuttleSubsystem.IsShuttleAtPosition(kShuttleRearPosition) == true &&
      Robot::m_cargoArmSubsystem.IsArmAtPosition(kArmTiltBackwardPosition))
  {
    return true;
  }
  return false;
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
