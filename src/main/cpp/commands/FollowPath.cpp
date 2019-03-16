/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/FollowPath.h"
#include "Robot.h"

FollowPath::FollowPath(const std::string& path, VelocityUnits units):
    m_pathName(path)
{
    // Use Requires() here to declare subsystem dependencies
    Requires(&Robot::m_driveTrainSubsystem);
}

// Called just before this Command runs the first time
void FollowPath::Initialize()
{
    // Setup initial path variables, such as right, left velocities, heading and times
    LoadPathFile();
}

// Called repeatedly when this Command is scheduled to run
void FollowPath::Execute()
{
    if (m_trajectories.empty()) {
        return;
    }
    
    Trajectory current = m_trajectories.front();
    
    Robot::m_driveTrainSubsystem.TankDrive(
        current.leftVelocity * m_conversionFactor,
        current.rightVelocity * m_conversionFactor
    );
    
    m_trajectories.pop_front();
}

// Make this return true when this Command no longer needs to run execute()
bool FollowPath::IsFinished()
{
    return m_trajectories.empty();
}

// Called once after isFinished returns true
void FollowPath::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowPath::Interrupted() {}

void FollowPath::SetUnitConversion(VelocityUnits v)
{
    double factor = 1;
    
    switch (v) {
    case VelocityUnits::kMetersPerSecond:
        factor = 0.3048;
        break;
    case VelocityUnits::kInchesPerSecond:
        factor = 12;
        break;
    }

    m_conversionFactor = (1 / (M_PI * kDriveTrainWheelSize * factor)) * 60;
}

void FollowPath::LoadPathFile()
{
}