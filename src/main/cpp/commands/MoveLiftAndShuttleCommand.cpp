/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveLiftAndShuttleCommand.h"
#include "Robot.h"
#include "subsystems/LiftAndShuttlePositions.h"

MoveLiftAndShuttleCommand::MoveLiftAndShuttleCommand(double targetLiftPosition)
{
  Requires(&Robot::m_liftAndShuttleSubsystem);

  m_targetLiftPosition = targetLiftPosition;
}

// Called just before this Command runs the first time
void MoveLiftAndShuttleCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void MoveLiftAndShuttleCommand::Execute()
{
  // tell the LiftAndShuttleSubsystem the target Lift Positions.
  Robot::m_liftAndShuttleSubsystem.MoveLiftToPosition(m_targetLiftPosition);
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
