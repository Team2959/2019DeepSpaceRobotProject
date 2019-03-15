/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TiltCargoArmIfAtLiftPositionConditionalCommand.h"
#include "commands/MoveCargoArmCommand.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include "subsystems/CargoArmPositions.h"
#include "Robot.h"

TiltCargoArmIfAtLiftPositionConditionalCommand::TiltCargoArmIfAtLiftPositionConditionalCommand()
 : ConditionalCommand(new MoveCargoArmCommand(kArmTiltForwardPosition))
{ }

bool TiltCargoArmIfAtLiftPositionConditionalCommand::Condition()
{
  return false;//Robot::m_liftAndShuttleSubsystem.IsLiftAtPosition(kLiftCargoShipPosition);
}
