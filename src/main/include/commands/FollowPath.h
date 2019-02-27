/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <subsystems/DriveTrainSubsystem.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <deque>
#include <string>

enum VelocityUnits {
    kFeetPerSecond,
    kMetersPerSecond,
    kInchesPerSecond
};

class FollowPath : public frc::Command {
public:
    FollowPath(const std::string& path, VelocityUnits units);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
private:
    struct Trajectory {
        double elapsedTime;
        double rightVelocity;
        double leftVelocity;
        double heading;
    };

    std::string m_pathName;
    std::deque<Trajectory> m_trajectories;

    void   LoadPathFile ();
    void   SetUnitConversion (VelocityUnits v);
    double m_conversionFactor = (1 / (M_PI * kDriveTrainWheelSize)) * 60;
};
