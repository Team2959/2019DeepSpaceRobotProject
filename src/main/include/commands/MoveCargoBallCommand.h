/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>

class MoveCargoBallCommand : public frc::Command
{
private:
  bool m_bFront;
  bool m_bDeliver;

public:
  MoveCargoBallCommand(bool bFront = true, bool bDeliver = true);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
