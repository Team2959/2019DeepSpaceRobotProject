/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/CommandGroup.h>
#include "subsystems/ClimbSubsystem.h"
#include "subsystems/LiftAndShuttleSubsystem.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include <Robot.h>


class RearRaiseClimbCommandGroup : public frc::CommandGroup {
 public:
  RearRaiseClimbCommandGroup();
  void Interrupted() override;
  void End() override;
};
