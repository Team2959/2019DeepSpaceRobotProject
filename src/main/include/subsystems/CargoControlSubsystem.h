/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Spark.h>
#include <frc/DigitalInput.h>
#include "RobotMap.h"

class CargoControlSubsystem : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  frc::Spark m_wheels { kCargoArmWheelsPwmSparkMotor };
  frc::DigitalInput m_cargoIn { kCargoInSwitch };
  frc::DigitalInput m_cargoIn2 { kCargoIn2Switch };

  void ChangeWheelsSpeed(double speed);
  
  void DashboardDebugInit();
  void DashboardDebugPeriodic();

 public:
  CargoControlSubsystem();

  void OnRobotInit();
  void OnRobotPeriodic(bool updateDebugInfo);
 
  bool CargoIn() const;
  
  void CargoBallTowardsFront();
  void CargoBallTowardsRear();
  void StopWheels();
};
