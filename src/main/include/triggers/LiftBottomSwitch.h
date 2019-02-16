/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/buttons/Trigger.h>
#include <frc/DigitalInput.h>

#include "RobotMap.h"

class LiftBottomSwitch : public frc::Trigger {
private:
    frc::DigitalInput m_limitSwitch{kLiftBottomSwitch};

public:
    LiftBottomSwitch();
    bool Get() override;
};
