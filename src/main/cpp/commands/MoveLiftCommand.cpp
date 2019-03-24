/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MoveLiftCommand.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include "Robot.h"

MoveLiftCommand::MoveLiftCommand(LiftTargetLevel liftTarget)
   : MoveLiftAndShuttleCommand(0)
{
  m_liftTarget = liftTarget;
}

void MoveLiftCommand::Initialize()
{
  MoveLiftAndShuttleCommand::Initialize();
  
  auto cargoIn = Robot::m_cargoControlSubsystem.CargoIn();
  switch (m_liftTarget)
  {
    case LiftTargetLevel::Floor:
      m_targetLiftPosition = kLiftFloorPosition;
      break;
    case LiftTargetLevel::Bottom:
      if (cargoIn)
        m_targetLiftPosition = kLiftBottomCargoPosition;
      else
        m_targetLiftPosition = kLiftBottomHatchPosition;
      break;
    case LiftTargetLevel::CargoShip:
      if (cargoIn)
        m_targetLiftPosition = kLiftCargoShipPosition;
      else
        m_targetLiftPosition = kLiftCargoShipHatchPosition;
      break;
    case LiftTargetLevel::MiddleRocket:
      if (cargoIn)
        m_targetLiftPosition = kLiftMiddleCargoPosition;
      else
        m_targetLiftPosition = kLiftMiddleHatchPosition;
      break;
    case LiftTargetLevel::TopRocket:
      if (cargoIn)
        m_targetLiftPosition = kLiftTopCargoPosition;
      else
        m_targetLiftPosition = kLiftTopHatchPosition;
      break;
    case LiftTargetLevel::RaiseHatchFromWall:
      m_targetLiftPosition = kLiftRemoveHatchFromWallPosition;
      break;
    case LiftTargetLevel::GrabHatchFromWall:
      m_targetLiftPosition = kLiftGrabHatchFromWallPosition;
      break;
    case LiftTargetLevel::ClimbHab2:
      m_targetLiftPosition = kLiftClimbHab2Position;
      break;
    case LiftTargetLevel::ClimbHab3:
      m_targetLiftPosition = kLiftClimbHab3Position;
      break;
  }
}
