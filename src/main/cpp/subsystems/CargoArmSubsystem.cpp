/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoArmSubsystem.h"
#include "subsystems/CargoArmPositions.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "utilities/MotorControllerHelpers.h"
#include <algorithm>
#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"

constexpr double kCloseEnoughToPosition = 500;

CargoArmSubsystem::CargoArmSubsystem() : Subsystem("CargoArmSubsystem")
{
  m_left.GetSlotConfigs(m_pidConfig);
  m_pidConfig.kP = 0.1;
  m_pidConfig.kI = 0.0001;
  m_pidConfig.kD = 0;
  m_pidConfig.kF = 0.057;
  // m_pidConfig.integralZone = x;
  // m_pidConfig.closedLoopPeakOutput = 1.0;
  // m_pidConfig.allowableClosedloopError = 128;

  m_left.ConfigMotionCruiseVelocity(5000, 10);
  m_left.ConfigMotionAcceleration(4500,10);

  MotorControllerHelpers::ConfigureTalonSrxMotorController(m_left, m_pidConfig, false);
  m_right.Follow(m_left);
  m_right.SetInverted( ctre::phoenix::motorcontrol::InvertType::OpposeMaster);
}

void CargoArmSubsystem::OnRobotInit()
{
  MoveCargoArmToPosition(0);

  DashboardDebugInit();
}

void CargoArmSubsystem::OnRobotPeriodic(bool updateDebugInfo)
{
  m_updateDebugInfo = updateDebugInfo;
  if (updateDebugInfo)
    DashboardDebugPeriodic();
}

void CargoArmSubsystem::DashboardDebugInit()
{
  frc::SmartDashboard::PutData(this);
  frc::SmartDashboard::PutBoolean("Arm: Start", false);
  MotorControllerHelpers::DashboardInitTalonSrx("Arm", m_pidConfig);
}

void CargoArmSubsystem::DashboardDebugPeriodic()
{
  MotorControllerHelpers::DashboardDataTalonSrx("Arm", m_left, m_pidConfig);

  frc::SmartDashboard::PutNumber("Arm: Position", CurrentArmPosition());
  frc::SmartDashboard::PutNumber("Arm: Velocity", m_left.GetSelectedSensorVelocity());

  auto start = frc::SmartDashboard::GetBoolean("Arm: Start", false);
  if (start)
  {
    auto targetPosition = frc::SmartDashboard::GetNumber("Arm: Go To Position", 0);
    targetPosition = std::min(targetPosition, kArmExtendPosition + kCloseEnoughToPosition);
    targetPosition = std::max(targetPosition, kArmTiltBackwardPosition - kCloseEnoughToPosition);
    MoveCargoArmToPosition(targetPosition);
  }
}

double CargoArmSubsystem::CurrentArmPosition()
{
  // actually check position is at target position
  return m_left.GetSelectedSensorPosition();
}

bool CargoArmSubsystem::IsArmAtPosition(double targetPosition)
{
  return fabs(CurrentArmPosition() - targetPosition) < kCloseEnoughToPosition;
}

void CargoArmSubsystem::MoveCargoArmToPosition(double targetPosition)
{
  m_left.Set(ctre::phoenix::motorcontrol::ControlMode::MotionMagic, targetPosition);

  if (m_updateDebugInfo)
    frc::SmartDashboard::PutNumber("Arm: Target", targetPosition);
}

void CargoArmSubsystem::StopAtCurrentPosition()
{
  MoveCargoArmToPosition(CurrentArmPosition());
}

void CargoArmSubsystem::StopAndZero()
{
  m_left.StopMotor();
  m_left.SetSelectedSensorPosition(0,0,0);
  MoveCargoArmToPosition(0);
}

void CargoArmSubsystem::SetArmCurrentLimitHigh()
{
  m_left.ConfigContinuousCurrentLimit(60);
  m_left.EnableCurrentLimit(true);
}

void CargoArmSubsystem::SetArmCurrentLimitLow()
{
  m_left.ConfigContinuousCurrentLimit(10);
  m_left.EnableCurrentLimit(true);
}

void CargoArmSubsystem::SetArmPercentOutputLow()
{
  m_left.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.1);
}
