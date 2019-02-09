/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
#include "RobotMap.h"
#include "VelocityTankDrive.h"

class DriveTrainSubsystem : public frc::Subsystem
{
 private:
    const double kMotorMaxSpeed     = 5676.0;  // RPM
    const double kDriveSafetyFactor = 0.90;    // Multiplier for establishing reliable limits
    const double kRobotMaxAccel     = 2207.07; // RPM / s
    const double kDriveMaxCurrent   = 80.0;    // Amps
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
    rev::CANSparkMax m_rightPrimary  {kRight1CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_rightFollower {kRight2CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_leftPrimary   {kLeft1CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_leftFollower  {kLeft2CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};


  VelocityTankDrive m_tankDrive { m_left1Primary, m_right1Primary };

 public:
  DriveTrainSubsystem();
  void InitDefaultCommand() override;

  void MyTankDrive(double leftSpeed, double rightSpeed);
};
