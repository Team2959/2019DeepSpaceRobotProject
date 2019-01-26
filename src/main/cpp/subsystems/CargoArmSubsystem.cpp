/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoArmSubsystem.h"

CargoArmSubsystem::CargoArmSubsystem() : Subsystem("CargoArmSubsystem") {}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void CargoArmSubsystem::Extend()
{
  m_armExtend.Set(true);
  WheelsOn();
}

void CargoArmSubsystem::Retract()
{
  m_armExtend.Set(false);
  WheelsOff();
}

void CargoArmSubsystem::WheelsOn()
{
  m_wheels.Set(1);
}

void CargoArmSubsystem::WheelsOff()
{
  m_wheels.Set(0);
}