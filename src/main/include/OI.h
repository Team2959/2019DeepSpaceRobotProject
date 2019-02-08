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

class OI
{
 public:
  OI();
  
  frc::XboxController m_driverJoystick { kDriverUSBController };
  frc::Joystick m_coPilotJoystick { 2 };

  frc::JoystickButton m_prepForHatch {&m_coPilotJoystick, 5};
  frc::JoystickButton m_secureHatch {&m_coPilotJoystick, 1};
  frc::JoystickButton m_attachHatch {&m_coPilotJoystick, 2};
  frc::JoystickButton m_releaseHatch {&m_coPilotJoystick, 3};
  frc::JoystickButton m_retractMechanismHatch {&m_coPilotJoystick, 4};
};
