/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoArmSubsystem.h"

constexpr int kArmUpPosition = 0;
constexpr int kArmFrontPosition = 2500;
constexpr int kArmRearPosition = -kArmFrontPosition;

CargoArmSubsystem::CargoArmSubsystem() : Subsystem("CargoArmSubsystem")
{
  // configure talons for position control
  // set PID values
  // Possibly have one side follow the other
}

bool CargoArmSubsystem::ArmAtPosition() const
{
  return true;
}

void CargoArmSubsystem::ArmUp()
{
  // move to up position
}

void CargoArmSubsystem::ArmExtendFront()
{
  // move to the front pickup position
}

void CargoArmSubsystem::ArmExtendRear()
{
  // move to the rear pickup position
}
