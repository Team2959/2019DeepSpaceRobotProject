#pragma once

// Define Lift and Shuttle Positions to be used outside subsystem

constexpr double kLiftFloorPosition = 0;    // cargo pickup from floor
constexpr double kLiftBottomCargoPosition = 0;   // deliver cargo to bottom level
constexpr double kLiftBottomHatchPosition = 10;   // pickup hatch or deliver hatch to bottom level
constexpr double kLiftCargoShipPosition = 19;   // deliver cargo to cargo ship
constexpr double kLiftMiddleCargoPosition = 26.5;      // deliver cargo to middle rocket level
constexpr double kLiftMiddleHatchPosition = 36;      // deliver hatch to middle rocket level
constexpr double kLiftTopCargoPosition = 56;         // deliver cargo to top rocket level
constexpr double kLiftTopHatchPosition = 62;         // deliver hatch to top rocket level
constexpr double kLiftGrabHatchFromWallPosition = 6.5;    // position for lifting hatch out of brushes from wall
constexpr double kLiftRemoveHatchFromWallPosition = kLiftGrabHatchFromWallPosition + 5;    // position for lifting hatch out of brushes from wall
constexpr double kLiftCargoShipHatchPosition = 8; // deliver hatch to cargo ship
constexpr double kLiftClimbHab3Position = 28;
constexpr double kLiftClimbHab2Position = 8;
