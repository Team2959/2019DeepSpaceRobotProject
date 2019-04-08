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
#include "subsystems/CargoControlSubsystem.h"
#include "commands/ResetCargoArmCommand.h"
#include "commands/RaiseBotBaseToClimbCommand.h"
#include "subsystems/ClimbSubsystem.h"
#include "commands/PowerClimbWheelsWhileHeldCommand.h"
#include "commands/DriveToPortTapeCommand.h"
#include "commands/ToggleClimbSolenoidCommand.h"

OI::OI()
{ 
  // Driver Buttons
  m_deliver.WhenPressed(new DeliverConditionalCommand());
  // m_followLine.WhileHeld(new FollowLineCommand());
  m_resetCargoArm.WhileHeld(new ResetCargoArmCommand());
  m_moveClimbArms.WhileHeld(new PowerClimbWheelsWhileHeldCommand(kClimbWheelsDriveCurrent));
  //m_driveToVision.WhileHeld(new DriveToPortTapeCommand());


  // Co-Pilot Buttons
  m_climbHabLevel2.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::ClimbHab2));
  m_climbSolenoidToggle.WhenPressed(new ToggleClimbSolenoidCommand());
  m_climbRaiseBotBase.WhenPressed(new RaiseBotBaseToClimbCommand());
  //m_climbHabLevel2.WhenPressed(new ClimbCommandGroup(ClimbCommandGroup::TargetHabLevel::HabLevel2));
  //m_climbHabLevel3.WhenPressed(new ClimbCommandGroup(ClimbCommandGroup::TargetHabLevel::HabLevel3));

  m_liftFloor.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::Floor));
  m_liftBottom.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::Bottom));
  m_liftCargoShuttle.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::CargoShip));
  m_liftMiddleRocket.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::MiddleRocket));
  m_liftTopRocket.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::TopRocket));

  m_cargoArmExtend.WhenPressed(new ExtendCargoArmCommand());
  m_cargoArmBack.WhenPressed(new MoveCargoArmCommand(kArmTiltBackwardPosition));

//   m_ejectCargo.WhenPressed(new EjectCargoCommandGroup());
  // m_ejectCargo.WhenPressed(new StopCargoControlWheelsCommand(0, 0, 0));

  m_hatchFromLoadingStation.WhenPressed(new GrabHatchCommandGroup());
  m_liftHatchPickup.WhenPressed(new MoveLiftCommand(MoveLiftCommand::LiftTargetLevel::GrabHatchFromWall));

  // Sensor Triggers
  m_cargoIn.WhenActive(new StopCargoControlWheelsCommand(1.0, -1.0, kHoldCargoSpeed));
  m_liftLimitSwitch.WhenActive(new LiftLimitSwitchBottomCommand());
}
