/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/drive/RobotDriveBase.h>
#include <rev/CANSparkMax.h>
#include "RobotMap.h"

class VelocityTankDrive: public frc::RobotDriveBase
{
private:
    // Establish useful constants, such as physical limitations of the robot
    const double kMotorMaxSpeed     = 5676.0;  // RPM
    const double kDriveSafetyFactor = 0.90;    // Multiplier for establishing reliable limits
    const double kRobotMaxAccel     = 2207.07; // RPM / s
    const double kDriveMaxCurrent   = 80.0;    // Amps

    // Motor controllers used in the robot drive
    rev::CANSparkMax m_rightPrimary  {kRight1CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_rightFollower {kRight2CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_leftPrimary   {kLeft1CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_leftFollower  {kLeft2CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    
    // PID Controllers
    rev::CANPIDController m_rightPID;
    rev::CANPIDController m_leftPID;

    // Encoders
    rev::CANEncoder m_rightEncoder;
    rev::CANEncoder m_leftEncoder;

    /*
       double m_maxRPM          = 5676.0 * 0.85;    // RPM
       double m_gearRatio       = 1.0 / 6.11;       // Unused
       double m_maxTorque       = 40.623744 * 0.85  // N*m
       double m_maxAcceleration = 2207.07 * 0.85;   // RPM/s
       double m_maxVelocity     = m_maxRPM;         // RPM
       double m_maxJerk         = 50000.0;          // RPM/s^2 
    */

   // Characterizations of our robot drive train in controlled units (RPM & seconds)
    double m_maxSpeed = kMotorMaxSpeed * kDriveSafetyFactor; // RPM
    double m_maxAccel = kRobotMaxAccel * kDriveSafetyFactor; // RPM / s

    // Control Loop (PIDF) gains
    double m_proportional = 0.0005;
    double m_integral     = 0.000001;
    double m_derivative   = 0.0;
    double m_feedForward  = 0.0;
    double m_iZone        = 0.0;

    // SetPointGenerator is the singular interface for each motor controller.  
    /* It shall accepts a desired set point and determines a responsible next set point 
       for the motor control loop, accounting for current speed and all applicable limits. */
    //void SetPointGenerator  (double dsp, rev::CANPIDController& pidController, rev::CANEncoder& encoder);
    void SetupSparkMax      (rev::CANSparkMax& motor);
    void SetupPIDController (rev::CANPIDController& pid);

public:
    // Constructor
    VelocityTankDrive();

    // TankDrive is an interface similar to that of the FRC differential drive class. 
    /* It shall accept a speed for each side of the robot drive in real world values (RPM),
       as opposed to percentages. */
    void TankDrive (double left, double right);
};
