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
    static std::tuple<double, double> ComputeRpms(double leftTapeX, double rightTapeX);

    void LookForTape(bool flag);
    void StopDriveMotion();

    std::shared_ptr<nt::NetworkTable> m_networkTable;
    DriveTrainSubsystem&              m_driveTrainSubsystem;
    bool                              m_isFinished{ false };
};
