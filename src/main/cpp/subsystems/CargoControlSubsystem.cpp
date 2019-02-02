/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoControlSubsystem.h"

CargoControlSubsystem::CargoControlSubsystem() : Subsystem("CargoControlSubsystem") {}

bool CargoControlSubsystem::CargoIn() const
{
  return m_cargoIn.Get();
}

void CargoControlSubsystem::CargoBallTowardsFront()
{
  ChangeWheelsSpeed(1);
}

void CargoControlSubsystem::CargoBallTowardsRear()
{
  ChangeWheelsSpeed(-1);
}

void CargoControlSubsystem::StopWheels()
{
  ChangeWheelsSpeed(0);
}

void CargoControlSubsystem::ChangeWheelsSpeed(double speed)
{
  m_wheels.Set(speed);
}