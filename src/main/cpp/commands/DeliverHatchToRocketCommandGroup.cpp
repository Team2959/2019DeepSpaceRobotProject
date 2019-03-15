/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeliverHatchToRocketCommandGroup.h"
#include "commands/AttachHatchCommand.h"
#include "commands/ReleaseHatchCommand.h"
#include "commands/RetractMechanismCommand.h"
#include <frc/commands/TimedCommand.h>
#include "commands/MoveLiftDownForHatchCommand.h"
#include "commands/KeepPinsOutCommand.h"

DeliverHatchToRocketCommandGroup::DeliverHatchToRocketCommandGroup()
{
  // extend safety and attach mechanisms
  AddSequential(new AttachHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  // extend pins
  AddSequential(new ReleaseHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  // retract pins
  AddSequential(new AttachHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  // drop relative to current height
  AddSequential(new MoveLiftDownForHatchCommand());
  // extend pins
  AddSequential(new ReleaseHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  // Retract safety and attatch mechanisms
  AddSequential(new KeepPinsOutCommand());
  AddSequential(new frc::TimedCommand(0.25));
  // Retract pins
  AddSequential(new RetractMechanismCommand());
}
