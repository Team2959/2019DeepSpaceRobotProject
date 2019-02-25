/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <networktables/NetworkTableInstance.h>

#include "OI.h"
#include "commands/MyAutoCommand.h"
#include "subsystems/DriveTrainSubsystem.h"
#include "subsystems/HatchSubsystem.h"
#include "subsystems/CargoControlSubsystem.h"
#include "subsystems/CargoArmSubsystem.h"
#include "subsystems/LiftAndShuttleSubsystem.h"

class Robot : public frc::TimedRobot {
 public:
  // Define all the subsystems to create here!
  static DriveTrainSubsystem m_driveTrainSubsystem;
  static HatchSubsystem m_hatchSubsystem;
  static CargoControlSubsystem m_cargoControlSubsystem;
  static CargoArmSubsystem m_cargoArmSubsystem;
  static LiftAndShuttleSubsystem m_liftAndShuttleSubsystem;

  static OI m_oi;

  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc::Command* m_autonomousCommand = nullptr;
  MyAutoCommand m_myAuto;
  frc::SendableChooser<frc::Command*> m_chooser;
  std::shared_ptr<nt::NetworkTable> m_networkTable;

  int m_periodic = 0;
  bool m_debugDrive = false;
  bool m_debugLiftAndShuttle = false;
  bool m_debugCargoArm = false;
  bool m_debugCargoControl = false;
  bool m_debugHatch = false;
};
