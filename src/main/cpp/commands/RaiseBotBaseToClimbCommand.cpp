/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RaiseBotBaseToClimbCommand.h"
#include "Robot.h"
#include "subsystems/LiftAndShuttlePositions.h"


RaiseBotBaseToClimbCommand::RaiseBotBaseToClimbCommand() {
  Requires(&Robot::m_liftAndShuttleSubsystem);
}

// Called just before this Command runs the first time
void RaiseBotBaseToClimbCommand::Initialize()
{
  Robot::m_liftAndShuttleSubsystem.EnableLiftBottomTrigger(false);
}

// Called repeatedly when this Command is scheduled to run
void RaiseBotBaseToClimbCommand::Execute()
{
  if (Robot::m_liftAndShuttleSubsystem.IsLiftAtBottom())
  {

  }
  else if (Robot::m_liftAndShuttleSubsystem.CurrentLiftPosition() >= 0.05)
  {
    Robot::m_liftAndShuttleSubsystem.MoveLiftToPosition(kLiftFloorPosition);
  }
  else
  {
    Robot::m_liftAndShuttleSubsystem.DriveLiftWithVelocityControl(kLiftToSwitchVelocity);
    
  }
}

// Make this return true when this Command no longer needs to run execute()
bool RaiseBotBaseToClimbCommand::IsFinished() { return Robot::m_liftAndShuttleSubsystem.IsLiftAtBottom(); }

// Called once after isFinished returns true
void RaiseBotBaseToClimbCommand::End()
{
  Robot::m_liftAndShuttleSubsystem.LiftBottomReset();
  Interrupted();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RaiseBotBaseToClimbCommand::Interrupted()
{
  Robot::m_liftAndShuttleSubsystem.EnableLiftBottomTrigger(true);
}
