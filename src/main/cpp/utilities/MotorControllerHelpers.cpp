#include "Utilities/MotorControllerHelpers.h"
#include <frc/smartdashboard/SmartDashboard.h>

void MotorControllerHelpers::ConfigureTalonSrxMotorController(
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX & motorController,
    ctre::phoenix::motorcontrol::can::SlotConfiguration & pidConfig,
    bool sensorPhase)
{
    motorController.ConfigSelectedFeedbackSensor(
        ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);

	motorController.Config_kP(0, pidConfig.kP, 0);
	motorController.Config_kI(0, pidConfig.kI, 0);
	motorController.Config_kD(0, pidConfig.kD, 0);
    motorController.Config_kF(0, pidConfig.kF, 0);
	motorController.Config_IntegralZone(0, pidConfig.integralZone, 0);

	motorController.SetSensorPhase(sensorPhase);
	motorController.SetSelectedSensorPosition(0,0,0);

	motorController.ConfigPeakOutputForward(pidConfig.closedLoopPeakOutput, 0);
	motorController.ConfigPeakOutputReverse(-pidConfig.closedLoopPeakOutput, 0);
//	motorController.ConfigPeakCurrentLimit(5, 0);

	motorController.ConfigAllowableClosedloopError(0, pidConfig.allowableClosedloopError, 0);
//	motorController.ConfigClosedloopRamp(0, 0);
}

void MotorControllerHelpers::DashboardInitTalonSrx(
    std::string name,
    ctre::phoenix::motorcontrol::can::SlotConfiguration & pidConfig)
{
  // display PID coefficients on SmartDashboard
  frc::SmartDashboard::PutNumber(name + ": P Gain", pidConfig.kP);
  frc::SmartDashboard::PutNumber(name + ": I Gain", pidConfig.kI);
  frc::SmartDashboard::PutNumber(name + ": D Gain", pidConfig.kD);
  frc::SmartDashboard::PutNumber(name + ": I Zone", pidConfig.integralZone);
  frc::SmartDashboard::PutNumber(name + ": Feed Forward", pidConfig.kF);
  frc::SmartDashboard::PutNumber(name + ": Closed Loop Err", pidConfig.allowableClosedloopError);
  // frc::SmartDashboard::PutNumber(name + ": Max Int Acc", pidConfig.maxIntegralAccumulator);
  frc::SmartDashboard::PutNumber(name + ": Cl Loop Peak Output", pidConfig.closedLoopPeakOutput);
  // frc::SmartDashboard::PutNumber(name + ": Cl Loop Period", pidConfig.closedLoopPeriod);

  frc::SmartDashboard::PutNumber(name + ": Go To Position", 0);
  frc::SmartDashboard::PutNumber(name + ": Target", 0);
  frc::SmartDashboard::PutNumber(name + ": Position", 0);
  frc::SmartDashboard::PutNumber(name + ": Velocity", 0);
}

void MotorControllerHelpers::DashboardDataTalonSrx(
    std::string name,
    ctre::phoenix::motorcontrol::can::WPI_TalonSRX & motorController,
    ctre::phoenix::motorcontrol::can::SlotConfiguration & pidConfig)
{
  // display PID coefficients on SmartDashboard
  auto kP = frc::SmartDashboard::GetNumber(name + ": P Gain", pidConfig.kP);
  auto kI = frc::SmartDashboard::GetNumber(name + ": I Gain", pidConfig.kI);
  auto kD = frc::SmartDashboard::GetNumber(name + ": D Gain", pidConfig.kD);
  auto kIz = frc::SmartDashboard::GetNumber(name + ": I Zone", pidConfig.integralZone);
  auto kF = frc::SmartDashboard::GetNumber(name + ": Feed Forward", pidConfig.kF);
  auto error = frc::SmartDashboard::GetNumber(name + ": Closed Loop Err", pidConfig.allowableClosedloopError);
  // auto accumulator = frc::SmartDashboard::GetNumber(name + ": Max Int Acc", pidConfig.maxIntegralAccumulator);
  auto peakOutput = frc::SmartDashboard::GetNumber(name + ": Cl Loop Peak Output", pidConfig.closedLoopPeakOutput);
  // auto period = frc::SmartDashboard::GetNumber(name + ": Cl Loop Period", pidConfig.closedLoopPeriod);

  if (fabs(kP - pidConfig.kP) > 0.0001)
  {
    pidConfig.kP = kP;
    motorController.Config_kP(0, kP, 0);
  }
  if (fabs(kI - pidConfig.kI) > 0.0001)
  {
    pidConfig.kI = kI;
    motorController.Config_kI(0, kI, 0);
  }
  if (fabs(kD - pidConfig.kD) > 0.0001)
  {
    pidConfig.kD = kD;
    motorController.Config_kD(0, kD, 0);
  }
  if (fabs(kF - pidConfig.kF) > 0.0001)
  {
    pidConfig.kF = kF;
    motorController.Config_kF(0, kF, 0);
  }
  if (fabs(kIz - pidConfig.integralZone) > 0.0001)
  {
    pidConfig.integralZone = kIz;
    motorController.Config_IntegralZone(0, kIz, 0);
  }
  if (fabs(error - pidConfig.allowableClosedloopError) > 0.0001)
  {
    pidConfig.allowableClosedloopError = error;
    motorController.ConfigAllowableClosedloopError(0, error, 0);
  }
  if (fabs(peakOutput - pidConfig.closedLoopPeakOutput) > 0.0001)
  {
    pidConfig.closedLoopPeakOutput = peakOutput;
    motorController.ConfigPeakOutputForward(peakOutput, 0);
    motorController.ConfigPeakOutputReverse(-peakOutput, 0);
  }
}

void MotorControllerHelpers::DashboardInitSparkMax(
    std::string name,
    rev::CANPIDController & pidConfig)
{
  // display PID coefficients on SmartDashboard
  frc::SmartDashboard::PutNumber(name + ": P Gain", pidConfig.GetP());
  frc::SmartDashboard::PutNumber(name + ": I Gain", pidConfig.GetI());
  frc::SmartDashboard::PutNumber(name + ": D Gain", pidConfig.GetD());
  frc::SmartDashboard::PutNumber(name + ": I Zone", pidConfig.GetIZone());
  frc::SmartDashboard::PutNumber(name + ": Feed Forward", pidConfig.GetFF());
  frc::SmartDashboard::PutNumber(name + ": Ouput Min", pidConfig.GetOutputMin());
  frc::SmartDashboard::PutNumber(name + ": Ouput Max", pidConfig.GetOutputMax());

  frc::SmartDashboard::PutNumber(name + ": Go To Position", 0);
  frc::SmartDashboard::PutNumber(name + ": Target", 0);
  frc::SmartDashboard::PutNumber(name + ": Position", 0);
  frc::SmartDashboard::PutNumber(name + ": Velocity", 0);
}

void MotorControllerHelpers::DashboardDataSparkMax(
    std::string name,
    rev::CANPIDController & pidConfig)
{
  // display PID coefficients on SmartDashboard
  auto kP = frc::SmartDashboard::GetNumber(name + ": P Gain", pidConfig.GetP());
  auto kI = frc::SmartDashboard::GetNumber(name + ": I Gain", pidConfig.GetI());
  auto kD = frc::SmartDashboard::GetNumber(name + ": D Gain", pidConfig.GetD());
  auto kIz = frc::SmartDashboard::GetNumber(name + ": I Zone", pidConfig.GetIZone());
  auto kF = frc::SmartDashboard::GetNumber(name + ": Feed Forward", pidConfig.GetFF());
  auto outputMin = frc::SmartDashboard::GetNumber(name + ": Ouput Min", pidConfig.GetOutputMin());
  auto outputMax = frc::SmartDashboard::GetNumber(name + ": Ouput Max", pidConfig.GetOutputMax());

  if (fabs(kP - pidConfig.GetP()) > 0.0001)
  {
    pidConfig.SetP(kP);
  }
  if (fabs(kI - pidConfig.GetI()) > 0.0001)
  {
    pidConfig.SetI(kI);
  }
  if (fabs(kD - pidConfig.GetD()) > 0.0001)
  {
    pidConfig.SetD(kD);
  }
  if (fabs(kF - pidConfig.GetFF()) > 0.0001)
  {
    pidConfig.SetFF(kF);
  }
  if (fabs(kIz - pidConfig.GetIZone()) > 0.0001)
  {
    pidConfig.SetIZone(kIz);
  }
  if (fabs(outputMin - pidConfig.GetOutputMin()) > 0.0001 ||
        fabs(outputMax - pidConfig.GetOutputMin()) > 0.0001)
  {
    pidConfig.SetOutputRange(outputMin, outputMax);
  }
}
