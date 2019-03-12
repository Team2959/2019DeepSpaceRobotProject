/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeliverHatchCommandGroup.h"
#include "commands/AttachHatchCommand.h"
#include "commands/ReleaseHatchCommand.h"
#include "commands/RetractMechanismCommand.h"
#include <frc/commands/TimedCommand.h>
#include "commands/MoveLiftCommand.h"
#include "commands/KeepPinsOutCommand.h"

DeliverHatchCommandGroup::DeliverHatchCommandGroup()
{
  AddSequential(new AttachHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  AddSequential(new ReleaseHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  AddSequential(new AttachHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  AddSequential(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::Floor, true));
  AddSequential(new ReleaseHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  AddSequential(new KeepPinsOutCommand());
  AddSequential(new frc::TimedCommand(0.25));
  AddSequential(new RetractMechanismCommand());
}
