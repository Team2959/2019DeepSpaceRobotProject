#pragma once

// Define Lift and Shuttle Positions to be used outside subsystem
constexpr int kShuttleMiddlePosition = 0;
constexpr int kShuttleFrontPosition = 11400;
constexpr int kShuttleRearPosition = -3700; // -3700 is for cable track tripping switch, -5200 is for near hard stop

constexpr int kLiftFloorPosition = 0;
constexpr int kLiftBottomPosition = 4;
constexpr int kLiftCargoShipPosition = 24;
constexpr int kLiftMiddlePosition = 40;
constexpr int kLiftTopPosition = 55;
constexpr int kLiftRemoveHatchFromWallPosition = kLiftBottomPosition + 6;
