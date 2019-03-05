/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>
#include "RobotMap.h"
#include "triggers/CargoInTrigger.h"
#include "triggers/LiftBottomSwitch.h"
#include "triggers/ShuttleFrontLimitTrigger.h"
#include "triggers/ShuttleRearLimitTrigger.h"

class OI
{
public:
  OI();

  // USB connections
  frc::Joystick m_leftDriverJoystick { kLeftDriverUSBController };
  frc::Joystick m_rightDriverJoystick { kRighttDriverUSBController };
  frc::Joystick m_coPilotJoystick { kCoPilotUSBController };

  bool m_shuttleTargetFront;

private:
  // Driver buttons
  //Right
  frc::JoystickButton m_deliver { &m_rightDriverJoystick, 1};
  frc::JoystickButton m_followLine { &m_rightDriverJoystick, 2};

  // Co Pilot Buttons
  frc::JoystickButton m_shuttleFront { &m_coPilotJoystick, 1};
  frc::JoystickButton m_shuttleRear { &m_coPilotJoystick, 2};

  frc::JoystickButton m_liftFloor { &m_coPilotJoystick, 3};
  frc::JoystickButton m_liftBottom { &m_coPilotJoystick, 4};
  frc::JoystickButton m_liftCargoShuttle { &m_coPilotJoystick, 5};
  frc::JoystickButton m_liftMiddleRocket { &m_coPilotJoystick, 6};
  frc::JoystickButton m_liftTopRocket { &m_coPilotJoystick, 7};

  frc::JoystickButton m_cargoArmExtend { &m_coPilotJoystick, 8};
  frc::JoystickButton m_cargoArmUp {&m_coPilotJoystick, 9};

  frc::JoystickButton m_ejectCargo {&m_coPilotJoystick, 10};

  frc::JoystickButton m_hatchFromLoadingStation {&m_coPilotJoystick, 11};

  frc::JoystickButton m_climb {&m_coPilotJoystick, 12};

  // triggers from robot digital inputs
  CargoInTrigger m_cargoIn;
  LiftBottomSwitch m_liftLimitSwitch;
  ShuttleFrontLimitTrigger m_shuttleFrontSwitch;
  ShuttleRearLimitTrigger m_shuttleBackSwitch;
};
