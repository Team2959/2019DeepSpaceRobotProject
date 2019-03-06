/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveCargoConditionalCommand.h"
#include "commands/MoveCargoBallCommand.h"
#include "commands/DeliverBackCommandGroup.h"
#include "Robot.h"

MoveCargoConditionalCommand::MoveCargoConditionalCommand() : ConditionalCommand(
  new MoveCargoBallCommand(true, true),
  new DeliverBackCommandGroup()) {
}

bool MoveCargoConditionalCommand::Condition()
{
  return Robot::m_liftAndShuttleSubsystem.CurrentShuttlePosition()>=0;
}
