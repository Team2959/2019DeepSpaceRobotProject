/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeliverConditionalCommand.h"
#include "commands/DeliverCargoCommandGroup.h"
#include "commands/DeliverHatchConditionalCommand.h"
#include "Robot.h"

DeliverConditionalCommand::DeliverConditionalCommand() : ConditionalCommand(
  new DeliverCargoCommandGroup(),
  new DeliverHatchConditionalCommand())
{
}

bool DeliverConditionalCommand::Condition()
{
  return Robot::m_cargoControlSubsystem.CargoIn();
}
