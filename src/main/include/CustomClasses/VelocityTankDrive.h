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
    rev::CANSparkMax m_right1Primary { kRight1CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    rev::CANSparkMax m_right2Follower { kRight2CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    rev::CANSparkMax m_left1Primary { kLeft1CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    rev::CANSparkMax m_left2Follower { kLeft2CanSparkMaxMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless };
    
    double m_maxRPM = 5676*0.85;

    double m_gearRatio = 1 / 6.11;

    double m_maxTorque = 40.623744*0.85;

    double m_maxAcceleration = 2207.07*0.85; //RPM/s

    double m_maxVelocity = m_maxRPM * m_gearRatio;



    public:
    VelocityTankDrive();

    void MyTankDrive(double leftSpeed, double rightSpeed);
};
