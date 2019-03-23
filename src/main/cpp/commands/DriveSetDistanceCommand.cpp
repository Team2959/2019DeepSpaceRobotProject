/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "subsystems/DriveTrainSubsystem.h"
#include "commands/DriveSetDistanceCommand.h"

DriveSetDistanceCommand::DriveSetDistanceCommand(double distance, double speed) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
      Requires(&Robot::m_driveTrainSubsystem);
      m_speed = speed;
      
}

// Called just before this Command runs the first time
void DriveSetDistanceCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveSetDistanceCommand::Execute() 
{
  //  Robot::m_climbSubsystem.ClimbWheelsSetPosition(m_targetPosition);

  while(Robot::m_driveTrainSubsystem.AreWheelsAtDistance(kDriveTargetDistance) != true)
  {
    Robot::m_driveTrainSubsystem.TankDrive(m_speed,m_speed);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool DriveSetDistanceCommand::IsFinished()
 { 
   return Robot::m_driveTrainSubsystem.AreWheelsAtDistance(kDriveTargetDistance);
 }

// Called once after isFinished returns true
void DriveSetDistanceCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveSetDistanceCommand::Interrupted() {
      Robot::m_driveTrainSubsystem.AreWheelsAtDistance(Robot::m_driveTrainSubsystem.CurrentWheelDistance());
}
