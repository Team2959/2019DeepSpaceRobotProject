/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LiftAndShuttleSubsystem.h"
#include "subsystems/LiftAndShuttlePositions.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "utilities/MotorControllerHelpers.h"

constexpr int kShuttleCloseEnoughToPosition = 100;
constexpr int kShuttleSafeFrontPosition = 1000;
constexpr int kShuttleSafeRearPosition = -kShuttleSafeFrontPosition;

constexpr int kLiftCloseEnoughToPosition = 250;
constexpr int kLiftMaxSafeHeight = 5000;

LiftAndShuttleSubsystem::LiftAndShuttleSubsystem() : Subsystem("LiftAndShuttleSubsystem") 
{
  // Shuttle motor controller configuration
  m_leftShuttle.GetSlotConfigs(m_pidConfigShuttle);
  m_pidConfigShuttle.kP = 0.1;
  m_pidConfigShuttle.kI = 0;
  m_pidConfigShuttle.kD = 0;
  m_pidConfigShuttle.kF = 0;
  // m_pidConfigShuttle.integralZone = x;
  // m_pidConfigShuttle.closedLoopPeakOutput = 1.0;
  // m_pidConfigShuttle.allowableClosedloopError = 128;
  MotorControllerHelpers::ConfigureTalonSrxMotorController(m_leftShuttle, m_pidConfigShuttle, false);
  MotorControllerHelpers::ConfigureTalonSrxMotorController(m_rightShuttle, m_pidConfigShuttle, false);

  MoveShuttleToPosition(kShuttleMiddlePosition);

  // Lift motor contorller configuration
  m_liftFollower1.Follow(m_liftPrimary);
  m_liftFollower2.Follow(m_liftPrimary);

  m_liftPidController = m_liftPrimary.GetPIDController();
  m_liftPidController.SetP(1.0);
  m_liftPidController.SetI(1.0);  
  m_liftPidController.SetD(0);
  m_liftPidController.SetIZone(0);
  m_liftPidController.SetFF(0);
  m_liftPidController.SetOutputRange(kLiftBottomPosition, kLiftTopPosition);
}

bool LiftAndShuttleSubsystem::IsShuttleAtPosition(double targetPosition)
{
  // actually check position is near target position
  return fabs(CurrentShuttlePosition() - targetPosition) < kShuttleCloseEnoughToPosition;
}

double LiftAndShuttleSubsystem::CurrentShuttlePosition()
{
  return m_leftShuttle.GetSelectedSensorPosition(0);;
}

void LiftAndShuttleSubsystem::MoveShuttleToPosition(double position)
{
  m_leftShuttle.Set(ctre::phoenix::motorcontrol::ControlMode::Position, position);
  m_rightShuttle.Set(ctre::phoenix::motorcontrol::ControlMode::Position, position);

  frc::SmartDashboard::PutNumber("Shtl: Target", position);
  frc::SmartDashboard::PutNumber("Shtl: Position", CurrentShuttlePosition());
  frc::SmartDashboard::PutNumber("Shtl: Velocity", m_leftShuttle.GetSelectedSensorVelocity());
}

void LiftAndShuttleSubsystem::ShuttleStopAtCurrentPosition()
{
  MoveShuttleToPosition(CurrentShuttlePosition());
}

// Lift Code

bool LiftAndShuttleSubsystem::IsLiftAtPosition(double targetPosition)
{
  // actually check position is near target position
  return fabs(CurrentLiftPosition() - targetPosition) < kLiftCloseEnoughToPosition;
}

bool LiftAndShuttleSubsystem::IsLiftSafeForShuttleMoveThroughMiddle()
{
  return CurrentLiftPosition() < kLiftMaxSafeHeight;
}

double LiftAndShuttleSubsystem::CurrentLiftPosition()
{
  return m_liftEncoder.GetPosition();
}

void LiftAndShuttleSubsystem::MoveLiftToPosition(double position)
{
  m_liftPidController.SetReference(position, rev::ControlType::kPosition);

  frc::SmartDashboard::PutNumber("Lift: Target", position);
  frc::SmartDashboard::PutNumber("Lift: Position", CurrentShuttlePosition());
  frc::SmartDashboard::PutNumber("Lift: Velocity", m_liftEncoder.GetVelocity());
}

void LiftAndShuttleSubsystem::LiftStopAtCurrentPosition()
{
  MoveLiftToPosition(CurrentLiftPosition());
}

// Movement Control Interface
bool LiftAndShuttleSubsystem::IsAtTargetPosition(double targetShuttlePosition, double targetLiftPosition)
{
  // compare the target positions against the current positions
  return IsShuttleAtPosition(targetShuttlePosition) && IsLiftAtPosition(targetLiftPosition);
}

void LiftAndShuttleSubsystem::MoveToTargetPosition(
    double targetShuttlePosition,
    double targetLiftPosition,
    bool isShuttleArmSafe)
{
  // evaluate current position and decide where to send lift and shuttle safely to get closer to target posistions
  auto currentShuttlePosition = CurrentShuttlePosition();

  // Moving shuttle to next position
  // Only move the shuttle if the cargo arm is safe and not at current position
  if (isShuttleArmSafe  && ! IsShuttleAtPosition(targetShuttlePosition))
  {
    // determine direction of shuttle movement
    if (targetShuttlePosition > currentShuttlePosition)
    {
      // needs to move towards front

      // if vertical system is safe or current position is greater than the safe rear shuttle psoition
      if (IsLiftSafeForShuttleMoveThroughMiddle() || currentShuttlePosition > kShuttleSafeRearPosition)
      {
        // move to target shuttle position
        MoveShuttleToPosition(targetShuttlePosition);
      }
      else
      {
        // move to safe shuttle rear position
        MoveShuttleToPosition(kShuttleSafeRearPosition);
      }
    }
    else
    {
      // needs to move towards rear

      // if vertical system safe or current position is less than the safe front shuttle position
      if (IsLiftSafeForShuttleMoveThroughMiddle() || currentShuttlePosition < kShuttleSafeFrontPosition)
      {
        // move to target shuttle position
        MoveShuttleToPosition(targetShuttlePosition);
      }
      else
      {
        // move to safe shuttle front position
        MoveShuttleToPosition(kShuttleSafeFrontPosition);
      }
    }
  }

  // move the lift

  // determine if the shuttle needs to cross through the middle
}

void LiftAndShuttleSubsystem::StopAtCurrentPosition()
{
  // stop lift and shuttle at current positions
  LiftStopAtCurrentPosition();
  ShuttleStopAtCurrentPosition();
}

void LiftAndShuttleSubsystem::DashboardDataInit()
{
  frc::SmartDashboard::PutData(this);
  MotorControllerHelpers::DashboardInitTalonSrx("Shtl", m_pidConfigShuttle);
  MotorControllerHelpers::DashboardInitSparkMax("Lift", m_liftPidController);
}

void LiftAndShuttleSubsystem::DashboardData()
{
  MotorControllerHelpers::DashboardDataTalonSrx("Shtl", m_leftShuttle, m_pidConfigShuttle);
  MotorControllerHelpers::DashboardDataTalonSrx("Shtl", m_rightShuttle, m_pidConfigShuttle);

  auto targetPosition = frc::SmartDashboard::GetNumber("Shtl: Go To Position", 0);
  MoveShuttleToPosition(targetPosition);

  MotorControllerHelpers::DashboardDataSparkMax("Lift", m_liftPidController);

  targetPosition = frc::SmartDashboard::GetNumber("Lift: Go To Position", 0);
  MoveLiftToPosition(targetPosition);
}
