/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"
#include "RobotMap.h"

class LiftAndShuttleSubsystem : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  // Lift control
  rev::CANSparkMax m_liftPrimary { kLiftPrimaryCanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
  rev::CANSparkMax m_liftFollower1 { kLiftFollower1CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
  rev::CANSparkMax m_liftFollower2 { kLiftFollower2CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
  rev::CANPIDController m_liftPidController { m_liftPrimary };
  rev::CANEncoder m_liftEncoder { m_liftPrimary };

  // Lift methods
  bool IsLiftSafeForShuttleMoveThroughMiddle();
  double CurrentLiftPosition();
  void MoveLiftToPosition(double position);
  void LiftStopAtCurrentPosition();

  // Shuttle control
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX m_leftShuttle { kLeftCargoShuttleCanTalonSrxMotor };
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX m_rightShuttle { kRightCargoShuttleCanTalonSrxMotor };
  ctre::phoenix::motorcontrol::can::SlotConfiguration m_pidConfigShuttle;

  // Shuttle methods
  void MoveShuttleToPosition(double position);
  void ShuttleStopAtCurrentPosition();

  // Smart Dashboard debug/info
  void DashboardDataInit();

 public:
  LiftAndShuttleSubsystem();

  void OnRobotInit();

  bool IsShuttleAtPosition(double targetPosition);
  double CurrentShuttlePosition();

  bool IsLiftAtPosition(double targetPosition);

  // Movement Control Interface
  bool IsAtTargetPosition(double targetShuttlePosition, double targetLiftPosition);
  void StopAtCurrentPosition();
  void MoveToTargetPosition(double targetShuttlePosition, double targetLiftPosition, bool isShuttleArmSafe);

  // Smart Dashboard debug/info
  void DashboardData();
};
