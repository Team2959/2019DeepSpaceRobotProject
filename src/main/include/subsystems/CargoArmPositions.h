#pragma once

// Define Cargo Arm positions
constexpr double kArmTiltBackwardPosition = 0;
constexpr double kArmUpPosition = 2500;
constexpr double kArmTiltForwardPosition = 6000;
constexpr double kArmExtendPosition = 16000;

constexpr double kArmEncoderTickPerRev = 1024;
constexpr double kArmTiltForwardDegrees = 110;
constexpr double kArmDegreeToEncoder = (kArmTiltForwardPosition) / (kArmTiltForwardDegrees);