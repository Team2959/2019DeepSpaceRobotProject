/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrainSubsystem.h"
#include "commands/DriveWithControllerCommand.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include <cmath>

DriveTrainSubsystem::DriveTrainSubsystem() : Subsystem("DriveTrainSubsystem")
{
    // Set up the motor controllers
    VelocityTankDrive::SetupSparkMax(m_rightPrimary, kMotorMaxSpeed, kDriveSafetyFactor, kRobotMaxAccel, kDriveMaxCurrent);
    VelocityTankDrive::SetupSparkMax(m_rightFollower, kMotorMaxSpeed, kDriveSafetyFactor, kRobotMaxAccel, kDriveMaxCurrent);
    VelocityTankDrive::SetupSparkMax(m_leftPrimary, kMotorMaxSpeed, kDriveSafetyFactor, kRobotMaxAccel, kDriveMaxCurrent);
    VelocityTankDrive::SetupSparkMax(m_leftFollower, kMotorMaxSpeed, kDriveSafetyFactor, kRobotMaxAccel, kDriveMaxCurrent);
   
    // Not doing follower, since reduce CAN traffic in setup and slows sending into fo follower
    //  therefore, configure like primary and send same info to all
    // m_rightFollower.Follow(m_rightPrimary);
    // m_leftFollower.Follow(m_leftPrimary);

    try {
        /* Communicate w/navX-MXP via the MXP USB.
           See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */
        ahrs = new AHRS(SerialPort::Port::kUSB);
    } catch (std::exception ex ) {
        std::string err_string = "Error instantiating navX-MXP:  ";
        err_string += ex.what();
        DriverStation::ReportError(err_string.c_str());
    }

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

void DriveTrainSubsystem::OnRobotInit()
{
    // P: 0.00012, I: 0.000156, D: 0.00000978, FF: 0.003
    
    m_tankDrive.SetupRightPIDGains(0.0003, 0.0, 0.0, 0.0002, 600);
    m_tankDrive.SetupLeftPIDGains(0.0003, 0.0, 0.0, 0.0002, 600);

    frc::SmartDashboard::PutBoolean("White1", false);
    frc::SmartDashboard::PutBoolean("White2", false);
    frc::SmartDashboard::PutBoolean("White3", false);

    DashboardDebugInit();
}

void DriveTrainSubsystem::OnRobotPeriodic(bool updateDebugInfo)
{
    frc::SmartDashboard::PutBoolean("White1", WhiteTape1());
    frc::SmartDashboard::PutBoolean("White2", WhiteTape2());
    frc::SmartDashboard::PutBoolean("White3", WhiteTape3());

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
    frc::SmartDashboard::PutNumber("Heading", GetHeading());
    frc::SmartDashboard::PutNumber("Pitch", GetPitch());


}

double DriveTrainSubsystem::GetMaxSpeed()
{
    return kDriveSafetyFactor * kMotorMaxSpeed;
}

double DriveTrainSubsystem::GetMaxAccel()
{
    return kDriveSafetyFactor * kRobotMaxAccel;
}


double DriveTrainSubsystem::GetHeading()
{
    if (ahrs) {
        return ahrs->GetFusedHeading();
    }

    return 0.0;

}

double DriveTrainSubsystem::GetPitch()
{
    if (ahrs) {
        return ahrs->GetPitch();
    }

    return 0.0;
}

bool DriveTrainSubsystem::IsBeyondTypicalPitch()
{
    double magnitude = std::abs(GetPitch());
    return magnitude > kDriveTiltThreshold;
}

void DriveTrainSubsystem::DisabledWatchDog()
{
    m_tankDrive.DisabledWatchDog();
}

bool DriveTrainSubsystem::WhiteTape1() const
{
    return !m_whiteTape1.Get();
}

bool DriveTrainSubsystem::WhiteTape2() const
{
    return !m_whiteTape2.Get();
}

bool DriveTrainSubsystem::WhiteTape3() const
{
    return !m_whiteTape3.Get();
}
