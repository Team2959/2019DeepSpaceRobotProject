/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveCargoArmCommand.h"
#include "commands/MoveLiftAndShuttleCommand.h"
#include "Robot.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include "subsystems/CargoArmPositions.h"

MoveLiftAndShuttleCommand::MoveLiftAndShuttleCommand(double targetLiftPosition)
{
  Requires(&Robot::m_liftAndShuttleSubsystem);

  m_targetLiftPosition = targetLiftPosition;
}

// Called just before this Command runs the first time
void MoveLiftAndShuttleCommand::Initialize() 
{
  m_tiltCargoArm = false;
  m_moveCargoArmUp = false;
}

// Called repeatedly when this Command is scheduled to run
void MoveLiftAndShuttleCommand::Execute()
{
  // tell the LiftAndShuttleSubsystem the target Lift Positions.
  Robot::m_liftAndShuttleSubsystem.MoveLiftToPosition(m_targetLiftPosition);

  //if robot has cargo
  if (Robot::m_cargoControlSubsystem.CargoIn())
  {
    // since we are moving the lift, get the cargo ready to deliver from up position
    if (m_moveCargoArmUp == false)
    {
      auto ptr = new MoveCargoArmCommand(kArmUpPosition);
      ptr->Start();
      m_moveCargoArmUp = true;
    }

    //If arm is moving up and haven't moved arm up, do so
    if (m_tiltCargoArm == false &&
       fabs(m_targetLiftPosition - kLiftCargoShipPosition) < 0.001 &&
       Robot::m_liftAndShuttleSubsystem.CurrentLiftPosition() >= kLiftCargoShipPosition - 3)
    {
      auto ptr = new MoveCargoArmCommand(kArmTiltForwardPosition);
      ptr->Start();
      m_tiltCargoArm = true;
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool MoveLiftAndShuttleCommand::IsFinished()
{
   return Robot::m_liftAndShuttleSubsystem.IsLiftAtPosition(m_targetLiftPosition);
}

// Called once after isFinished returns true
void MoveLiftAndShuttleCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveLiftAndShuttleCommand::Interrupted()
{
  Robot::m_liftAndShuttleSubsystem.StopAtCurrentPosition();
}
