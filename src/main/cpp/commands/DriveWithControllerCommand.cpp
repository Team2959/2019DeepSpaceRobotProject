/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveWithControllerCommand.h"
#include "Robot.h"

DriveWithControllerCommand::DriveWithControllerCommand()
{
    // Use Requires() here to declare subsystem dependencies
    // eg. Requires(Robot::chassis.get());
    Requires(&Robot::m_driveTrainSubsystem);
}

// Called just before this Command runs the first time
void DriveWithControllerCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveWithControllerCommand::Execute()
{
    Robot::m_driveTrainSubsystem.TankDrive(
        Robot::m_oi.m_driverJoystick.GetY(frc::GenericHID::JoystickHand::kLeftHand),
        Robot::m_oi.m_driverJoystick.GetY(frc::GenericHID::JoystickHand::kRightHand)
    );
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithControllerCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveWithControllerCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithControllerCommand::Interrupted() {}
