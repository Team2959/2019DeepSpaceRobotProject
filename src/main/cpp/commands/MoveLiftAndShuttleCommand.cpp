/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveLiftAndShuttleCommand.h"
#include "Robot.h"

MoveLiftAndShuttleCommand::MoveLiftAndShuttleCommand(double targetShuttlePosition, double targetLiftPosition)
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_liftAndShuttleSubsytem);

  m_targetShuttlePosition = targetShuttlePosition;
  m_targetLiftPosition = targetLiftPosition;
}

// Called just before this Command runs the first time
void MoveLiftAndShuttleCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void MoveLiftAndShuttleCommand::Execute()
{
  // tell the LiftAndShuttleSubsystem the target Shuttle and Lift Positions.
  Robot::m_liftAndShuttleSubsytem.MoveToTargetPosition(
    m_targetShuttlePosition, m_targetLiftPosition,
    Robot::m_cargoArmSubsystem.IsArmAboveCargoShuttle());
}

// Make this return true when this Command no longer needs to run execute()
bool MoveLiftAndShuttleCommand::IsFinished()
{
   return Robot::m_liftAndShuttleSubsytem.IsAtTargetPosition(
     m_targetShuttlePosition, m_targetLiftPosition);
}

// Called once after isFinished returns true
void MoveLiftAndShuttleCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveLiftAndShuttleCommand::Interrupted()
{
  Robot::m_liftAndShuttleSubsytem.StopAtCurrentPosition();
}