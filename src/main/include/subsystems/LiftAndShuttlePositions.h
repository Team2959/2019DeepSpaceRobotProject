#pragma once

// Define Lift and Shuttle Positions to be used outside subsystem
constexpr double kShuttleMiddlePosition = 0;
constexpr double kShuttleFrontPosition = 11000;
constexpr double kShuttleRearPosition = -4500; // -3700 is for cable track tripping switch, -5200 is for near hard stop

constexpr double kLiftFloorPosition = 0;    // cargo pickup from floor
constexpr double kLiftBottomCargoPosition = 0;   // deliver cargo to bottom level
constexpr double kLiftBottomHatchPosition = 12;   // pickup hatch or deliver hatch to bottom level
constexpr double kLiftCargoShipPosition = 24;   // deliver cargo to cargo ship
constexpr double kLiftMiddleCargoPosition = 35;      // deliver cargo to middle rocket level
constexpr double kLiftMiddleHatchPosition = 45;      // deliver hatch to middle rocket level
constexpr double kLiftTopCargoPosition = 70;         // deliver cargo to top rocket level
constexpr double kLiftTopHatchPosition = 79;         // deliver hatch to top rocket level
constexpr double kLiftRemoveHatchFromWallPosition = kLiftBottomHatchPosition + 3;    // position for lifting hatch out of brushes from wall
