/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LiftAndShuttleSubsystem.h"

constexpr int kShuttleMiddlePosition = 0;
constexpr int kShuttleFrontPosition = 5000;
constexpr int kShuttleRearPosition = -3000;
constexpr double kCloseEnoughToPosition = 100;

LiftAndShuttleSubsystem::LiftAndShuttleSubsystem() : Subsystem("LiftAndShuttleSubsystem") 
{
  // Shuttle motor controller configuration
  ConfigureTalonMotorController(m_leftShuttle);
  ConfigureTalonMotorController(m_rightShuttle);

  ShuttleMiddle();

  // Lift motor contorller configuration
  m_liftFollower1.Follow(m_liftPrimary);
  m_liftFollower2.Follow(m_liftPrimary);
}

void LiftAndShuttleSubsystem::ConfigureTalonMotorController(
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX & motorController)
{
  motorController.ConfigSelectedFeedbackSensor(
    ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
	motorController.Config_kF(0, 0, 0);

	motorController.Config_kP(0, 1.0, 0);
	motorController.Config_kI(0, 0, 0);
//	motorController.Config_IntegralZone(0, 300, 0);
	motorController.SetSensorPhase(false);
	motorController.SetSelectedSensorPosition(0,0,0);

//	motorController.ConfigPeakOutputForward(1.00, 0);
//	motorController.ConfigPeakOutputReverse(-1.00, 0);
//	motorController.ConfigPeakCurrentLimit(5, 0);

//	motorController.ConfigAllowableClosedloopError(0, 128, 0);
//	motorController.ConfigClosedloopRamp(0, 0);
}

bool LiftAndShuttleSubsystem::IsShuttleAtPosition()
{
  // actually check position is at target position
  int currentPosition = m_leftShuttle.GetSelectedSensorPosition(0);

  return fabs(currentPosition - m_targetShuttlePosition) < kCloseEnoughToPosition;
}

void LiftAndShuttleSubsystem::MoveShuttleToPosition(double position)
{
  m_leftShuttle.Set(ctre::phoenix::motorcontrol::ControlMode::Position, position);
  m_rightShuttle.Set(ctre::phoenix::motorcontrol::ControlMode::Position, position);
  m_targetShuttlePosition = position;
}

void LiftAndShuttleSubsystem::ShuttleMiddle()
{
  // move to middle shuttle position
  MoveShuttleToPosition(kShuttleMiddlePosition);
}

void LiftAndShuttleSubsystem::ShuttleFront()
{
  // move to the front shuttle position
  MoveShuttleToPosition(kShuttleFrontPosition);
}

void LiftAndShuttleSubsystem::ShuttleRear()
{
  // move to the rear shuttle position
  MoveShuttleToPosition(kShuttleRearPosition);
}

void LiftAndShuttleSubsystem::ShuttleStopAtCurrentPosition()
{
  int currentPosition = m_leftShuttle.GetSelectedSensorPosition(0);
  MoveShuttleToPosition(currentPosition);
}