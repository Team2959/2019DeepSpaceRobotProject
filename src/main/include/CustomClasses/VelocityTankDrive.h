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
    // Motor controllers used in the robot drive
    rev::CANSparkMax m_right1Primary { kRight1CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    rev::CANSparkMax m_right2Follower { kRight2CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    rev::CANSparkMax m_left1Primary { kLeft1CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    rev::CANSparkMax m_left2Follower { kLeft2CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    
    // PID Controllers
    rev::CANPIDController m_pidControllerLeft;
    rev::CANPIDController m_pidControllerRight;

    // Encoders
    rev::CANEncoder m_encoderLeft;
    rev::CANEncoder m_encoderRight;

    // Characterizations of our robot drive train in controlled units (RPM & seconds)
    double m_maxRPM          = 5676.0 * 0.85;    // RPM
    double m_gearRatio       = 1.0 / 6.11;       // Unused
    double m_maxTorque       = 40.623744 * 0.85  // N*m
    double m_maxAcceleration = 2207.07 * 0.85;   // RPM/s
    double m_maxVelocity     = m_maxRPM;         // RPM
    double m_maxJerk         = 50000.0;          // RPM/s^2

    // Control Loop (PIDF) gains
    double m_proportional = 0.0005;
    double m_integral     = 0.000001;
    double m_derivative   = 0.0;
    double m_feedForward  = 0.0;
    double m_iZone        = 0.0;

    // SetPointGenerator is the singular interface for each motor controller.  
    /* It shall accepts a desired set point and determines a responsible next set point 
       for the motor control loop, accounting for current speed and all applicable limits. */
    void SetPointGenerator (double dsp, rev::CANPIDController& pidController, rev::CANEncoder& encoder);

public:
    // Constructor
    VelocityTankDrive();

    // TankDrive is an interface similar to that of the FRC differential drive class. 
    /* It shall accept a speed for each side of the robot drive in real world values (RPM),
       as opposed to percentages. */
    void TankDrive (double left, double right);
};
