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
constexpr double kCruiseVelocity = 3000;
constexpr double kAcceleration = 4500;

ClimbSubsystem::ClimbSubsystem() : Subsystem("ClimbSubsystem")
{
    m_right.GetSlotConfigs(m_pidConfig);
    m_pidConfig.kP = 0.001;
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

    // Debug info
    frc::SmartDashboard::PutData(this);
    MotorControllerHelpers::DashboardInitTalonSrx("Climb", m_pidConfig);
    frc::SmartDashboard::PutBoolean("Climb: Start", false);
    frc::SmartDashboard::PutBoolean("Climb: Engage", false);
}

void ClimbSubsystem::OnRobotPeriodic(bool updateDebugInfo)
{
    m_updateDebugInfo = updateDebugInfo;
    if (updateDebugInfo)
        DashboardDebugPeriodic();
}

void ClimbSubsystem::DashboardDebugPeriodic()
{
    m_climbEngage.Set(frc::SmartDashboard::GetBoolean("Climb: Engage", false));

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
}

void ClimbSubsystem::ClimbSolenoidDisengage()
{
    m_climbEngage.Set(false);
}

void ClimbSubsystem::PowerToClimbWheels()
{
    m_left.Set(ctre::phoenix::motorcontrol::ControlMode::Current, kClimbWheelsHoldingCurrent);
    m_right.Set(ctre::phoenix::motorcontrol::ControlMode::Current, kClimbWheelsHoldingCurrent);
}

void ClimbSubsystem::StopAtCurrentDistance()
{
    ClimbWheelsSetPosition(CurrentClimbWheelsPosition());
}

bool ClimbSubsystem::AreClimbWheelsAtPosition( double targetPosition)
{
    //Check to see if distance driven is close
    return fabs(CurrentClimbWheelsPosition() - targetPosition) < kDriveCloseEnoughToPosition;
}

double ClimbSubsystem::CurrentClimbWheelsPosition()
{
    return  m_right.GetSelectedSensorPosition();
}
