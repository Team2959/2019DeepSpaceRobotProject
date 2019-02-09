/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LiftAndShuttleSubsystem.h"
#include "subsystems/LiftAndShuttlePositions.h"

constexpr int kShuttleCloseEnoughToPosition = 100;
constexpr int kShuttleSafeFrontPosition = 1000;
constexpr int kShuttleSafeRearPosition = -kShuttleSafeFrontPosition;

constexpr int kLiftCloseEnoughToPosition = 250;
constexpr int kLiftMaxSafeHeight = 5000;

LiftAndShuttleSubsystem::LiftAndShuttleSubsystem() : Subsystem("LiftAndShuttleSubsystem") 
{
  // Shuttle motor controller configuration
  ConfigureTalonMotorController(m_leftShuttle);
  ConfigureTalonMotorController(m_rightShuttle);

  MoveShuttleToPosition(kShuttleMiddlePosition);

  // Lift motor contorller configuration
  m_liftFollower1.Follow(m_liftPrimary);
  m_liftFollower2.Follow(m_liftPrimary);

  ConfigureSparkMaxMotorController(m_liftPrimary);
  ConfigureSparkMaxMotorController(m_liftFollower1);
  ConfigureSparkMaxMotorController(m_liftFollower2);
}

void LiftAndShuttleSubsystem::ConfigureSparkMaxMotorController(rev::CANSparkMax & motorController)
{
  rev::CANPIDController myPidController = motorController.GetPIDController();

  myPidController.SetP(1.0);
  myPidController.SetI(1.0);  
  myPidController.SetD(0);
  myPidController.SetIZone(0);
  myPidController.SetFF(0);
  myPidController.SetOutputRange(kLiftBottomPosition, kLiftTopPosition);
}

void LiftAndShuttleSubsystem::ConfigureTalonMotorController(
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX & motorController)
{
  motorController.ConfigSelectedFeedbackSensor(
    ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
	motorController.Config_kF(0, 0, 0);

	motorController.Config_kP(0, 1.0, 0);
	motorController.Config_kI(0, 0, 0);
//	motorController.Config_IntegralZone(0, 300, 0);
	motorController.SetSensorPhase(false);
	motorController.SetSelectedSensorPosition(0,0,0);

//	motorController.ConfigPeakOutputForward(1.00, 0);
//	motorController.ConfigPeakOutputReverse(-1.00, 0);
//	motorController.ConfigPeakCurrentLimit(5, 0);

//	motorController.ConfigAllowableClosedloopError(0, 128, 0);
//	motorController.ConfigClosedloopRamp(0, 0);
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
    (targetShuttlePosition <= kShuttleSafeRearPosition && currentShuttlePosition <= kShuttleSafeRearPosition)){
      // keep move to target position
  }
  // if yes, follow each plan
  else{
    // up => up
    if(currentLiftPosition >= kLiftMaxSafeHeight && targetLiftPosition >= kLiftMaxSafeHeight){
      targetLiftPosition = kLiftMaxSafeHeight;
    }
    // down => up
    else if(currentLiftPosition < kLiftMaxSafeHeight && targetLiftPosition >= kLiftMaxSafeHeight){
      targetLiftPosition = kLiftMaxSafeHeight;
    }
    // up => down or down => down
    else {
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