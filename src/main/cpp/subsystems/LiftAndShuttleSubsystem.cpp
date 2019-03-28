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

// Lift constants
constexpr double kLiftCloseEnoughToPosition = 0.1;
constexpr double kLiftKP = 0.00012;
constexpr double kLiftKPClimbAdjust = 0.0001;
constexpr double kLiftKI = 1e-6;
constexpr double kLiftMaxVelocity = 4000;
constexpr double kLiftMaxAcceleration = 9000;
constexpr double kLiftFirstStopPosition = 40;
constexpr double kLiftCloseToStop = 2;

LiftAndShuttleSubsystem::LiftAndShuttleSubsystem() : Subsystem("LiftAndShuttleSubsystem") 
{
}

void LiftAndShuttleSubsystem::OnRobotInit()
{
  // Lift motor contorller configuration
  MotorControllerHelpers::SetupSparkMax(m_liftPrimary, 80, false);

  m_liftFollower1.Follow(m_liftPrimary);
  m_liftFollower2.Follow(m_liftPrimary);

  ConfigureLiftPid(m_liftPidController);

  m_liftEncoder.SetPosition(0);

  MoveLiftToPosition(0);

  frc::SmartDashboard::PutBoolean("Lift: Bottom Limit", IsLiftAtBottom());

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

  m_updateDebugInfo = updateDebugInfo;
  if (updateDebugInfo)
    DashboardDebugPeriodic();
}

void LiftAndShuttleSubsystem::DashboardDebugInit()
{
  frc::SmartDashboard::PutData(this);

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

bool LiftAndShuttleSubsystem::IsLiftAtBottom() const
{
  return !m_liftBottomLimitSwitch.Get();
}

// Lift Code

bool LiftAndShuttleSubsystem::IsLiftAtPosition(double targetPosition)
{
  // actually check position is near target position
  return fabs(CurrentLiftPosition() - targetPosition) < kLiftCloseEnoughToPosition;
}

double LiftAndShuttleSubsystem::CurrentLiftPosition()
{
  return -m_liftEncoder.GetPosition();
}

// Movement Control Interface

void LiftAndShuttleSubsystem::MoveLiftToPosition(double position)
{
  double arbFF = 0.0;
  if (m_updateDebugInfo)
  {
    arbFF = frc::SmartDashboard::GetNumber("Lift: Arb FF", arbFF);
    frc::SmartDashboard::PutNumber("Lift: Target", position);
  }

  if (position > kLiftFirstStopPosition && CurrentLiftPosition() < kLiftFirstStopPosition - kLiftCloseToStop)
  {
    position = kLiftFirstStopPosition;
  }

  m_liftPidController.SetReference(-position, rev::ControlType::kSmartMotion, arbFF);
}

void LiftAndShuttleSubsystem::StopAtCurrentPosition()
{
  // stop lift and shuttle at current positions
  MoveLiftToPosition(CurrentLiftPosition());
}

void LiftAndShuttleSubsystem::LiftBottomReset()
{
  m_liftPrimary.StopMotor();
  m_liftFollower1.StopMotor();
  m_liftFollower2.StopMotor();
  m_liftEncoder.SetPosition(0);
  MoveLiftToPosition(0);
}

void LiftAndShuttleSubsystem::ReconfigureLiftForClimb()
{
  m_liftPidController.SetP(kLiftKP + kLiftKPClimbAdjust);
  m_liftPidController.SetSmartMotionMaxVelocity(kLiftMaxVelocity/3.0);
  m_liftPidController.SetSmartMotionMaxAccel(kLiftMaxAcceleration/3.0);
}

void LiftAndShuttleSubsystem::EnableLiftBottomTrigger(bool enable)
{
    m_bLiftBottomTriggerEnable = enable;
}

bool LiftAndShuttleSubsystem::IsLiftBottomTriggerEnabled() const
{
    return m_bLiftBottomTriggerEnable;
}
 double LiftAndShuttleSubsystem::LiftAppliedOutput()
 {
    return m_liftPrimary.GetAppliedOutput();
 }
void LiftAndShuttleSubsystem::DriveLiftWithDutyCycle(double dutyCycle)
 {
  m_liftPrimary.Set(dutyCycle);
 }
 void LiftAndShuttleSubsystem::DriveLiftWithVelocityControl(double velocity)
 {
  m_liftPidController.SetReference(velocity, rev::ControlType::kVelocity);
 }
