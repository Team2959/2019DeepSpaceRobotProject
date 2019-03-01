/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoControlSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>

constexpr double kWheelSpeed = 0.5;

CargoControlSubsystem::CargoControlSubsystem() : Subsystem("CargoControlSubsystem") {}

void CargoControlSubsystem::OnRobotInit()
{
  frc::SmartDashboard::PutBoolean("Cargo 1", false);
  frc::SmartDashboard::PutBoolean("Cargo 2", false);

  DashboardDebugInit();
}

void CargoControlSubsystem::OnRobotPeriodic(bool updateDebugInfo)
{
  frc::SmartDashboard::PutBoolean("Cargo 1", !m_cargoIn.Get());
  frc::SmartDashboard::PutBoolean("Cargo 2", !m_cargoIn2.Get());

  if (updateDebugInfo)
    DashboardDebugPeriodic();
}

void CargoControlSubsystem::DashboardDebugInit()
{
  frc::SmartDashboard::PutData(this);

  frc::SmartDashboard::PutBoolean("Cargo Move", false);
  frc::SmartDashboard::PutNumber("Cargo Speed", 0.5);
}

void CargoControlSubsystem::DashboardDebugPeriodic()
{
  auto start = frc::SmartDashboard::GetBoolean("Cargo Move", false);
  if (start && !CargoIn())
  {
    ChangeWheelsSpeed(-frc::SmartDashboard::GetNumber("Cargo Speed", 0.5));
  }
  else
  {
    StopWheels();
  }
}

bool CargoControlSubsystem::CargoIn() const
{
  return !m_cargoIn.Get() || !m_cargoIn2.Get();
}

void CargoControlSubsystem::CargoBallTowardsFront()
{
  ChangeWheelsSpeed(-kWheelSpeed);
}

void CargoControlSubsystem::CargoBallTowardsRear()
{
  ChangeWheelsSpeed(kWheelSpeed);
}

void CargoControlSubsystem::StopWheels()
{
  ChangeWheelsSpeed(0);
}

void CargoControlSubsystem::ChangeWheelsSpeed(double speed)
{
  m_wheels.Set(speed);
}
