/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ClimbSubsystem.h"
#include "utilities/MotorControllerHelpers.h"
#include <frc/smartdashboard/SmartDashboard.h>

// Climb constants
constexpr double kCruiseVelocity = 300;
constexpr double kAcceleration = 450;

ClimbSubsystem::ClimbSubsystem() : Subsystem("ClimbSubsystem")
{
    m_right.GetSlotConfigs(m_pidConfig);
    m_pidConfig.kP = 0.4;
    m_pidConfig.kI = 0.0;
    m_pidConfig.kD = 0;
    m_pidConfig.kF = 0;
    // m_pidConfig.integralZone = x;
    // m_pidConfig.closedLoopPeakOutput = 1.0;
    // m_pidConfig.allowableClosedloopError = 128;
    MotorControllerHelpers::ConfigureTalonSrxMotorController(m_left, m_pidConfig, true);
    MotorControllerHelpers::ConfigureTalonSrxMotorController(m_right, m_pidConfig, false);

    m_left.ConfigMotionCruiseVelocity(kCruiseVelocity, 10);
    m_left.ConfigMotionAcceleration(kAcceleration, 10);

    m_right.ConfigMotionCruiseVelocity(kCruiseVelocity, 10);
    m_right.ConfigMotionAcceleration(kAcceleration, 10);
}

void ClimbSubsystem::OnRobotInit()
{
    // Zero shuttle positions
    m_left.SetSelectedSensorPosition(0, 0, 0);
    m_right.SetSelectedSensorPosition(0, 0, 0);
    ClimbSolenoidDisengage();

    frc::SmartDashboard::PutBoolean("Climb Solenoid", m_newClimbEngage.Get() == frc::DoubleSolenoid::Value::kForward);

    // Debug info
    frc::SmartDashboard::PutData(this);
    MotorControllerHelpers::DashboardInitTalonSrx("Climb", m_pidConfig);
    frc::SmartDashboard::PutBoolean("Climb: Start", false);
    frc::SmartDashboard::PutBoolean("Climb: Engage", false);
}

void ClimbSubsystem::OnRobotPeriodic(bool updateDebugInfo)
{
    frc::SmartDashboard::PutBoolean("Climb Solenoid", m_newClimbEngage.Get() == frc::DoubleSolenoid::Value::kForward);

    m_updateDebugInfo = updateDebugInfo;
    if (updateDebugInfo)
        DashboardDebugPeriodic();
}

void ClimbSubsystem::DashboardDebugPeriodic()
{
    if (frc::SmartDashboard::GetBoolean("Climb: Engage", false))
        ClimbSolenoidEngage();
    else
        ClimbSolenoidDisengage();

    MotorControllerHelpers::DashboardDataTalonSrx("Climb", m_left, m_pidConfig);
    MotorControllerHelpers::DashboardDataTalonSrx("Climb", m_right, m_pidConfig);
    frc::SmartDashboard::PutNumber("Climb: Position", CurrentClimbWheelsPosition());
    frc::SmartDashboard::PutNumber("Climb: Position Left", m_left.GetSelectedSensorPosition(0));
    frc::SmartDashboard::PutNumber("Climb: Velocity", m_right.GetSelectedSensorVelocity());

    auto startShuttle = frc::SmartDashboard::GetBoolean("Climb: Start", false);
    if (startShuttle)
    {
        auto targetPosition = frc::SmartDashboard::GetNumber("Climb: Go To Position", 0);
        ClimbWheelsSetPosition(targetPosition);
    }
}

void ClimbSubsystem::ClimbWheelsSetPosition(double position)
{
    m_left.Set(ctre::phoenix::motorcontrol::ControlMode::MotionMagic, position);
    m_right.Set(ctre::phoenix::motorcontrol::ControlMode::MotionMagic, position);

    if (m_updateDebugInfo)
        frc::SmartDashboard::PutNumber("Climb: Target", position);
}

void ClimbSubsystem::ClimbSolenoidEngage() 
{
    m_climbEngage.Set(true);
    m_newClimbEngage.Set(frc::DoubleSolenoid::Value::kForward);
}

void ClimbSubsystem::ClimbSolenoidDisengage()
{
    m_climbEngage.Set(false);
    m_newClimbEngage.Set(frc::DoubleSolenoid::Value::kReverse);
}

void ClimbSubsystem::PowerToClimbWheels(double amps)
{
    m_left.Set(ctre::phoenix::motorcontrol::ControlMode::Current, amps);
    m_right.Set(ctre::phoenix::motorcontrol::ControlMode::Current, amps);
}

void ClimbSubsystem::StopAtCurrentDistance()
{
    ClimbWheelsSetPosition(CurrentClimbWheelsPosition());
}

bool ClimbSubsystem::AreClimbWheelsAtPosition( double targetPosition)
{
    //Check to see if distance driven is close
    return CurrentClimbWheelsPosition() > (targetPosition - kDriveCloseEnoughToPosition);
}

double ClimbSubsystem::CurrentClimbWheelsPosition()
{
    return  m_right.GetSelectedSensorPosition();
}

void ClimbSubsystem::SetArmCurrentLimitLow()
{
  m_left.ConfigContinuousCurrentLimit(10);
  m_right.ConfigContinuousCurrentLimit(10);
  m_left.EnableCurrentLimit(true);
  m_right.EnableCurrentLimit(true);
}

void ClimbSubsystem::SetArmPercentOutputLow()
{
  m_left.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.25);
  m_right.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.25);
}

void ClimbSubsystem::StopAndZero()
{
  m_left.StopMotor();
  m_right.StopMotor();
  m_left.SetSelectedSensorPosition(0,0,0);
  m_right.SetSelectedSensorPosition(0,0,0);
  ClimbWheelsSetPosition(0);
}

void ClimbSubsystem::SetArmCurrentLimitHigh()
{
  m_left.ConfigContinuousCurrentLimit(60);
  m_right.ConfigContinuousCurrentLimit(60);
  m_left.EnableCurrentLimit(true);
  m_right.EnableCurrentLimit(true);
}
