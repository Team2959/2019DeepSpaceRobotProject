/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CustomClasses/VelocityTankDrive.h"


VelocityTankDrive::VelocityTankDrive()
{
    // Establish current and acceleration limits
    SetupSparkMax(m_rightPrimary);
    SetupSparkMax(m_rightFollower);
    SetupSparkMax(m_leftPrimary);
    SetupSparkMax(m_leftFollower);

    // Set up the follower motor controllers
    m_rightFollower.Follow(m_rightPrimary);
    m_leftFollower.Follow(m_leftPrimary);

    // Set the PIDF gains for the primary motor controllers
    SetupPIDController(m_rightPID);
    SetupPIDController(m_leftPID);

    //NavX Communication

     ahrs = new AHRS(SerialPort::Port::kUSB);
}

void VelocityTankDrive::SetupSparkMax (rev::CANSparkMax& motor)
{
    motor.SetSmartCurrentLimit(kDriveMaxCurrent);
    motor.SetRampRate(kMotorMaxSpeed / m_maxAccel);
}

void VelocityTankDrive::SetupPIDController(rev::CANPIDController& pid)
{
    pid.SetP(m_proportional);
    pid.SetI(m_integral);
    pid.SetD(m_derivative);
    pid.SetIZone(m_iZone);
    pid.SetFF(m_feedForward);
    pid.SetOutputRange(-1, 1);
}

/*void VelocityTankDrive::SetPointGenerator (double dsp, rev::CANPIDController& pidController, rev::CANEncoder& encoder)
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
}*/

void VelocityTankDrive::TankDrive(double left, double right)
{
    // Set the left and right side speeds
    m_rightPID.SetReference(right, rev::ControlType::kVelocity);
    m_leftPID.SetReference(left, rev::ControlType::kVelocity);
}