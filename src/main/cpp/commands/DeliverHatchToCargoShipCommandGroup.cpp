/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeliverHatchToCargoShipCommandGroup.h"
#include "commands/PrepForHatchCommand.h"
#include <frc/commands/TimedCommand.h>
#include "commands/MoveLiftDownForHatchCommand.h"
#include "commands/KeepPinsOutCommand.h"
#include "commands/AttachHatchToCargoShipCommand.h"
#include "commands/RetractHatchAtEndOfDeliveryCommand.h"

DeliverHatchToCargoShipCommandGroup::DeliverHatchToCargoShipCommandGroup()
{
  // Extend Safety
  AddSequential(new PrepForHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  // Extend Pins
  AddSequential(new AttachHatchToCargoShipCommand());
  AddSequential(new frc::TimedCommand(0.25));
  // Retract Pins
  AddSequential(new PrepForHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  // drop relative to current height
  AddSequential(new MoveLiftDownForHatchCommand());
  // Extend Pins
  AddSequential(new AttachHatchToCargoShipCommand());
  AddSequential(new frc::TimedCommand(0.25));
  // Retract Safety
  AddSequential(new KeepPinsOutCommand());
  AddSequential(new frc::TimedCommand(0.25));
  // Retract Everything
  AddSequential(new RetractHatchAtEndOfDeliveryCommand());
}
