#pragma once

// Define Lift and Shuttle Positions to be used outside subsystem
constexpr double kShuttleMiddlePosition = 0;
constexpr double kShuttleFrontPosition = 11000;
constexpr double kShuttleRearPosition = -4500; // -3700 is for cable track tripping switch, -5200 is for near hard stop

constexpr double kLiftFloorPosition = 0;
constexpr double kLiftBottomPosition = 4;
constexpr double kLiftCargoShipPosition = 24;
constexpr double kLiftMiddlePosition = 40;
constexpr double kLiftTopPosition = 55;
constexpr double kLiftRemoveHatchFromWallPosition = kLiftBottomPosition + 6;
