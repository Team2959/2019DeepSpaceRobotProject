/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>
#include "subsystems/LiftAndShuttlePositions.h"
#include "subsystems/CargoArmPositions.h"
#include "commands/DeliverConditionalCommand.h"
#include "commands/MoveLiftCommand.h"
#include "commands/ExtendCargoArmCommand.h"
#include "commands/MoveCargoArmCommand.h"
#include "commands/EjectCargoCommandGroup.h"
#include "commands/GrabHatchCommandGroup.h"
#include "commands/LiftLimitSwitchBottomCommand.h"
#include "commands/ClimbCommandGroup.h"
#include "commands/StopCargoControlWheelsCommand.h"

#include "commands/AttachHatchCommand.h"
#include "commands/ReleaseHatchCommand.h"
#include "commands/RetractMechanismCommand.h"
#include "commands/PrepForHatchCommand.h"

#include "commands/FollowLineCommand.h"

OI::OI()
{ 
  // Driver Buttons
  m_deliver.WhenPressed(new DeliverConditionalCommand());
  // m_followLine.WhileHeld(new FollowLineCommand());

  // Co-Pilot Buttons
  // m_shuttleFront.WhenPressed(new ShuttleTargetCommand(true));
  // m_shuttleRear.WhenPressed(new ShuttleTargetCommand(false));

  m_liftFloor.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::Floor));
  m_liftBottom.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::Bottom));
  m_liftCargoShuttle.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::CargoShip));
  m_liftMiddleRocket.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::MiddleRocket));
  m_liftTopRocket.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::TopRocket));

  m_cargoArmExtend.WhenPressed(new ExtendCargoArmCommand());
  m_cargoArmBack.WhenPressed(new MoveCargoArmCommand(kArmTiltBackwardPosition));

  m_ejectCargo.WhenPressed(new EjectCargoCommandGroup());

  m_hatchFromLoadingStation.WhenPressed(new GrabHatchCommandGroup());

  // m_climb.WhenPressed(new ClimbCommandGroup());
  m_climb.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::GrabHatchFromWall));

  // Sensor Triggers
  m_cargoIn.WhenActive(new StopCargoControlWheelsCommand(1.0, -1.0, -0.2));
  m_liftLimitSwitch.WhenActive(new LiftLimitSwitchBottomCommand());
}
