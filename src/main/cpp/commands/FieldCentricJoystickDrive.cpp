/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/FieldCentricJoystickDrive.h"
#include "Robot.h"

#include <cmath>

constexpr double kRadToDegree = 3.14159265358979323846 / 180.0;

FieldCentricJoystickDrive::FieldCentricJoystickDrive() {
    // Use Requires() here to declare subsystem dependencies
    // eg. Requires(Robot::chassis.get());
    Requires(&Robot::m_driveTrainSubsystem);

    jsc.SetDeadband(0.1);
    jsc.SetExponent(3.0);
    jsc.SetRange(0, 1);
}

double FieldCentricJoystickDrive::TrigAngleToRobotHeading (double angle) {
    double heading;
    
    heading = angle + 270.0;
    while (heading >= 360.0) heading -= 360.0;

    return heading;
}

// This function returns the shortest angle between a target and current angle
double FieldCentricJoystickDrive::ShortestAngle (double target, double current) {
    // Avoid error with wraparound at 360 by coercing values to [0, 360)
    while (target >= 360.0) target -= 360.0;
    while (current >= 360.0) current -= 360.0;

    double diff = target - current;
    if (diff > 180.0) {
        diff = -1.0 * (360 - diff);
    } else if (diff < -180.0) {
        diff = 360 + diff;
    }

    return diff;
}

FieldCentricJoystickDrive::JoystickVector FieldCentricJoystickDrive::ProcessJoystick (double x, double y) {
    struct JoystickVector jv;
    jv.heading = TrigAngleToRobotHeading(atan2(y, x) * kRadToDegree);
    jv.magnitude = jsc.Condition(fmax(fabs(x), fabs(y)));

    return jv;
}

// Called just before this Command runs the first time
void FieldCentricJoystickDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void FieldCentricJoystickDrive::Execute() {
    double x = Robot::m_oi.m_leftDriverJoystick.GetX();
    double y = Robot::m_oi.m_leftDriverJoystick.GetY();
    double t = Robot::m_oi.m_leftDriverJoystick.GetTwist();

    auto jv = ProcessJoystick(x, y);
    double currentHeading = Robot::m_driveTrainSubsystem.GetHeading();

    double angleToTurn = ShortestAngle(jv.heading, currentHeading);
    double rightVelocity = jv.magnitude;
    // Select which wheel velocity is going to be changed
    if (angleToTurn < 0.0) {
        
    }
}

// Make this return true when this Command no longer needs to run execute()
bool FieldCentricJoystickDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void FieldCentricJoystickDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FieldCentricJoystickDrive::Interrupted() {}
