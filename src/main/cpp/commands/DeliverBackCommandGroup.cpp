/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeliverBackCommandGroup.h"
#include "commands/MoveCargoBallCommand.h"
#include "commands/OpenCargoControlForBackCommand.h"
#include "commands/RetractMechanismCommand.h"

DeliverBackCommandGroup::DeliverBackCommandGroup() {
  AddSequential(new OpenCargoControlForBackCommand());
  AddSequential(new MoveCargoBallCommand(false, true));
  AddSequential(new RetractMechanismCommand());
}
