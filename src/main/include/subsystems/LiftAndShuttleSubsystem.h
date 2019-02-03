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

  // Shuttle control
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX m_leftShuttle { kLeftCargoShuttleCanTalonSrxMotor };
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX m_rightShuttle { kRightCargoShuttleCanTalonSrxMotor };

  double m_targetShuttlePosition;

  void ConfigureTalonMotorController(ctre::phoenix::motorcontrol::can::WPI_TalonSRX & motorController);
  void MoveShuttleToPosition(double position);
  
 public:
  LiftAndShuttleSubsystem();

  // Shuttle methods
  bool IsShuttleAtPosition();

  void ShuttleMiddle();
  void ShuttleFront();
  void ShuttleRear();
  void ShuttleStopAtCurrentPosition();

  // Lift methods
};
