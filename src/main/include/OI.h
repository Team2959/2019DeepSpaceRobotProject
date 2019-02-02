/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/XboxController.h>
#include <frc/Buttons/JoystickButton.h>
#include "RobotMap.h"
#include "triggers/CargoInTrigger.h"
#include "frc/Joystick.h"

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

  // triggers from robot digital inputs
  CargoInTrigger m_cargoIn;
};
