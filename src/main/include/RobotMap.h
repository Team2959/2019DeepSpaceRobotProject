/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
constexpr int kRight1CanSparkMaxMotor = 1;
constexpr int kRight2CanSparkMaxMotor = 2;
constexpr int kRight3CanSparkMaxMotor = 3;
constexpr int kLeft1CanSparkMaxMotor = 4;
constexpr int kLeft2CanSparkMaxMotor = 5;
constexpr int kLeft3CanSparkMaxMotor = 6;

constexpr int kCargoArmWheelsMotorPWM = 0;

constexpr int kCargoArmExtendSolenoid = 0;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;

constexpr int kDriverUSBController = 0;
