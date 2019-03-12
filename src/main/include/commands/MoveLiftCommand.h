/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "commands/MoveLiftAndShuttleCommand.h"

class MoveLiftCommand : public MoveLiftAndShuttleCommand
{
 public:
  enum LiftTargetLevel
  {
    Floor,
    Bottom,
    CargoShip,
    MiddleRocket,
    TopRocket,
    RaiseHatchFromWall,
    GrabHatchFromWall
  };

 private:
  LiftTargetLevel m_liftTarget;
  bool m_bUseCurrentShuttlePosition;
  bool m_bUseCurrentLiftPosition;

 public:
  MoveLiftCommand(LiftTargetLevel liftTarget,
   bool useCurrentShuttlePosition = false,
   bool useCurrentLiftPosition = false);

  void Initialize() override;
};
