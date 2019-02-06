/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CustomClasses/VelocityTankDrive.h"


VelocityTankDrive::VelocityTankDrive()
{
    // Set up the follower motor controllers
    m_right2Follower.Follow(m_right1Primary);
    m_left2Follower.Follow(m_left1Primary);
    
    // Assign a PID controller for each motor
    m_pidControllerLeft = m_left1Primary.GetPIDController();
    m_pidControllerRight = m_right1Primary.GetPIDController();

    // Get the encoder values from each primary controller
    m_encoderLeft = m_left1Primary.GetEncoder();
    m_encoderRight = m_right1Primary.GetEncoder();

    // Set the PIDF gains for the left side primary motor controller
    m_pidControllerLeft.SetP(m_proportional);
    m_pidControllerLeft.SetI(m_integral);
    m_pidControllerLeft.SetD(m_derivative);
    m_pidControllerLeft.SetIZone(m_iZone);
    m_pidControllerLeft.SetFF(m_feedForward);
    m_pidControllerLeft.SetOutputRange(-1, 1);

    // Set the PIDF gains for the right side primary motor controller
    m_pidControllerRight.SetP(m_proportional);
    m_pidControllerRight.SetI(m_integral);
    m_pidControllerRight.SetD(m_derivative);
    m_pidControllerRight.SetIZone(m_iZone);
    m_pidControllerRight.SetFF(m_feedForward);
    m_pidControllerRight.SetOutputRange(-1, 1);
}

void VelocityTankDrive::SetPointGenerator (double dsp, rev::CANPIDController& pidController, rev::CANEncoder& encoder)
{
    double tSlice  = 0.02;                  // Assumed rate at which this function is called in seconds
    double current = encoder.GetVelocity(); // Current velocity

    // Calculating the maximum speed that can be achieved by driving at each limit for 'tslice'
    // This approach applies each limit independently, rather than using all together
    double velocity = dsp;                                   // RPM
    double accel    = m_maxAcceleration * tSlice + current;  // RPM/s
    double jerk     = m_maxJerk * tSlice * tSlice + current; // RPM/s^2

    // Calculate the minimum of the 3 above variables
    double min = velocity; // Initially, assume velocity is the minimum
    if (accel < min)       // Check if acceleration is less than the minimum
        min = accel;       // If so, set it as the new minimum
    if (jerk < min)        // Check if jerk is less than the minimum
        min = jerk;        // If so, set it as the new minimum

    // The minimum of our limits is our set-point to drive at
    pidController.SetReference(min, rev::ControlType::kVelocity);
}

void VelocityTankDrive::TankDrive(double left, double right)
{
    // Set the lieft and right side sppeds through the SetPointGenerator function
    SetPointGenerator(left, m_pidControllerLeft, m_encoderLeft);
    SetPointGenerator(right, m_pidControllerRight, m_encoderRight);
}