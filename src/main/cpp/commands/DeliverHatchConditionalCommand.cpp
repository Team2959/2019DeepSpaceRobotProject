/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeliverHatchConditionalCommand.h"
#include "commands/DeliverHatchToCargoShipCommandGroup.h"
#include "commands/DeliverHatchToRocketCommandGroup.h"
#include "Robot.h"
#include "subsystems/LiftAndShuttlePositions.h"

DeliverHatchConditionalCommand::DeliverHatchConditionalCommand() : ConditionalCommand(
  new DeliverHatchToCargoShipCommandGroup(),
  new DeliverHatchToRocketCommandGroup())
{
}

bool DeliverHatchConditionalCommand::Condition()
{
  return Robot::m_liftAndShuttleSubsystem.IsLiftAtPosition(kLiftCargoShipPosition);
}
