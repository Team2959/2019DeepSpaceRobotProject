/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
//#include "frc/Solenoid.h"
#include "frc/Talon.h"
#include "frc/Spark.h"
#include "RobotMap.h"

class CargoArmSubsystem : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  frc::Spark m_wheels {kCargoArmWheelsMotorPWM};
  frc::Talon m_armExtendRight {kRightCargoArmExtendTalonSRX};
  frc::Talon m_armExtendLeft {kLeftCargoArmExtendTalonSRX};

 public:
  CargoArmSubsystem();

  void ExtendForward(); 
   void ExtendBackward();
  void Retract();
  void WheelsOn();
  void WheelsOff();
};
