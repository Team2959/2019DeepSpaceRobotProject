/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ClimbSubsystem.h"

ClimbSubsystem::ClimbSubsystem() : Subsystem("ClimbSubsystem") {}

void ClimbSubsystem::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void ClimbSubsystem::HighClimbPosition()
{
    m_shifter.Set(frc::DoubleSolenoid::Value::kForward);
}

void ClimbSubsystem::LowClimbPosition()
{
    m_shifter.Set(frc::DoubleSolenoid::Value::kReverse);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
