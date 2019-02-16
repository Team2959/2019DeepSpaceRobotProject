/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "triggers/LiftBottomSwitch.h"
#include "Robot.h"

LiftBottomSwitch::LiftBottomSwitch() {}

bool LiftBottomSwitch::Get()
{
    return Robot::m_liftAndShuttleSubsystem.IsLiftAtBottom();
}
