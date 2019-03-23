/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbCommandGroup.h"
#include "commands/MoveLiftCommand.h"
#include "commands/MoveCargoArmCommand.h"
#include "subsystems/CargoArmPositions.h"
#include "commands/EngageClimbSolenoidCommand.h"
#include "commands/PowerToClimbWheelsCommand.h"

#include <frc/commands/TimedCommand.h>

ClimbCommandGroup::ClimbCommandGroup(TargetHabLevel targetLevel)
{
  AddParallel(new MoveCargoArmCommand(kArmTiltBackwardPosition));
  if (targetLevel == TargetHabLevel::HabLevel2){
        AddSequential(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::ClimbHab2));
  }else{
        AddSequential(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::ClimbHab3));
  }
  AddSequential(new EngageClimbSolenoidCommand());
  AddSequential(new frc::TimedCommand(0.25));
  AddSequential(new MoveCargoArmCommand(kArmExtendPosition));
  AddSequential(new PowerToClimbWheelsCommand());
  AddSequential(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::Floor));
}
