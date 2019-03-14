/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TiltCargoArmBackCommand.h"


TiltCargoArmBackCommand::TiltCargoArmBackCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
   Requires(&Robot::m_cargoArmSubsystem);
  Requires(&Robot::m_cargoControlSubsystem);
}

// Called just before this Command runs the first time
void TiltCargoArmBackCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TiltCargoArmBackCommand::Execute() 
{
  Robot::m_cargoControlSubsystem.ChangeWheelsSpeed(-0.3);
  Robot::m_cargoArmSubsystem.MoveCargoArmToPosition(kArmTiltBackwardPosition);

}

// Make this return true when this Command no longer needs to run execute()
bool TiltCargoArmBackCommand::IsFinished()
 { 
     return Robot::m_cargoArmSubsystem.IsArmAtPosition(kArmUpPosition);
 }

// Called once after isFinished returns true
void TiltCargoArmBackCommand::End()
 {
   Robot::m_cargoControlSubsystem.ChangeWheelsSpeed(-0.2);
 }

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TiltCargoArmBackCommand::Interrupted()
 {
    Robot::m_cargoArmSubsystem.StopAtCurrentPosition();
    End();
  }
