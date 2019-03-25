/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Solenoid.h>
#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"
#include "RobotMap.h"

constexpr double kClimbWheelsHoldingCurrent = 1;
constexpr double kDriveClimbWheelsDistance = 700;
constexpr double kDriveCloseEnoughToPosition = 0.1;

class ClimbSubsystem : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  frc::Solenoid m_climbEngage {kClimbEngageSolenoid};
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX m_left { kLeftClimbCanTalonSrxMotor };
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX m_right { kRightClimbCanTalonSrxMotor };
  ctre::phoenix::motorcontrol::can::SlotConfiguration m_pidConfig;

  // Smart Dashboard debug/info
  bool m_updateDebugInfo = false;
  void DashboardDebugPeriodic();

 public:
  ClimbSubsystem();

  void OnRobotInit();
  void OnRobotPeriodic(bool updateDebugInfo);

  void ClimbWheelsSetPosition(double position);
  void ClimbSolenoidEngage();
  void ClimbSolenoidDisengage();
  void PowerToClimbWheels();
  void StopAtCurrentDistance();

  bool AreClimbWheelsAtPosition(double position);

  double CurrentClimbWheelsPosition();
};
