/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>
#include "subsystems/LiftAndShuttlePositions.h"
#include "commands/DeliverCommandGroup.h"
#include "commands/ShuttleTargetCommand.h"
#include "commands/MoveLiftCommand.h"
#include "commands/ExtendCargoArmCommand.h"
#include "commands/CargoArmUpCommand.h"
#include "commands/EjectCargoCommandGroup.h"
#include "commands/GrabHatchCommandGroup.h"
#include "commands/ClimbCommandGroup.h"
#include "commands/StopCargoControlWheelsCommand.h"

OI::OI()
{
  // Driver Buttons
  m_deliver.WhenPressed(new DeliverCommandGroup());

  // Co-Pilot Buttons
  m_shuttleFront.WhenPressed(new ShuttleTargetCommand(true));
  m_shuttleRear.WhenPressed(new ShuttleTargetCommand(false));

  m_liftFloor.WhenPressed(new MoveLiftCommand(kLiftFloorPosition));
  m_liftBottom.WhenPressed(new MoveLiftCommand(kLiftBottomPosition));
  m_liftCargoShuttle.WhenPressed(new MoveLiftCommand(kLiftCargoShuttlePosition));
  m_liftMiddleRocket.WhenPressed(new MoveLiftCommand(kLiftMiddlePosition));
  m_liftTopRocket.WhenPressed(new MoveLiftCommand(kLiftTopPosition));

  m_cargoArmExtend.WhenPressed(new ExtendCargoArmCommand());
  m_cargoArmUp.WhenPressed(new CargoArmUpCommand());

  m_ejectCargo.WhenPressed(new EjectCargoCommandGroup());

  m_hatchFromLoadingStation.WhenPressed(new GrabHatchCommandGroup());

  m_climb.WhenPressed(new ClimbCommandGroup());

  // Sensor Triggers
  m_cargoIn.WhenActive(new StopCargoControlWheelsCommand());
}
