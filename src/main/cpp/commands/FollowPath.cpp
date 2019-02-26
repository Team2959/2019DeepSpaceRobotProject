/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/FollowPath.h"
#include "Robot.h"

FollowPath::FollowPath() {
  // Use Requires() here to declare subsystem dependencies
Requires(&Robot::m_driveTrainSubsystem);

}

// Called just before this Command runs the first time
void FollowPath::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void FollowPath::Execute() {
  Robot::m_driveTrainSubsystem.TankDrive(m_right[m_index], m_left[m_index]);
}

// Make this return true when this Command no longer needs to run execute()
bool FollowPath::IsFinished() { return false; }

// Called once after isFinished returns true
void FollowPath::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowPath::Interrupted() {}

  double FollowPath::UnitCoversion(double x)
  {
return x*ConversionFactor;
  }
