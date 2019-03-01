/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrainSubsystem.h"
#include "commands/DriveWithControllerCommand.h"

DriveTrainSubsystem::DriveTrainSubsystem() : Subsystem("DriveTrainSubsystem")
{
    // Set up the follower motor controllers
    VelocityTankDrive::SetupSparkMax(m_rightPrimary, kMotorMaxSpeed, kDriveSafetyFactor, kRobotMaxAccel, kDriveMaxCurrent);
    VelocityTankDrive::SetupSparkMax(m_rightFollower, kMotorMaxSpeed, kDriveSafetyFactor, kRobotMaxAccel, kDriveMaxCurrent);
    VelocityTankDrive::SetupSparkMax(m_leftPrimary, kMotorMaxSpeed, kDriveSafetyFactor, kRobotMaxAccel, kDriveMaxCurrent);
    VelocityTankDrive::SetupSparkMax(m_leftFollower, kMotorMaxSpeed, kDriveSafetyFactor, kRobotMaxAccel, kDriveMaxCurrent);
   
    // m_rightFollower.Follow(m_rightPrimary);
    // m_leftFollower.Follow(m_leftPrimary);
}

void DriveTrainSubsystem::InitDefaultCommand()
{
    // Set the default command for a subsystem here.
    SetDefaultCommand(new DriveWithControllerCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrainSubsystem::TankDrive(double leftSpeed, double rightSpeed)
{
    m_tankDrive.TankDrive(leftSpeed, rightSpeed);
}

void DriveTrainSubsystem::OnRobotInit(bool addDebugInfo)
{
    // P: 0.00012, I: 0.000156, D: 0.00000978, FF: 0.003
    
    m_tankDrive.SetupRightPIDGains(0.0, 0.0, 0.0, 0.003, 0.0);
    m_tankDrive.SetupLeftPIDGains(0.0, 0.0, 0.0, 0.003, 0.0);

    if (addDebugInfo)
        DashboardDebugInit();
}

void DriveTrainSubsystem::OnRobotPeriodic(bool updateDebugInfo)
{
    if (updateDebugInfo)
        DashboardDebugPeriodic();
}

void DriveTrainSubsystem::DashboardDebugInit()
{
    m_tankDrive.DashboardDebugInit();
}

void DriveTrainSubsystem::DashboardDebugPeriodic()
{
    m_tankDrive.DashboardDebugPeriodic();
}

double DriveTrainSubsystem::GetMaxSpeed()
{
    return kDriveSafetyFactor * kMotorMaxSpeed;
}

double DriveTrainSubsystem::GetMaxAccel()
{
    return kDriveSafetyFactor * kRobotMaxAccel;
}

void DriveTrainSubsystem::DisabledWatchDog()
{
    m_tankDrive.DisabledWatchDog();
}
