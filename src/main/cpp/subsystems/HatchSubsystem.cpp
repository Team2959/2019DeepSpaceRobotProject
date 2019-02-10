/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchSubsystem.h"

HatchSubsystem::HatchSubsystem() : Subsystem("HatchSubsystem") {}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void HatchSubsystem::PrepForHatch(){
  // m_attach.Set(false);
  m_release.Set(false);
  m_safety.Set(true);
}

void HatchSubsystem::SecureHatch(){
  // m_attach.Set(false);
  m_release.Set(false);
  m_safety.Set(false);
}

void HatchSubsystem::AttachHatch(){
  m_attach.Set(true);
  m_release.Set(false);
  m_safety.Set(false);
}

void HatchSubsystem::ReleaseHatch(){
  m_attach.Set(true);
  m_release.Set(true);
  m_safety.Set(false);
}

void HatchSubsystem::RetractMechanism(){
  m_attach.Set(false);
  m_release.Set(false);
  m_safety.Set(false);
}
