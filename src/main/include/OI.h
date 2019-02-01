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

class OI
{

 public:
  OI();
  
  frc::XboxController m_driverJoystick { kDriverUSBController };
  frc::JoystickButton m_cargoArmExtend { &m_driverJoystick, 1};
};
