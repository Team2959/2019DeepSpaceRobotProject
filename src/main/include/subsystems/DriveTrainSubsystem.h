/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
#include <frc/Drive/DifferentialDrive.h>
#include "RobotMap.h"

class DriveTrainSubsystem : public frc::Subsystem
{
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  rev::CANSparkMax m_right1Primary { kRight1CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
  rev::CANSparkMax m_right2Follower { kRight2CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
  rev::CANSparkMax m_right3Follower { kRight3CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
  rev::CANSparkMax m_left1Primary { kLeft1CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
  rev::CANSparkMax m_left2Follower { kLeft2CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
  rev::CANSparkMax m_left3Follower { kLeft3CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };

  frc::DifferentialDrive m_tankDrive { m_left1Primary, m_right1Primary };

 public:
  DriveTrainSubsystem();
  void InitDefaultCommand() override;

  void MyTankDrive(double leftSpeed, double rightSpeed);
};
