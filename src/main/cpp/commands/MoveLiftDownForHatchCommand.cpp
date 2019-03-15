/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveLiftDownForHatchCommand.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include "Robot.h"

MoveLiftDownForHatchCommand::MoveLiftDownForHatchCommand()
   : MoveLiftAndShuttleCommand(0)
{
}

void MoveLiftDownForHatchCommand::Initialize()
{
  // drop set number of rotations from current position when delivering hatch
  m_targetLiftPosition = Robot::m_liftAndShuttleSubsystem.CurrentLiftPosition();
  m_targetLiftPosition -= 3;
}
