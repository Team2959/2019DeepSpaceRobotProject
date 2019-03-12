/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/GrabHatchCommandGroup.h"
#include "commands/PrepForHatchCommand.h"
#include "commands/RetractMechanismCommand.h"
#include "commands/MoveLiftCommand.h"
#include <frc/commands/TimedCommand.h>

GrabHatchCommandGroup::GrabHatchCommandGroup()
{
  AddSequential(new PrepForHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  //     lift up + x from current position to get hatch out of brushes on wall));
  AddSequential(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::RaiseHatchFromWall, true));
  AddSequential(new RetractMechanismCommand());
}
