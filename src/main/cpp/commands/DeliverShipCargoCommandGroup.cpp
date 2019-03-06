/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeliverShipCargoCommandGroup.h"
#include "commands/MoveLiftAndShuttleCommand.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include "commands/TiltCargoArmCommand.h"
#include "commands/MoveCargoBallCommand.h"

DeliverShipCargoCommandGroup::DeliverShipCargoCommandGroup() {
  AddSequential(new MoveLiftAndShuttleCommand(kLiftFloorPosition, 5000));
  AddSequential(new TiltCargoArmCommand());
  AddSequential(new MoveCargoBallCommand(true, true));
}
