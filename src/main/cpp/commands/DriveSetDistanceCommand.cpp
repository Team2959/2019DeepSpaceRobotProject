/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "subsystems/DriveTrainSubsystem.h"
#include "commands/DriveSetDistanceCommand.h"

constexpr double kDriveTargetRevolutions = 10.2; // to move wheels 21", one wheels revolution is 12.566" and there are 6.11 motor revolutions per wheel rotation 
constexpr double kDriveSpeed = 500; //RPM

DriveSetDistanceCommand::DriveSetDistanceCommand()
{
  Requires(&Robot::m_driveTrainSubsystem);
  m_startingPosition = 0;
}

// Called just before this Command runs the first time
void DriveSetDistanceCommand::Initialize()
{
  m_startingPosition = Robot::m_driveTrainSubsystem.CurrentPosition();
}

// Called repeatedly when this Command is scheduled to run
void DriveSetDistanceCommand::Execute() 
{
  Robot::m_driveTrainSubsystem.TankDrive(kDriveSpeed, kDriveSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveSetDistanceCommand::IsFinished()
{
  return Robot::m_driveTrainSubsystem.CurrentPosition() > m_startingPosition + kDriveTargetRevolutions;
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
