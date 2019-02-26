/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

class FollowPath : public frc::Command {
 public:
  FollowPath();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

  private:
  double UnitCoversion(double x);
  std::vector<double> m_right;
  std::vector<double> m_left;
  std::vector<double> m_heading;
  double ConversionFactor = (1/(M_PI*4))*60;
  int m_index = 0;
};
