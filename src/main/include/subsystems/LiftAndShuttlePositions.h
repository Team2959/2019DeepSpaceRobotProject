#pragma once

// Define Lift and Shuttle Positions to be used outside subsystem
constexpr double kShuttleMiddlePosition = 0;
constexpr double kShuttleFrontPosition = 11400;
constexpr double kShuttleRearPosition = -3700; // -3700 is for cable track tripping switch, -5200 is for near hard stop

constexpr double kLiftFloorPosition = 0;    // cargo pickup from floor
constexpr double kLiftBottomPosition = 4;   // pickup hatch or deliver hatch or cargo to bottom level
constexpr double kLiftCargoShipPosition = 24;   // deliver cargo to cargo ship
constexpr double kLiftMiddlePosition = 40;      // deliver to middle rocket level
constexpr double kLiftTopPosition = 55;         // deliver to top rocket level
constexpr double kLiftRemoveHatchFromWallPosition = kLiftBottomPosition + 2;    // position for lifting hatch out of brushes from wall
constexpr double kLiftRocketCargoOffset = 0;    // adjustment to vertical position when delivering cargo to rocket, which is offset from hatch level
