/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ClimbSubsystem.h"
#include "commands/ClimbWheelsSetPositionCommand.h"
#include "Robot.h"

ClimbWheelsSetPositionCommand::ClimbWheelsSetPositionCommand(double position) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
    Requires(&Robot::m_climbSubsystem);
    m_targetPosition = position;
}

// Called just before this Command runs the first time
void ClimbWheelsSetPositionCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ClimbWheelsSetPositionCommand::Execute() {
  Robot::m_climbSubsystem.ClimbWheelsSetPosition(m_targetPosition);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbWheelsSetPositionCommand::IsFinished()
 {  
     return Robot::m_climbSubsystem.AreClimbWheelsAtPosition(m_targetPosition);
 }

// Called once after isFinished returns true
void ClimbWheelsSetPositionCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbWheelsSetPositionCommand::Interrupted() {
  return Robot::m_climbSubsystem.StopAtCurrentDistance();
}
