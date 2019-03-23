/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Solenoid.h>
#include "RobotMap.h"

class HatchSubsystem : public frc::Subsystem {
 private:
  frc::Solenoid m_attach  {kHatchAttachSolenoid};
  frc::Solenoid m_release {kHatchReleaseSolenoid};
  frc::Solenoid m_safety  {kHatchSafetySolenoid};

 public:
  HatchSubsystem();

  void OnRobotInit();
  void OnRobotPeriodic(bool updateDebugInfo);

  void PrepForHatch();
  void AttachHatch();
  void ReleaseHatch();
  void RetractMechanism();
  void KeepPinsOut();
  void AttachHatchToCargoShip();
};
