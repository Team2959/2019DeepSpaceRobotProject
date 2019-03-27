#pragma once

// Define Lift and Shuttle Positions to be used outside subsystem

constexpr double kLiftFloorPosition = 0;    // cargo pickup from floor
constexpr double kLiftBottomCargoPosition = 0;   // deliver cargo to bottom level
constexpr double kLiftBottomHatchPosition = 14;   // pickup hatch or deliver hatch to bottom level
constexpr double kLiftCargoShipPosition = 28;   // deliver cargo to cargo ship
constexpr double kLiftMiddleCargoPosition = 35;      // deliver cargo to middle rocket level
constexpr double kLiftMiddleHatchPosition = 51;      // deliver hatch to middle rocket level
constexpr double kLiftTopCargoPosition = 70;         // deliver cargo to top rocket level
constexpr double kLiftTopHatchPosition = 79;         // deliver hatch to top rocket level
constexpr double kLiftGrabHatchFromWallPosition = 10;    // position for lifting hatch out of brushes from wall
constexpr double kLiftRemoveHatchFromWallPosition = kLiftGrabHatchFromWallPosition + 10;    // position for lifting hatch out of brushes from wall
constexpr double kLiftCargoShipHatchPosition = kLiftBottomHatchPosition + 3; // deliver hatch to cargo ship
constexpr double kLiftClimbPrepHab3Position = 35;
constexpr double kLiftClimbPrepHab2Position = 16;
constexpr double kLiftClimbHab3Position = 30.5;
constexpr double kLiftClimbHab2Position = 11;
constexpr double kLiftRaiseClimbWheelsPosition = 4;
