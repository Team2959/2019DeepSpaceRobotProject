#pragma once

// Define Cargo Arm positions
constexpr double kArmTiltBackwardPosition = 0;
constexpr double kArmUpPosition = 3500;
constexpr double kArmTiltForwardPosition = 7000;
constexpr double kArmExtendPosition = 13000;

constexpr double kArmEncoderTickPerRev = 1024;
constexpr double kArmTiltForwardDegrees = 110;
constexpr double kArmDegreeToEncoder = (kArmTiltForwardPosition) / (kArmTiltForwardDegrees);