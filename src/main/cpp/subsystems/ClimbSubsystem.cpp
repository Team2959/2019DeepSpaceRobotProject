/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ClimbSubsystem.h"
#include "utilities/MotorControllerHelpers.h"

ClimbSubsystem::ClimbSubsystem() : Subsystem("ClimbSubsystem") {
    m_left.GetSlotConfigs(m_pidConfig);
    m_pidConfig.kP = 0.1;
    m_pidConfig.kI = 0.0;
    m_pidConfig.kD = 0;
    m_pidConfig.kF = 0.057;
    // m_pidConfig.integralZone = x;
    // m_pidConfig.closedLoopPeakOutput = 1.0;
    // m_pidConfig.allowableClosedloopError = 128;

    m_left.ConfigMotionCruiseVelocity(5000, 10);
    m_left.ConfigMotionAcceleration(4500,10);

    MotorControllerHelpers::ConfigureTalonSrxMotorController(m_left, m_pidConfig, false);
    m_right.Follow(m_left);
    m_right.SetInverted( ctre::phoenix::motorcontrol::InvertType::OpposeMaster);
}

void ClimbSubsystem::ClimbWheelsSetPosition(double position)
{
    m_left.Set(ctre::phoenix::motorcontrol::ControlMode::MotionMagic, position);
}

void ClimbSubsystem::ClimbSolenoidEngage() 
{
    m_climbEngage.Set(true);
}

void ClimbSubsystem::ClimbSolenoidDisengage()
{
    m_climbEngage.Set(false);
}

void ClimbSubsystem::PowerToClimbWheels()
{
    m_left.Set(ctre::phoenix::motorcontrol::ControlMode::Current, kClimbWheelsHoldingCurrent);
}
void ClimbSubsystem::StopAtCurrentDistance()
{
    ClimbWheelsSetPosition(CurrentClimbWheelPosition());
}
bool ClimbSubsystem::AreClimbWheelsAtPosition( double targetPosition)
{
    //Check to see if distance driven is close
    return fabs(CurrentClimbWheelPosition() - targetPosition) < kDriveCloseEnoughToPosition;
}
double ClimbSubsystem::CurrentClimbWheelPosition()
{
  return  m_left.GetSelectedSensorPosition();
}

