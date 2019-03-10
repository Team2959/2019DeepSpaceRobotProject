/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeliverCargoCommandGroup.h"
#include "commands/MoveCargoConditionalCommand.h"
#include "commands/StopCargoControlWheelsCommand.h"
#include "commands/TiltCargoArmIfAtLiftPositionConditionalCommand.h"

DeliverCargoCommandGroup::DeliverCargoCommandGroup() 
{
  AddSequential(new TiltCargoArmIfAtLiftPositionConditionalCommand());
  AddSequential(new MoveCargoConditionalCommand());
  AddSequential(new StopCargoControlWheelsCommand());
}
