/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/FollowLineCommand.h"
#include "Robot.h"

FollowLineCommand::FollowLineCommand()
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_driveTrainSubsystem);
}

// Called just before this Command runs the first time
void FollowLineCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void FollowLineCommand::Execute() 
{
  double leftVelocityMultiplier = 1;//0.25;
  double rightVelocityMultiplier = 1;//0.25;

  bool seeWhite1 = Robot::m_driveTrainSubsystem.WhiteTape1();
  bool seeWhite2 = Robot::m_driveTrainSubsystem.WhiteTape2();
  bool seeWhite3 = Robot::m_driveTrainSubsystem.WhiteTape3();

  if(seeWhite1 == false && seeWhite2 == true && seeWhite3 == false)
  {
  }
  else if(seeWhite1 == false && seeWhite2 == true && seeWhite3 == true)
  {
      leftVelocityMultiplier = 0.5;//0.2;
  }
  else if(seeWhite1 == true && seeWhite2 == true && seeWhite3 == false)
  {
      rightVelocityMultiplier = 0.5;//.2;
  }

  else if(seeWhite1 == true && seeWhite2 == false && seeWhite3 == false)
  {
      rightVelocityMultiplier = .15;
  }

  else if(seeWhite1 == false && seeWhite2 == false && seeWhite3 == true)
  {
      leftVelocityMultiplier = .15;
  }
  else
  {
    // don't set a velocity
    return;
  }
  
  // set the velocity to drive train subsystem!
  auto maxSpeed = Robot::m_driveTrainSubsystem.GetMaxSpeed();
  Robot::m_driveTrainSubsystem.TankDrive(maxSpeed * leftVelocityMultiplier, maxSpeed * rightVelocityMultiplier);
}

// Make this return true when this Command no longer needs to run execute()
bool FollowLineCommand::IsFinished() { return false; }

// Called once after isFinished returns true
void FollowLineCommand::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowLineCommand::Interrupted()
{
  // stop the drive motors
  Robot::m_driveTrainSubsystem.TankDrive(0, 0);
}
