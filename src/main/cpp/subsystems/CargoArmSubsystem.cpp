/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoArmSubsystem.h"

constexpr int kArmUpPosition = 0;
constexpr int kArmFrontPosition = 5000;
constexpr int kArmRearPosition = -kArmFrontPosition;
constexpr int kCloseEnoughToPosition = 100;
constexpr int kArmIsClearOfShuttle = 4000;

CargoArmSubsystem::CargoArmSubsystem() : Subsystem("CargoArmSubsystem")
{
  ConfigureMotorController(m_left);
  ConfigureMotorController(m_right);

  ArmUp();
}

void CargoArmSubsystem::ConfigureMotorController(
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

double CargoArmSubsystem::CurrentArmPosition()
{
  // actually check position is at target position
  return m_left.GetSelectedSensorPosition(0);
}

bool CargoArmSubsystem::IsArmAtPosition()
{
  return fabs(CurrentArmPosition() - m_targetPosition) < kCloseEnoughToPosition;
}

bool CargoArmSubsystem::IsArmAboveCargoShuttle()
{
  return fabs(CurrentArmPosition()) < kArmIsClearOfShuttle;
}

void CargoArmSubsystem::MoveCargoArmToPosition(double position)
{
  m_left.Set(ctre::phoenix::motorcontrol::ControlMode::Position, position);
  m_right.Set(ctre::phoenix::motorcontrol::ControlMode::Position, position);
  m_targetPosition = position;
}

void CargoArmSubsystem::ArmUp()
{
  // move to up position
  MoveCargoArmToPosition(kArmUpPosition);
}

void CargoArmSubsystem::ArmExtendFront()
{
  // move to the front pickup position
  MoveCargoArmToPosition(kArmFrontPosition);
}

void CargoArmSubsystem::ArmExtendRear()
{
  // move to the rear pickup position
  MoveCargoArmToPosition(kArmRearPosition);
}

void CargoArmSubsystem::StopAtCurrentPosition()
{
  MoveCargoArmToPosition(CurrentArmPosition());
}