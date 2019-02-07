/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrainSubsystem.h"
#include "commands/DriveWithControllerCommand.h"

DriveTrainSubsystem::DriveTrainSubsystem() : Subsystem("DriveTrainSubsystem") {
  m_right2Follower.Follow(m_right1Primary);
  m_left2Follower.Follow(m_left1Primary);
}

void DriveTrainSubsystem::InitDefaultCommand() {
 SetDefaultCommand(new DriveWithControllerCommand());
 
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrainSubsystem::MyTankDrive(double leftSpeed, double rightSpeed){
  m_tankDrive.TankDrive(leftSpeed, rightSpeed);
}