/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"
#include "RobotMap.h"

class CargoArmSubsystem : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX m_left { kLeftCargoArmCanTalonSrxMotor };
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX m_right { kRightCargoArmCanTalonSrxMotor };

  double m_targetPosition;

  void ConfigureMotorController(ctre::phoenix::motorcontrol::can::WPI_TalonSRX & motorController);
  void MoveCargoArmToPosition(double position);
  double CurrentArmPosition();

 public:
  CargoArmSubsystem();

  bool IsArmAtPosition();
  bool IsArmAboveCargoShuttle();

  void ArmUp();
  void ArmExtendFront();
  void ArmExtendRear();
  void StopAtCurrentPosition();
};
