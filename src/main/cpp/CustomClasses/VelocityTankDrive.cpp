/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CustomClasses/VelocityTankDrive.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include "utilities/MotorControllerHelpers.h"

VelocityTankDrive::VelocityTankDrive(rev::CANSparkMax& leftPrimary, rev::CANSparkMax& rightPrimary):
    m_rightPrimary(rightPrimary), m_leftPrimary(leftPrimary),
    m_rightPID(m_rightPrimary),  m_leftPID(m_leftPrimary),
    m_rightEncoder(m_rightPrimary),  m_leftEncoder(m_leftPrimary)
{
    //NavX Communication
    //ahrs = new AHRS(SerialPort::Port::kUSB);
}

void VelocityTankDrive::SetupSparkMax (rev::CANSparkMax& motor, double motorMaxSpeed,double driveSafetyFactor, double robotMaxAccel, double driveMaxCurrent)
{
    MotorControllerHelpers::SetupSparkMax(motor, driveMaxCurrent);
    // motor.SetClosedLoopRampRate(motorMaxSpeed / (robotMaxAccel));
}

void VelocityTankDrive::TankDrive(double left, double right)
{
    // Set the left and right side speeds
    rev::CANError er = m_rightPID.SetReference(right, rev::ControlType::kVelocity);
    rev::CANError el = m_leftPID.SetReference(left, rev::ControlType::kVelocity);

    m_rightSetpoint = right;
    m_leftSetpoint  = left;

    FeedWatchdog();
}
void VelocityTankDrive::SetupRightPIDGains (double p, double i, double d, double ff, double iz)
{
    m_rightPID.SetP(p);
    m_rightPID.SetI(i);
    m_rightPID.SetD(d);
    m_rightPID.SetIZone(iz);
    m_rightPID.SetFF(ff);
    m_rightPID.SetOutputRange(-1, 1);
}

void VelocityTankDrive::SetupLeftPIDGains (double p, double i, double d, double ff, double iz)
{
    m_leftPID.SetP(p);
    m_leftPID.SetI(i);
    m_leftPID.SetD(d);
    m_leftPID.SetIZone(iz);
    m_leftPID.SetFF(ff);
    m_leftPID.SetOutputRange(-1, 1);
}

void VelocityTankDrive::StopMotor () 
{
    m_rightPrimary.StopMotor();
    m_leftPrimary.StopMotor();

    FeedWatchdog();
}

void VelocityTankDrive::GetDescription (wpi::raw_ostream& desc) const
{
    desc << "Velocity Tank Drive";
}

void VelocityTankDrive::InitSendable (SendableBuilder& builder) 
{

}

void VelocityTankDrive::DashboardDataInit () 
{
    MotorControllerHelpers::DashboardInitSparkMax("Drive/Right", m_rightPID, m_rightEncoder);
    MotorControllerHelpers::DashboardInitSparkMax("Drive/Left", m_leftPID, m_leftEncoder);
}

void VelocityTankDrive::DashboardDataUpdate () 
{
    MotorControllerHelpers::DashboardDataSparkMax("Drive/Right", m_rightPID, m_rightEncoder);
    MotorControllerHelpers::DashboardDataSparkMax("Drive/Left", m_leftPID, m_leftEncoder);

    frc::SmartDashboard::PutNumber("Drive/Right: Setpoint", m_rightSetpoint);
    frc::SmartDashboard::PutNumber("Drive/Left: Setpoint", m_leftSetpoint);
}

void VelocityTankDrive::DisabledWatchDog ()
{
    FeedWatchdog();
}
