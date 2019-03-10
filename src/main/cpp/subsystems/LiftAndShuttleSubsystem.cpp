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
#include <algorithm>

// Shuttle constants
constexpr double kShuttleCloseEnoughToPosition = 500;
constexpr double kShuttleSafeFrontPosition = 6000;
constexpr double kShuttleSafeRearPosition = -4000;
constexpr double kShuttleKP = 0.37;
constexpr double kShuttleKFf = 0.2046;
constexpr double kShuttleCruiseVelocity = 3000;
constexpr double kShuttleAcceleration = 4500;

// Lift constants
constexpr double kLiftCloseEnoughToPosition = 0.1;
constexpr double kLiftMaxSafeHeight = 2;
constexpr double kLiftKP = 0.00012;
constexpr double kLiftKI = 1e-6;
constexpr double kLiftMaxVelocity = 4000;
constexpr double kLiftMaxAcceleration = 9000;
constexpr double kLiftFirstStopPosition = 40;
constexpr double kLiftCloseToStop = 2;

LiftAndShuttleSubsystem::LiftAndShuttleSubsystem() : Subsystem("LiftAndShuttleSubsystem") 
{
  // Shuttle motor controller configuration
  m_rightShuttle.GetSlotConfigs(m_pidConfigShuttle);
  m_pidConfigShuttle.kP = kShuttleKP;
  m_pidConfigShuttle.kI = 0;
  m_pidConfigShuttle.kD = 0;
  m_pidConfigShuttle.kF = kShuttleKFf;
  MotorControllerHelpers::ConfigureTalonSrxMotorController(m_leftShuttle, m_pidConfigShuttle, true);
  MotorControllerHelpers::ConfigureTalonSrxMotorController(m_rightShuttle, m_pidConfigShuttle, false);

  m_leftShuttle.ConfigMotionCruiseVelocity(kShuttleCruiseVelocity, 10);
  m_leftShuttle.ConfigMotionAcceleration(kShuttleAcceleration, 10);

  m_rightShuttle.ConfigMotionCruiseVelocity(kShuttleCruiseVelocity, 10);
  m_rightShuttle.ConfigMotionAcceleration(kShuttleAcceleration, 10);
}

void LiftAndShuttleSubsystem::OnRobotInit()
{
  // Zero shuttle positions
	m_leftShuttle.SetSelectedSensorPosition(0,0,0);
	m_rightShuttle.SetSelectedSensorPosition(0,0,0);

  MoveShuttleToPosition(0);

  // Lift motor contorller configuration
  MotorControllerHelpers::SetupSparkMax(m_liftPrimary, 80, false);

  m_liftFollower1.Follow(m_liftPrimary);
  m_liftFollower2.Follow(m_liftPrimary);

  ConfigureLiftPid(m_liftPidController);

  m_liftEncoder.SetPosition(0);

  MoveLiftToPosition(0);

  frc::SmartDashboard::PutBoolean("Lift: Bottom Limit", IsLiftAtBottom());
  frc::SmartDashboard::PutBoolean("Shtl: Front Limit", IsAtShuttleFrontLimit());
  frc::SmartDashboard::PutBoolean("Shtl: Rear Limit", IsAtShuttleRearLimit());

  DashboardDebugInit();
}

void LiftAndShuttleSubsystem::ConfigureLiftPid(rev::CANPIDController & pidConfig)
{
  // common spot for lift motor controller PID config, so same values
  pidConfig.SetP(kLiftKP);
  pidConfig.SetI(kLiftKI);  
  pidConfig.SetD(0);
  pidConfig.SetIZone(0);
  pidConfig.SetFF(0);
  pidConfig.SetOutputRange(-1, 1);
  pidConfig.SetP(kLiftKP);

  pidConfig.SetSmartMotionMaxVelocity(kLiftMaxVelocity);
  pidConfig.SetSmartMotionMinOutputVelocity(0);
  pidConfig.SetSmartMotionMaxAccel(kLiftMaxAcceleration);
  pidConfig.SetSmartMotionAllowedClosedLoopError(0);
}

void LiftAndShuttleSubsystem::OnRobotPeriodic(bool updateDebugInfo)
{
  frc::SmartDashboard::PutBoolean("Lift: Bottom Limit", IsLiftAtBottom());
  frc::SmartDashboard::PutBoolean("Shtl: Front Limit", IsAtShuttleFrontLimit());
  frc::SmartDashboard::PutBoolean("Shtl: Rear Limit", IsAtShuttleRearLimit());

  m_updateDebugInfo = updateDebugInfo;
  if (updateDebugInfo)
    DashboardDebugPeriodic();
}

void LiftAndShuttleSubsystem::DashboardDebugInit()
{
  frc::SmartDashboard::PutData(this);
  MotorControllerHelpers::DashboardInitTalonSrx("Shtl", m_pidConfigShuttle);
  frc::SmartDashboard::PutBoolean("Shtl: Start", false);

  MotorControllerHelpers::DashboardInitSparkMax("Lift", m_liftEncoder);
  frc::SmartDashboard::PutBoolean("Lift: Start", false);

  frc::SmartDashboard::PutNumber("Lift: Max Velocity", kLiftMaxVelocity);
  frc::SmartDashboard::PutNumber("Lift: Min Velocity", 0);
  frc::SmartDashboard::PutNumber("Lift: Max Acceleration", kLiftMaxAcceleration);
  frc::SmartDashboard::PutNumber("Lift: Allowed Closed Loop Error", 0);
  frc::SmartDashboard::PutNumber("Lift: Arb FF", 0);
}

void LiftAndShuttleSubsystem::DashboardDebugPeriodic()
{
  MotorControllerHelpers::DashboardDataTalonSrx("Shtl", m_leftShuttle, m_pidConfigShuttle);
  MotorControllerHelpers::DashboardDataTalonSrx("Shtl", m_rightShuttle, m_pidConfigShuttle);
  frc::SmartDashboard::PutNumber("Shtl: Position", CurrentShuttlePosition());
  frc::SmartDashboard::PutNumber("Shtl: Position Left", m_leftShuttle.GetSelectedSensorPosition(0));
  frc::SmartDashboard::PutNumber("Shtl: Velocity", m_rightShuttle.GetSelectedSensorVelocity());

  auto startShuttle = frc::SmartDashboard::GetBoolean("Shtl: Start", false);
  if (startShuttle)
  {
    auto targetPosition = frc::SmartDashboard::GetNumber("Shtl: Go To Position", 0);
    targetPosition = std::min(targetPosition, kShuttleFrontPosition + kShuttleCloseEnoughToPosition);
    targetPosition = std::max(targetPosition, kShuttleRearPosition - kShuttleCloseEnoughToPosition);
    MoveShuttleToPosition(targetPosition);
  }

  MotorControllerHelpers::DashboardDataSparkMax("Lift", m_liftPidController, m_liftEncoder);

  auto maxV = frc::SmartDashboard::GetNumber("Lift: Max Velocity", kLiftMaxVelocity);
  if (fabs(maxV - m_liftPidController.GetSmartMotionMaxVelocity()) > kCloseToSameValue)
  {
    m_liftPidController.SetSmartMotionMaxVelocity(maxV);
  }
  auto minV = frc::SmartDashboard::GetNumber("Lift: Min Velocity", 0);
  if (fabs(minV - m_liftPidController.GetSmartMotionMinOutputVelocity()) > kCloseToSameValue)
  {
    m_liftPidController.SetSmartMotionMinOutputVelocity(minV);
  }
  auto maxAcc = frc::SmartDashboard::GetNumber("Lift: Max Acceleration", kLiftMaxAcceleration);
  if (fabs(maxAcc - m_liftPidController.GetSmartMotionMaxAccel()) > kCloseToSameValue)
  {
    m_liftPidController.SetSmartMotionMaxAccel(maxAcc);
  }
  auto err = frc::SmartDashboard::GetNumber("Lift: Allowed Closed Loop Error", 0);
  if (fabs(err - m_liftPidController.GetSmartMotionAllowedClosedLoopError()) > kCloseToSameValue)
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
    targetPosition = std::min(targetPosition, kLiftTopHatchPosition + 5);
    targetPosition = std::max(targetPosition, kLiftFloorPosition);
    MoveLiftToPosition(targetPosition);
  }
}

bool LiftAndShuttleSubsystem::IsAtShuttleFrontLimit() const
{
  return !m_shuttleFrontSwitch.Get();
}

bool LiftAndShuttleSubsystem::IsAtShuttleRearLimit() const
{
  return !m_shuttleBackSwitch.Get();
}

bool LiftAndShuttleSubsystem::IsLiftAtBottom() const
{
  return !m_liftBottomLimitSwitch.Get();
}

bool LiftAndShuttleSubsystem::IsShuttleAtPosition(double targetPosition)
{
  // actually check position is near target position
  return fabs(CurrentShuttlePosition() - targetPosition) < kShuttleCloseEnoughToPosition;
}

double LiftAndShuttleSubsystem::CurrentShuttlePosition()
{
  return m_rightShuttle.GetSelectedSensorPosition(0);
}

void LiftAndShuttleSubsystem::MoveShuttleToPosition(double position)
{
  m_leftShuttle.Set(ctre::phoenix::motorcontrol::ControlMode::MotionMagic, position);
  m_rightShuttle.Set(ctre::phoenix::motorcontrol::ControlMode::MotionMagic, position);

  if (m_updateDebugInfo)
    frc::SmartDashboard::PutNumber("Shtl: Target", position);
}

void LiftAndShuttleSubsystem::ShuttleStopAtCurrentPosition()
{
  MoveShuttleToPosition(CurrentShuttlePosition());
}

void LiftAndShuttleSubsystem::StopShuttleAndSetPosition(double position)
{
  m_rightShuttle.StopMotor();
  m_leftShuttle.StopMotor();
  m_leftShuttle.SetSelectedSensorPosition(position);
  m_rightShuttle.SetSelectedSensorPosition(position);
  MoveShuttleToPosition(position);
}

void LiftAndShuttleSubsystem::CargoShuttleFrontStop()
{
  StopShuttleAndSetPosition(kShuttleFrontPosition);
}

void LiftAndShuttleSubsystem::CargoShuttleBackStop()
{
  StopShuttleAndSetPosition(kShuttleRearPosition);
}

// Lift Code

void LiftAndShuttleSubsystem::LiftBottomReset()
{
  m_liftPrimary.StopMotor();
  m_liftFollower1.StopMotor();
  m_liftFollower2.StopMotor();
  m_liftEncoder.SetPosition(0);
  MoveLiftToPosition(0);
}

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
  double arbFF = 0.0;
  if (m_updateDebugInfo)
  {
    arbFF = frc::SmartDashboard::GetNumber("Lift: Arb FF", arbFF);
    frc::SmartDashboard::PutNumber("Lift: Target", position);
  }

  if (position > kLiftFirstStopPosition && CurrentLiftPosition() < kLiftFirstStopPosition - kLiftCloseToStop) {
    position = kLiftFirstStopPosition;
  }

  m_liftPidController.SetReference(position, rev::ControlType::kSmartMotion, arbFF);
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
  if (isShuttleArmSafe)//  && ! IsShuttleAtPosition(targetShuttlePosition))
  {
    // determine direction of shuttle movement
    if (targetShuttlePosition > currentShuttlePosition || targetShuttlePosition >= 0)
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

  // if (!IsLiftAtPosition(targetLiftPosition))
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

void LiftAndShuttleSubsystem::StopAndZero()
{
  // stop all motors and zero all encoders
  LiftBottomReset();
  StopShuttleAndSetPosition(0);
}
