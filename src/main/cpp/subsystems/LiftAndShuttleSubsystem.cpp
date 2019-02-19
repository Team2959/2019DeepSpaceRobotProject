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
#include <frc/DigitalInput.h>


constexpr int kShuttleCloseEnoughToPosition = 100;
constexpr int kShuttleSafeFrontPosition = 1000;
constexpr int kShuttleSafeRearPosition = -kShuttleSafeFrontPosition;

constexpr int kLiftCloseEnoughToPosition = 0.5;
constexpr int kLiftMaxSafeHeight = 2;

LiftAndShuttleSubsystem::LiftAndShuttleSubsystem() : Subsystem("LiftAndShuttleSubsystem") 
{
  // configure limit switches
  m_leftShuttle.ConfigForwardLimitSwitchSource(
    ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector,
    ctre::phoenix::motorcontrol::LimitSwitchNormal::LimitSwitchNormal_NormallyOpen);
  
  m_leftShuttle.ConfigReverseLimitSwitchSource(
  ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector,
  ctre::phoenix::motorcontrol::LimitSwitchNormal::LimitSwitchNormal_NormallyOpen);

    m_rightShuttle.ConfigForwardLimitSwitchSource(
    ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector,
    ctre::phoenix::motorcontrol::LimitSwitchNormal::LimitSwitchNormal_NormallyOpen);
  
  m_rightShuttle.ConfigReverseLimitSwitchSource(
  ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector,
  ctre::phoenix::motorcontrol::LimitSwitchNormal::LimitSwitchNormal_NormallyOpen);
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
}

void LiftAndShuttleSubsystem::OnRobotInit()
{
  MotorControllerHelpers::SetupSparkMax(m_liftPrimary, 80);
  MotorControllerHelpers::SetupSparkMax(m_liftFollower1, 80);
  MotorControllerHelpers::SetupSparkMax(m_liftFollower2, 80);

  // Lift motor contorller configuration
  m_liftFollower1.Follow(m_liftPrimary);
  m_liftFollower2.Follow(m_liftPrimary);

  m_liftPidController.SetP(5e-5);
  m_liftPidController.SetI(1e-6);  
  m_liftPidController.SetD(0);
  m_liftPidController.SetIZone(0);
  m_liftPidController.SetFF(0);
  m_liftPidController.SetOutputRange(-1, 1);

  m_liftPidController.SetSmartMotionMaxVelocity(4000);
  m_liftPidController.SetSmartMotionMinOutputVelocity(0);
  m_liftPidController.SetSmartMotionMaxAccel(1000);
  m_liftPidController.SetSmartMotionAllowedClosedLoopError(0);

  m_liftEncoder.SetPosition(0);

  DashboardDataInit();
}

bool LiftAndShuttleSubsystem::IsAtShuttleFrontLimit() const
{
  return m_shuttleFrontSwitch.Get();
}

bool LiftAndShuttleSubsystem::IsAtShuttleRearLimit() const
{
  return m_shuttleBackSwitch.Get();
}

bool LiftAndShuttleSubsystem::IsLiftAtBottom() const
{
  return m_liftBottomLimitSwitch.Get();
}

bool LiftAndShuttleSubsystem::IsShuttleAtPosition(double targetPosition)
{
  // actually check position is near target position
  return fabs(CurrentShuttlePosition() - targetPosition) < kShuttleCloseEnoughToPosition;
}

double LiftAndShuttleSubsystem::CurrentShuttlePosition()
{
  return m_leftShuttle.GetSelectedSensorPosition(0);
}

void LiftAndShuttleSubsystem::MoveShuttleToPosition(double position)
{
  m_leftShuttle.Set(ctre::phoenix::motorcontrol::ControlMode::Position, position);
  m_rightShuttle.Set(ctre::phoenix::motorcontrol::ControlMode::Position, position);

  frc::SmartDashboard::PutNumber("Shtl: Target", position);
}

void LiftAndShuttleSubsystem::ShuttleStopAtCurrentPosition()
{
  MoveShuttleToPosition(CurrentShuttlePosition());
}

void LiftAndShuttleSubsystem::LiftBottomReset()
{
  m_liftEncoder.SetPosition(0);
  m_liftPidController.SetReference(0,rev::ControlType::kPosition);
  m_liftPrimary.StopMotor();
}

void LiftAndShuttleSubsystem::CargoShuttleFrontStop()
{
  m_rightShuttle.StopMotor();
  m_leftShuttle.StopMotor();
  m_leftShuttle.SetSelectedSensorPosition(kShuttleFrontPosition);
  m_rightShuttle.SetSelectedSensorPosition(kShuttleFrontPosition);
}

void LiftAndShuttleSubsystem::CargoShuttleBackStop()
{
  m_rightShuttle.StopMotor();
  m_leftShuttle.StopMotor();
  m_leftShuttle.SetSelectedSensorPosition(kShuttleRearPosition);
  m_rightShuttle.SetSelectedSensorPosition(kShuttleRearPosition);
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
  auto arbFF = frc::SmartDashboard::GetNumber("Lift: Arb FF", 0);
  m_liftPidController.SetReference(position, rev::ControlType::kSmartMotion, arbFF);

  frc::SmartDashboard::PutNumber("Lift: Target", position);
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
  auto currentLiftPosition = CurrentLiftPosition();

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
  // if not, then go to target
  if((targetShuttlePosition >= kShuttleSafeFrontPosition && currentShuttlePosition >= kShuttleSafeFrontPosition)||
     (targetShuttlePosition <= kShuttleSafeRearPosition && currentShuttlePosition <= kShuttleSafeRearPosition))
  {
      // keep move to target position
  }
  // if yes, follow each plan
  else
  {
    // up => up
    if(currentLiftPosition >= kLiftMaxSafeHeight && targetLiftPosition >= kLiftMaxSafeHeight)
    {
      targetLiftPosition = kLiftMaxSafeHeight;
    }
    // down => up
    else if(currentLiftPosition < kLiftMaxSafeHeight && targetLiftPosition >= kLiftMaxSafeHeight)
    {
      targetLiftPosition = kLiftMaxSafeHeight;
    }
    // up => down or down => down
    else
    {
      // up => down
      //   if(currentLiftPosition >= kLiftMaxSafeHeight && targetLiftPosition < kLiftMaxSafeHeight)
      // down => down
      //   if(currentLiftPosition < kLiftMaxSafeHeight && targetLiftPosition < kLiftMaxSafeHeight){
          // move to target position
    }
  }

  if (!IsLiftAtPosition(targetLiftPosition))
  {
    MoveLiftToPosition(targetLiftPosition);
  }
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
  frc::SmartDashboard::PutBoolean("Shtl: Start", false);

  MotorControllerHelpers::DashboardInitSparkMax("Lift", m_liftEncoder);
  frc::SmartDashboard::PutBoolean("Lift: Start", false);

  frc::SmartDashboard::PutNumber("Lift: Max Velocity", 2000);
  frc::SmartDashboard::PutNumber("Lift: Min Velocity", 0);
  frc::SmartDashboard::PutNumber("Lift: Max Acceleration", 500);
  frc::SmartDashboard::PutNumber("Lift: Allowed Closed Loop Error", 0);
  frc::SmartDashboard::PutNumber("Lift: Arb FF", 0);
}

void LiftAndShuttleSubsystem::DashboardData()
{
  MotorControllerHelpers::DashboardDataTalonSrx("Shtl", m_leftShuttle, m_pidConfigShuttle);
  MotorControllerHelpers::DashboardDataTalonSrx("Shtl", m_rightShuttle, m_pidConfigShuttle);
  frc::SmartDashboard::PutNumber("Shtl: Position", CurrentShuttlePosition());
  frc::SmartDashboard::PutNumber("Shtl: Velocity", m_leftShuttle.GetSelectedSensorVelocity());

  auto startShuttle = frc::SmartDashboard::GetBoolean("Shtl: Start", false);
  if (startShuttle)
  {
    auto targetPosition = frc::SmartDashboard::GetNumber("Shtl: Go To Position", 0);
    MoveShuttleToPosition(targetPosition);
  }

  MotorControllerHelpers::DashboardDataSparkMax("Lift", m_liftPidController, m_liftEncoder);

  auto maxV = frc::SmartDashboard::GetNumber("Lift: Max Velocity", 2000);
  if (fabs(maxV - m_liftPidController.GetSmartMotionMaxVelocity()) > 0.0001)
  {
    m_liftPidController.SetSmartMotionMaxVelocity(maxV);
  }
  auto minV = frc::SmartDashboard::GetNumber("Lift: Min Velocity", 0);
  if (fabs(minV - m_liftPidController.GetSmartMotionMinOutputVelocity()) > 0.0001)
  {
    m_liftPidController.SetSmartMotionMinOutputVelocity(minV);
  }
  auto maxAcc = frc::SmartDashboard::GetNumber("Lift: Max Acceleration", 2000);
  if (fabs(maxAcc - m_liftPidController.GetSmartMotionMaxAccel()) > 0.0001)
  {
    m_liftPidController.SetSmartMotionMaxAccel(maxAcc);
  }
  auto err = frc::SmartDashboard::GetNumber("Lift: Allowed Closed Loop Error", 2000);
  if (fabs(err - m_liftPidController.GetSmartMotionAllowedClosedLoopError()) > 0.0001)
  {
    m_liftPidController.SetSmartMotionAllowedClosedLoopError(err);
  }

  frc::SmartDashboard::PutNumber("Lift: Position", CurrentLiftPosition());
  frc::SmartDashboard::PutNumber("Lift: Velocity", m_liftEncoder.GetVelocity());

  frc::SmartDashboard::PutNumber("Lift : Applied Output", m_liftPrimary.GetAppliedOutput() );
  frc::SmartDashboard::PutNumber("Lift : Output Current", m_liftPrimary.GetOutputCurrent() );

  auto startLift = frc::SmartDashboard::GetBoolean("Lift: Start", false);
  if (startLift)
  {
    auto targetPosition = frc::SmartDashboard::GetNumber("Lift: Go To Position", 0);
    MoveLiftToPosition(targetPosition);
  }

  frc::SmartDashboard::PutBoolean("Lift: Bottom Limit", m_liftBottomLimitSwitch.Get());
  frc::SmartDashboard::PutBoolean("Shtl: Front Limit", m_shuttleFrontSwitch.Get());
  frc::SmartDashboard::PutBoolean("Shtl: Rear Limit", m_shuttleBackSwitch.Get());
}
