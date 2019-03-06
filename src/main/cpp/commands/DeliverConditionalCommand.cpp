/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeliverConditionalCommand.h"
#include "commands/DeliverCargoCommandGroup.h"
#include "commands/DeliverHatchCommandGroup.h"
#include "commands/TiltCargoArmCommand.h"
#include "commands/MoveCargoBallCommand.h"
#include "commands/StopCargoControlWheelsCommand.h"
#include "commands/AttachHatchCommand.h"
#include "commands/ReleaseHatchCommand.h"
#include "commands/RetractMechanismCommand.h"
#include "commands/PrepForHatchCommand.h"
#include <frc/commands/TimedCommand.h>
#include "Robot.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include "subsystems/HatchSubsystem.h"

DeliverConditionalCommand::DeliverConditionalCommand() : ConditionalCommand(
  new DeliverCargoCommandGroup(),
  new DeliverHatchCommandGroup())
  { }

bool DeliverConditionalCommand::Condition()
{
  return Robot::m_cargoControlSubsystem.CargoIn();
}
