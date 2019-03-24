/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "subsystems/DriveTrainSubsystem.h"
#include "commands/DriveSetDistanceCommand.h"

constexpr double kDriveTargetRevolutions = 5000; 
constexpr double kDriveSpeed = 1000; 

DriveSetDistanceCommand::DriveSetDistanceCommand()
{
  Requires(&Robot::m_driveTrainSubsystem);
  m_startingPosition = 0;
}

// Called just before this Command runs the first time
void DriveSetDistanceCommand::Initialize()
{
  m_startingPosition = Robot::m_driveTrainSubsystem.CurrentPosition();
  Robot::m_driveTrainSubsystem.TankDrive(kDriveSpeed, kDriveSpeed);
}

// Called repeatedly when this Command is scheduled to run
void DriveSetDistanceCommand::Execute() 
{
}

// Make this return true when this Command no longer needs to run execute()
bool DriveSetDistanceCommand::IsFinished()
{
  return fabs(m_startingPosition - Robot::m_driveTrainSubsystem.CurrentPosition()) >= kDriveTargetRevolutions;
}

// Called once after isFinished returns true
void DriveSetDistanceCommand::End()
{
  Robot::m_driveTrainSubsystem.TankDrive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveSetDistanceCommand::Interrupted()
{
  End();
}
