/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "utilities/conditioning.h"

class FieldCentricJoystickDrive : public frc::Command {
private:
    struct JoystickVector {
        double magnitude;
        double heading;
    };

    double m_twistMultiplier = 3;
    cwtech::UniformConditioning jsc;

    double TrigAngleToRobotHeading (double angle);
    double ShortestAngle (double target, double current);
    struct JoystickVector ProcessJoystick (double x, double y);

public:
    FieldCentricJoystickDrive();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
