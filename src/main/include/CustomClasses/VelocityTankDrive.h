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
#include "AHRS.h"

class VelocityTankDrive: public frc::RobotDriveBase
{

 //NAVX Communications
    AHRS* ahrs;
    

private:
    // Motor controllers used in the robot drive
    rev::CANSparkMax& m_rightPrimary;
    rev::CANSparkMax& m_leftPrimary;

    
    // PID Controllers
    rev::CANPIDController m_rightPID = m_rightPrimary.GetPIDController();
    rev::CANPIDController m_leftPID  = m_leftPrimary.GetPIDController();

    // Encoders
    rev::CANEncoder m_rightEncoder = m_rightPrimary.GetEncoder();
    rev::CANEncoder m_leftEncoder  = m_leftPrimary.GetEncoder();

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
    
    void SetupPIDController (rev::CANPIDController& pid);
   

   


public:
    // Constructor
    VelocityTankDrive(rev::CANSparkMax& leftPrimary, rev::CANSparkMax& rightPrimary,double maxSpeed,double safety, double maxAccel, double maxCurrent );

    // TankDrive is an interface similar to that of the FRC differential drive class. 
    /* It shall accept a speed for each side of the robot drive in real world values (RPM),
       as opposed to percentages. */
    
    void TankDrive (double left, double right);
    static void SetupSparkMax (rev::CANSparkMax& motor, double motorMaxSpeed,double driveSafetyFactor, double robotMaxAccel, double driveMaxCurrent);
    void SetupPIDGains (double p, double i, double d, double ff, double iz);
};
