/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "Robot.h"
#include "subsystems/CargoArmPositions.h"
#include <frc/commands/Command.h>
#include "subsystems/CargoArmSubsystem.h"
#include "subsystems/CargoControlSubsystem.h"


class TiltCargoArmBackCommand : public frc::Command {
 public:
  TiltCargoArmBackCommand();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
