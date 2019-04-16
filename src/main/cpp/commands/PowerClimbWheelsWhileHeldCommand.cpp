/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PowerClimbWheelsWhileHeldCommand.h"
#include "Robot.h"

PowerClimbWheelsWhileHeldCommand::PowerClimbWheelsWhileHeldCommand(double amps) {
  Requires(&Robot::m_climbSubsystem);
  m_amps = amps;
}

// Called just before this Command runs the first time
void PowerClimbWheelsWhileHeldCommand::Initialize() {
  Robot::m_climbSubsystem.PowerToClimbWheels(m_amps);
  Robot::m_liftAndShuttleSubsystem.ReconfigureLiftForClimb();
}

// Called repeatedly when this Command is scheduled to run
void PowerClimbWheelsWhileHeldCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool PowerClimbWheelsWhileHeldCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void PowerClimbWheelsWhileHeldCommand::End() {
  Robot::m_climbSubsystem.PowerToClimbWheels(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PowerClimbWheelsWhileHeldCommand::Interrupted() {
  End();
}
