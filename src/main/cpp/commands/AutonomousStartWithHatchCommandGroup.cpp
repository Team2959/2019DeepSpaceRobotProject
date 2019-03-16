/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutonomousStartWithHatchCommandGroup.h"
#include "commands/MoveLiftAndShuttleCommand.h"
#include "commands/PrepForHatchCommand.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include "commands/RetractMechanismCommand.h"
#include <frc/commands/TimedCommand.h>

AutonomousStartWithHatchCommandGroup::AutonomousStartWithHatchCommandGroup()
{
  AddSequential(new PrepForHatchCommand());
  AddSequential(new frc::TimedCommand(0.25));
  AddSequential(new MoveLiftAndShuttleCommand(kLiftCargoShipHatchPosition));
  AddSequential(new RetractMechanismCommand());
}
