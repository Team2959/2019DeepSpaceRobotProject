/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>
#include "commands/ExtendCargoArmFrontCommand.h"
#include "commands/StopCargoControlWheelsCommand.h"
#include "commands/MoveCargoTowardFrontCommand.h"
#include "commands/MoveCargoTowardRearCommand.h"
#include "commands/CargoArmUpCommand.h"
#include "commands/ExtendCargoArmFrontCommand.h"
#include "commands/ExtendCargoArmRearCommand.h"

OI::OI()
 {
  // Process operator interface input here.

  m_cargoStop.WhenPressed(new StopCargoControlWheelsCommand(0.0));
  m_cargoTowardsFront.WhenPressed(new MoveCargoTowardFrontCommand());
  m_cargoTowardsRear.WhenPressed(new MoveCargoTowardRearCommand());

  m_cargoArmUp.WhenPressed(new CargoArmUpCommand());
  m_cargoArmFront.WhenPressed(new ExtendCargoArmFrontCommand());
  m_cargoArmRear.WhenPressed(new ExtendCargoArmRearCommand());

  m_cargoIn.WhenActive(new StopCargoControlWheelsCommand());
}
