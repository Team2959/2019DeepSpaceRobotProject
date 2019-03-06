/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveLiftCommand.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include "Robot.h"

MoveLiftCommand::MoveLiftCommand(double targetLiftPosition) : MoveLiftAndShuttleCommand(targetLiftPosition, 0)
{
}

void MoveLiftCommand::Initialize()
{
  // if shuttle target is front -> set shuttle target postion to kShuttleFrontPosition
  if (Robot::m_oi.m_shuttleTargetFront == true)
  {
    m_targetShuttlePosition = kShuttleFrontPosition;
  }
  // else shuttle is rear -> set shuttle target postion to kShuttleRearPosition
  else
  {
    m_targetShuttlePosition = kShuttleRearPosition;
  }
}
