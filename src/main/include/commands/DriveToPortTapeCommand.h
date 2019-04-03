/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <networktables/NetworkTable.h>
#include "subsystems/DriveTrainSubsystem.h"

class DriveToPortTapeCommand : public frc::Command
{
  public:
    DriveToPortTapeCommand();
    virtual void Initialize() override;
    virtual void Execute() override;
    virtual bool IsFinished() override;
    virtual void End() override;
    virtual void Interrupted() override;

  private:
    std::tuple<double, double> ComputeRpms(double leftTapeX, double rightTapeX);

    void LookForTape(bool flag);
    void StopDriveMotion();

    std::shared_ptr<nt::NetworkTable> m_networkTable;
    bool                              m_isFinished{ false };

    double m_accelDecel;
    double m_separationLimit;
    double m_maxForwardSpeed;
    double m_maxRotationSpeed;
    double m_currentLeftSpeed;
    double m_currentRightSpeed;
};
