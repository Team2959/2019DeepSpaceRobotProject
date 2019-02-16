/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/XboxController.h>
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
  frc::XboxController m_driverJoystick { kDriverUSBController };
  frc::Joystick m_coPilotJoystick { kCoPilotUSBController };

  // Driver buttons

  // Co Pilot Buttons
  frc::JoystickButton m_cargoTowardsFront { &m_coPilotJoystick, 1};
  frc::JoystickButton m_cargoTowardsRear { &m_coPilotJoystick, 2};
  frc::JoystickButton m_cargoStop { &m_coPilotJoystick, 3};

  frc::JoystickButton m_cargoArmUp {&m_coPilotJoystick, 4};
  frc::JoystickButton m_cargoArmFront {&m_coPilotJoystick, 5};
  frc::JoystickButton m_cargoArmRear {&m_coPilotJoystick, 6};
  
  frc::JoystickButton m_prepForHatch {&m_coPilotJoystick, 7};
  frc::JoystickButton m_secureHatch {&m_coPilotJoystick, 8};
  frc::JoystickButton m_attachHatch {&m_coPilotJoystick, 9};

  frc::JoystickButton m_liftAndShuttleToTopFront { &m_coPilotJoystick, 7 };

  // triggers from robot digital inputs
  CargoInTrigger m_cargoIn;
  LiftBottomSwitch m_liftLimitSwitch;
  ShuttleFrontLimitTrigger m_shuttleFrontSwitch;
  ShuttleRearLimitTrigger m_shuttleBackSwitch;


};
