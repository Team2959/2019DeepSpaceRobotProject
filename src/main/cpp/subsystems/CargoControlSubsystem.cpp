/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoControlSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>

constexpr double kWheelPickupSpeed = 0.35;
constexpr double kWheelDeliverSpeed = 1;

CargoControlSubsystem::CargoControlSubsystem() : Subsystem("CargoControlSubsystem")
{
  m_wheelPickupSpeed = kWheelPickupSpeed;
  m_wheelDeliverSpeed = kWheelDeliverSpeed;
}

void CargoControlSubsystem::OnRobotInit()
{
  StopWheels();
  
  frc::SmartDashboard::PutBoolean("Cargo", false);

  DashboardDebugInit();
}

void CargoControlSubsystem::OnRobotPeriodic(bool updateDebugInfo)
{
  frc::SmartDashboard::PutBoolean("Cargo", !m_cargoIn.Get());

  if (updateDebugInfo)
    DashboardDebugPeriodic();
}

void CargoControlSubsystem::DashboardDebugInit()
{
  frc::SmartDashboard::PutData(this);

  frc::SmartDashboard::PutBoolean("Cargo Move", false);
  frc::SmartDashboard::PutNumber("Cargo Pickup Speed", kWheelPickupSpeed);
  frc::SmartDashboard::PutNumber("Cargo Deliver Speed", kWheelDeliverSpeed);
}

void CargoControlSubsystem::DashboardDebugPeriodic()
{
  auto start = frc::SmartDashboard::GetBoolean("Cargo Move", false);
  if (start && !CargoIn())
  {
    m_wheelPickupSpeed = frc::SmartDashboard::GetNumber("Cargo Pickup Speed", kWheelPickupSpeed);
    m_wheelDeliverSpeed = frc::SmartDashboard::GetNumber("Cargo Deliver Speed", kWheelDeliverSpeed);
    ChangeWheelsSpeed(m_wheelPickupSpeed);
  }
  else
  {
    StopWheels();
  }
}

bool CargoControlSubsystem::CargoIn() const
{
  return !m_cargoIn.Get();
}

void CargoControlSubsystem::MoveCargoBall(bool bFront, bool bDeliver)
{
  auto speed = m_wheelDeliverSpeed;
  if (bDeliver == false)
    speed = m_wheelPickupSpeed;
  
  if(bFront == false)
    speed *= -1;
  
  ChangeWheelsSpeed(speed);
}

void CargoControlSubsystem::StopWheels()
{
  ChangeWheelsSpeed(0);
}

void CargoControlSubsystem::ChangeWheelsSpeed(double speed)
{
  m_wheels.Set(speed);
}
