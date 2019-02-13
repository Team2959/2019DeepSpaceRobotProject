/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CustomClasses/VelocityTankDrive.h"

#include <frc/smartdashboard/SmartDashboard.h>

VelocityTankDrive::VelocityTankDrive(rev::CANSparkMax& leftPrimary, rev::CANSparkMax& rightPrimary):
    m_rightPrimary(rightPrimary), m_leftPrimary(leftPrimary)
{
    m_rightPID = m_rightPrimary.GetPIDController();
    m_leftPID  = m_leftPrimary.GetPIDController();

    m_rightEncoder = m_rightPrimary.GetEncoder();
    m_leftEncoder  = m_leftPrimary.GetEncoder();

    // Set the PIDF gains for the primary motor controllers
    SetupPIDController(m_rightPID);
    SetupPIDController(m_leftPID);

    //NavX Communication
    //ahrs = new AHRS(SerialPort::Port::kUSB);
}

void VelocityTankDrive::SetupSparkMax (rev::CANSparkMax& motor, double motorMaxSpeed,double driveSafetyFactor, double robotMaxAccel, double driveMaxCurrent)
{
    motor.SetSmartCurrentLimit(driveMaxCurrent);
    motor.SetRampRate(motorMaxSpeed / (robotMaxAccel * driveSafetyFactor));
    motor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}

void VelocityTankDrive::SetupPIDController(rev::CANPIDController& pid)
{
    pid.SetP(m_proportional);
    pid.SetI(m_integral);
    pid.SetD(m_derivative);
    pid.SetIZone(m_iZone);
    pid.SetFF(m_feedForward);
    pid.SetOutputRange(-1, 1);
}

void VelocityTankDrive::TankDrive(double left, double right)
{
    // Set the left and right side speeds
    frc::SmartDashboard::PutNumber("Drive/L Setpoint", left);
    frc::SmartDashboard::PutNumber("Drive/R Setpoint", right);

    m_rightPID.SetReference(right, rev::ControlType::kVelocity);
    m_leftPID.SetReference(left, rev::ControlType::kVelocity);

    FeedWatchdog();
}
void VelocityTankDrive::SetupPIDGains (double p, double i, double d, double ff, double iz)
{
    m_proportional = p;
    m_integral     = i;
    m_derivative   = d;
    m_feedForward  = ff;
    m_iZone        = iz;

    SetupPIDController(m_rightPID);
    SetupPIDController(m_leftPID);
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
}

void VelocityTankDrive::DisabledWatchDog ()
{
    FeedWatchdog();
}
