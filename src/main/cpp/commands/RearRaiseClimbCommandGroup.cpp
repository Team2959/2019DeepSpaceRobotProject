/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RearRaiseClimbCommandGroup.h"
#include "Robot.h"
#include "commands/ClimbSolenoidEngageCommand.h"
#include "commands/RaiseBotBaseToClimbCommand.h"

RearRaiseClimbCommandGroup::RearRaiseClimbCommandGroup()
{
  AddSequential(new RaiseBotBaseToClimbCommand());
  AddSequential(new ClimbSolenoidEngageCommand());
}

void RearRaiseClimbCommandGroup::Interrupted()
{
  End();
}

void RearRaiseClimbCommandGroup::End()
{
  Robot::m_climbSubsystem.ClimbSolenoidDisengage();
}
