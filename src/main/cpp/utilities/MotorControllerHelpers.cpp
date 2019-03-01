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

void MotorControllerHelpers::SetupSparkMax(rev::CANSparkMax& motor, double driveMaxCurrent)
{
  motor.RestoreFactoryDefaults();
  motor.ClearFaults();
  motor.SetSmartCurrentLimit(driveMaxCurrent);
  motor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  motor.SetParameter(rev::CANSparkMaxLowLevel::ConfigParameter::kHardLimitFwdEn, false);
  motor.SetParameter(rev::CANSparkMaxLowLevel::ConfigParameter::kHardLimitRevEn, false);
  motor.SetParameter(rev::CANSparkMaxLowLevel::ConfigParameter::kSoftLimitFwdEn, false);
  motor.SetParameter(rev::CANSparkMaxLowLevel::ConfigParameter::kSoftLimitRevEn, false);

  motor.SetPeriodicFramePeriod(rev::CANSparkMaxLowLevel::PeriodicFrame::kStatus0, 100);
  motor.SetPeriodicFramePeriod(rev::CANSparkMaxLowLevel::PeriodicFrame::kStatus1, 200);
  motor.SetPeriodicFramePeriod(rev::CANSparkMaxLowLevel::PeriodicFrame::kStatus2, 200);
}

void MotorControllerHelpers::DashboardInitSparkMax(
    std::string name,
    rev::CANEncoder & encoder,
    double kP, double kI, double kD,
    double iZone, double ff,
    double outputMin, double outputMax)
{
  // display PID coefficients on SmartDashboard
  frc::SmartDashboard::PutNumber(name + ": P Gain", kP);
  frc::SmartDashboard::PutNumber(name + ": I Gain", kI);
  frc::SmartDashboard::PutNumber(name + ": D Gain", kD);
  frc::SmartDashboard::PutNumber(name + ": I Zone", iZone);
  frc::SmartDashboard::PutNumber(name + ": Feed Forward", ff);
  frc::SmartDashboard::PutNumber(name + ": Ouput Min", outputMin);
  frc::SmartDashboard::PutNumber(name + ": Ouput Max", outputMax);

  frc::SmartDashboard::PutNumber(name + ": Go To Position", 0);
  frc::SmartDashboard::PutNumber(name + ": Target", 0);
  frc::SmartDashboard::PutNumber(name + ": Position", encoder.GetPosition());
  frc::SmartDashboard::PutNumber(name + ": Velocity", encoder.GetVelocity());
}

void MotorControllerHelpers::DashboardDataSparkMax3(
    std::string name,
    rev::CANPIDController & pidConfig,
    rev::CANPIDController & pidConfig2,
    rev::CANPIDController & pidConfig3,
    rev::CANEncoder & encoder)
{
  frc::SmartDashboard::PutNumber(name + ": Position", encoder.GetPosition());
  frc::SmartDashboard::PutNumber(name + ": Velocity", encoder.GetVelocity());

  auto myP = pidConfig.GetP();
  auto myI = pidConfig.GetI();
  auto myD = pidConfig.GetD();
  auto myIzone = pidConfig.GetIZone();
  auto myFF = pidConfig.GetFF();
  auto myOmin = pidConfig.GetOutputMin();
  auto myOmax = pidConfig.GetOutputMax();

  // display PID coefficients on SmartDashboard
  auto kP = frc::SmartDashboard::GetNumber(name + ": P Gain", myP);
  auto kI = frc::SmartDashboard::GetNumber(name + ": I Gain", myI);
  auto kD = frc::SmartDashboard::GetNumber(name + ": D Gain", myD);
  auto kIz = frc::SmartDashboard::GetNumber(name + ": I Zone", myIzone);
  auto kF = frc::SmartDashboard::GetNumber(name + ": Feed Forward", myFF);
  auto outputMin = frc::SmartDashboard::GetNumber(name + ": Ouput Min", myOmin);
  auto outputMax = frc::SmartDashboard::GetNumber(name + ": Ouput Max", myOmax);

  if (fabs(kP - myP) > 0.0001)
  {
    pidConfig.SetP(kP);
    pidConfig2.SetP(kP);
    pidConfig3.SetP(kP);  
  }
  if (fabs(kI - myI) > 0.0001)
  {
    pidConfig.SetI(kI);
    pidConfig2.SetI(kI);
    pidConfig3.SetI(kI);
  }
  if (fabs(kD - myD) > 0.0001)
  {
    pidConfig.SetD(kD);
    pidConfig2.SetP(kD);
    pidConfig3.SetP(kD);
  }
  if (fabs(kF - myFF) > 0.0001)
  {
    pidConfig.SetFF(kF);
    pidConfig2.SetFF(kF);
    pidConfig3.SetFF(kF);
  }
  if (fabs(kIz - myIzone) > 0.0001)
  {
    pidConfig.SetIZone(kIz);
    pidConfig2.SetIZone(kIz);
    pidConfig3.SetIZone(kIz);
  }
  if (fabs(outputMin - myOmin) > 0.0001 ||
        fabs(outputMax - myOmax) > 0.0001)
  {
    pidConfig.SetOutputRange(outputMin, outputMax);
    pidConfig2.SetOutputRange(outputMin, outputMax);
    pidConfig3.SetOutputRange(outputMin, outputMax);
  }
}

void MotorControllerHelpers::DashboardDataSparkMax2(
    std::string name,
    rev::CANPIDController & pidConfig,
    rev::CANPIDController & pidConfig2,
    rev::CANEncoder & encoder)
{
  frc::SmartDashboard::PutNumber(name + ": Position", encoder.GetPosition());
  frc::SmartDashboard::PutNumber(name + ": Velocity", encoder.GetVelocity());

  auto myP = pidConfig.GetP();
  auto myI = pidConfig.GetI();
  auto myD = pidConfig.GetD();
  auto myIzone = pidConfig.GetIZone();
  auto myFF = pidConfig.GetFF();
  auto myOmin = pidConfig.GetOutputMin();
  auto myOmax = pidConfig.GetOutputMax();

  // display PID coefficients on SmartDashboard
  auto kP = frc::SmartDashboard::GetNumber(name + ": P Gain", myP);
  auto kI = frc::SmartDashboard::GetNumber(name + ": I Gain", myI);
  auto kD = frc::SmartDashboard::GetNumber(name + ": D Gain", myD);
  auto kIz = frc::SmartDashboard::GetNumber(name + ": I Zone", myIzone);
  auto kF = frc::SmartDashboard::GetNumber(name + ": Feed Forward", myFF);
  auto outputMin = frc::SmartDashboard::GetNumber(name + ": Ouput Min", myOmin);
  auto outputMax = frc::SmartDashboard::GetNumber(name + ": Ouput Max", myOmax);

  if (fabs(kP - myP) > 0.0001)
  {
    pidConfig.SetP(kP);
    pidConfig2.SetP(kP);
  }
  if (fabs(kI - myI) > 0.0001)
  {
    pidConfig.SetI(kI);
    pidConfig2.SetI(kI);
  }
  if (fabs(kD - myD) > 0.0001)
  {
    pidConfig.SetD(kD);
    pidConfig2.SetD(kD);
  }
  if (fabs(kF - myFF) > 0.0001)
  {
    pidConfig.SetFF(kF);
    pidConfig2.SetFF(kF);
  }
  if (fabs(kIz - myIzone) > 0.0001)
  {
    pidConfig.SetIZone(kIz);
    pidConfig2.SetIZone(kIz);
  }
  if (fabs(outputMin - myOmin) > 0.0001 ||
        fabs(outputMax - myOmax) > 0.0001)
  {
    pidConfig.SetOutputRange(outputMin, outputMax);
    pidConfig2.SetOutputRange(outputMin, outputMax);
  }
}
