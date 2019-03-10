/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TiltCargoArmIfAtLiftPositionConditionalCommand.h"
#include "commands/TiltCargoArmCommand.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include "Robot.h"

TiltCargoArmIfAtLiftPositionConditionalCommand::TiltCargoArmIfAtLiftPositionConditionalCommand()
 : ConditionalCommand(new TiltCargoArmCommand())
{ }

bool TiltCargoArmIfAtLiftPositionConditionalCommand::Condition()
{
  return Robot::m_liftAndShuttleSubsystem.IsLiftAtPosition(kLiftCargoShipPosition);
}
