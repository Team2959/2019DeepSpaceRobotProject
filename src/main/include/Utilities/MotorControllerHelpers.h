#pragma once

#include "ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h"

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
};
