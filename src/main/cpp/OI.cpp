/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>
#include "commands/PrepForHatchCommand.h"  
#include "commands/SecureHatchCommand.h" 
#include "commands/AttachHatchCommand.h"  
#include "commands/ReleaseHatchCommand.h"  
#include "commands/RetractMechanismCommand.h"   

OI::OI() {
  // Process operator interface input here.
  m_prepForHatch.WhenPressed(new PrepForHatchCommand());
  m_secureHatch.WhenPressed(new SecureHatchCommand());
  m_attachHatch.WhenPressed(new AttachHatchCommand());
  m_releaseHatch.WhenPressed(new ReleaseHatchCommand());
  m_retractMechanismHatch.WhenPressed(new RetractMechanismCommand());
}
