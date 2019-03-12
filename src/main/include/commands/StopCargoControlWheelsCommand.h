/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/TimedCommand.h>

class StopCargoControlWheelsCommand : public frc::TimedCommand {
 private:
  double m_targetSpeedEnd;
  double m_targetSpeedSwitch;

 public:
  StopCargoControlWheelsCommand(double timeout = 0.1,
    double targetSpeedSwitch = 0,
    double targetSpeedEnd = 0);
  
  void Initialize() override;
  void Execute() override;
  void End() override;
  void Interrupted() override;
};
