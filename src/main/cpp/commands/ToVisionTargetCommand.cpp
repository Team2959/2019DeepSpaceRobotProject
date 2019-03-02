/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToVisionTargetCommand.h"

ToVisionTargetCommand::ToVisionTargetCommand() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::m_driveTrainSubsystem);
  Requires(Robot::m_networkTable);
}

// Called just before this Command runs the first time
void ToVisionTargetCommand::Initialize() 
{
    m_networkTable.setDouble(Rpi2959Shared::Keys::FrontTargets, Rpi2959Shared::ProcessingTargets::PortTape); 
    m_isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void ToVisionTargetCommand::Execute()
{
  auto Results = m_networkTable->GetNumberArray(Rpi2959Shared::Keys::FrontPortTapeResults, std::vector<double>{});

  if(Results.size() == 0)
  {
    return;
  }
    auto  LeftX = Results[0];   // in [0,1]
   auto  RightX = Results[1];
   auto Middle = (RightX + LeftX) / 2;
   auto result = ComputeRpms(Middle);
   Robot::m_driveTrainSubsystem.TankDrive(std::get<0>(result),std::get<1>(result));
  
}

  std::tuple<double, double> ToVisionTargetCommand::ComputeRpms(double middle)
  {
   if(Middle > 0.55)
  {
      //Turn right
      //Can change speed with testing
      return std::make_tuple(0.1,-0.1);
  }
  else if(Middle < 0.45)
  {
          //Turn left
      return std::make_tuple(-0.1,0.1);
  }
  else
  {
      m_isFinished = true;
      return std::make_tuple(0,0);
  }

  }

// Make this return true when this Command no longer needs to run execute()
bool ToVisionTargetCommand::IsFinished() { return m_isFinished; }

// Called once after isFinished returns true
void ToVisionTargetCommand::End() 
{
   m_networkTable.setDouble(Rpi2959Shared::Keys::FrontTargets, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToVisionTargetCommand::Interrupted() {}
