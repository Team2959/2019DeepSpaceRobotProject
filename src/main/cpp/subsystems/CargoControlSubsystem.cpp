/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoControlSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>

CargoControlSubsystem::CargoControlSubsystem() : Subsystem("CargoControlSubsystem") {}

void CargoControlSubsystem::OnRobotInit()
{
  frc::SmartDashboard::PutBoolean("Cargo 1", false);
  frc::SmartDashboard::PutBoolean("Cargo 2", false);

  DashboardDebugInit();
}

void CargoControlSubsystem::OnRobotPeriodic()
{
  frc::SmartDashboard::PutBoolean("Cargo 1", !m_cargoIn.Get());
  frc::SmartDashboard::PutBoolean("Cargo 2", !m_cargoIn2.Get());

  DashboardDebugPeriodic();
}

void CargoControlSubsystem::DashboardDebugInit()
{
  frc::SmartDashboard::PutData(this);
}

void CargoControlSubsystem::DashboardDebugPeriodic()
{
}

bool CargoControlSubsystem::CargoIn() const
{
  return !m_cargoIn.Get() || !m_cargoIn2.Get();
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