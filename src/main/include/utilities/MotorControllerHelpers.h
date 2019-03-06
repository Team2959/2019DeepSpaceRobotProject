#pragma once

#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"
#include <rev/CANPIDController.h>
#include <rev/CANEncoder.h>
#include <rev/CANSparkMax.h>

constexpr double kCloseToSameValue = 0.0000001;

// Functions to consolidate configuration of motor controllers
//  and interact with smart dashboard to setup/troubleshoot

class MotorControllerHelpers
{
private:
public:
    static void ConfigureTalonSrxMotorController(
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX & motorController,
        ctre::phoenix::motorcontrol::can::SlotConfiguration & pidConfig,
        bool sensorPhase);

    static void DashboardInitTalonSrx(
        std::string name,
        ctre::phoenix::motorcontrol::can::SlotConfiguration & pidConfig);

    static void DashboardDataTalonSrx(
        std::string name,
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX & motorController,
        ctre::phoenix::motorcontrol::can::SlotConfiguration & pidConfig);

    static void SetupSparkMax(rev::CANSparkMax& motor, double driveMaxCurrent, bool reduceCanTraffic);

    static void DashboardInitSparkMax(
        std::string name,
        rev::CANEncoder & encoder,
        double kP = 5e-5, double kI = 1e-6, double kD = 0,
        double iZone = 0, double ff = 0,
        double outputMin = -1, double outputMax = 1);

    static void DashboardDataSparkMax(
        std::string name,
        rev::CANPIDController & pidConfig,
        rev::CANEncoder & encoder);

    static void DashboardDataSparkMax2(
        std::string name,
        rev::CANPIDController & pidConfig,
        rev::CANPIDController & pidConfig2,
        rev::CANEncoder & encoder);
};
