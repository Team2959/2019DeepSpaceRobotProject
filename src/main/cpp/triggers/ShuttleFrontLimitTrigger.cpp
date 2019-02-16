/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "triggers/ShuttleFrontLimitTrigger.h"
#include "Robot.h"

ShuttleFrontLimitTrigger::ShuttleFrontLimitTrigger() {}

bool ShuttleFrontLimitTrigger::Get()
{
    return Robot::m_liftAndShuttleSubsystem.IsAtShuttleFrontLimit();
}
