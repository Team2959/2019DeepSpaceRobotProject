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

#include "utilities/MotorControllerHelpers.h"

class VelocityTankDrive: public frc::RobotDriveBase
{   
private:
    //NAVX Communications
    AHRS* ahrs;

    // Motor controllers used in the robot drive
    rev::CANSparkMax& m_rightPrimary;
    rev::CANSparkMax& m_leftPrimary;
    
    // PID Controllers
    rev::CANPIDController m_rightPID;
    rev::CANPIDController m_leftPID;

    // Encoders
    rev::CANEncoder m_rightEncoder;
    rev::CANEncoder m_leftEncoder;

    // Control Loop (PIDF) gains
    double m_proportional = 0.0005;
    double m_integral     = 0.000001;
    double m_derivative   = 0.0;
    double m_feedForward  = 0.0;
    double m_iZone        = 0.0;
    
    // Send Gains to PID Controller
    void SetupPIDController (rev::CANPIDController& pid);

public:
    // Constructor
    explicit VelocityTankDrive (rev::CANSparkMax& leftPrimary, rev::CANSparkMax& rightPrimary);

    static void SetupSparkMax  (rev::CANSparkMax& motor, double motorMaxSpeed,double driveSafetyFactor, double robotMaxAccel, double driveMaxCurrent);

    // TankDrive is an interface similar to that of the FRC differential drive class. 
    /* It shall accept a speed for each side of the robot drive in real world values (RPM),
       as opposed to percentages. */
    void TankDrive     (double left, double right);
    void SetupPIDGains (double p, double i, double d, double ff, double iz);

    void StopMotor      () override;
    void GetDescription (wpi::raw_ostream& desc) const override;
    void InitSendable   (SendableBuilder& builder) override;

    void DisabledWatchDog ();

    // Testing functions only, should not be used in production
    void DashboardDataInit   ();
    void DashboardDataUpdate ();
};
