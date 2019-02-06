/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CustomClasses/VelocityTankDrive.h"


VelocityTankDrive::VelocityTankDrive() {
    m_right2Follower.Follow(m_right1Primary);
    m_left2Follower.Follow(m_left1Primary);

    m_pidControllerLeft = m_left1Primary.GetPIDController();
    m_pidControllerRight = m_right1Primary.GetPIDController();

    m_pidControllerLeft.SetP(m_proportional);
    m_pidControllerLeft.SetI(m_integral);
    m_pidControllerLeft.SetD(m_derivative);
    m_pidControllerLeft.SetIZone(m_iZone);
    m_pidControllerLeft.SetFF(m_feedForward);
    m_pidControllerLeft.SetOutputRange(-1, 1);

    m_pidControllerRight.SetP(m_proportional);
    m_pidControllerRight.SetI(m_integral);
    m_pidControllerRight.SetD(m_derivative);
    m_pidControllerRight.SetIZone(m_iZone);
    m_pidControllerRight.SetFF(m_feedForward);
    m_pidControllerRight.SetOutputRange(-1, 1);

    m_encoderLeft = m_left1Primary.GetEncoder();
    m_encoderRight = m_right1Primary.GetEncoder();

}

void VelocityTankDrive::SetPointGenerator (double dsp, rev::CANPIDController& pidController, rev::CANEncoder& encoder)
{
    double tSlice = 0.02;
    double current = encoder.GetVelocity();
    double velocity = dsp;
    double accel = m_maxAcceleration * tSlice + current;
    double jerk = m_maxJerk * tSlice * tSlice + current;
    double min = velocity;
    if (accel < min)min = accel;
    if (jerk < min)min = jerk;
    pidController.SetReference(min, rev::ControlType::kVelocity);
  
}
void VelocityTankDrive::TankDrive(double left, double right){
    SetPointGenerator(left, m_pidControllerLeft,m_encoderLeft);
    SetPointGenerator(right, m_pidControllerRight,m_encoderRight);
}