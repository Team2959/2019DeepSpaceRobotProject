/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ResetCargoArmCommandEndCommand.h"

#include "subsystems/CargoArmSubsystem.h"
#include "commands/ResetCargoArmCommand.h"
#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"
#include "RobotMap.h"
#include "Robot.h"
#include "OI.h"
#include "frc/buttons/Button.h"

#include <iostream>

ResetCargoArmCommandEndCommand::ResetCargoArmCommandEndCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ResetCargoArmCommandEndCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ResetCargoArmCommandEndCommand::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ResetCargoArmCommandEndCommand::IsFinished() { return true; }

// Called once after isFinished returns true
void ResetCargoArmCommandEndCommand::End() {

    Robot::m_cargoArmSubsystem.StopAndZero();
  Robot::m_cargoArmSubsystem.SetArmCurrentLimitHigh();

  std::cout << "ResetCargoArmCommandFinished" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetCargoArmCommandEndCommand::Interrupted() {}
