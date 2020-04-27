//----------------------------------------------------------------------------
//Description: The  class
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOFlyer5Thruster.h"

//----------------------------------------------------------------------------
//Description: The WOVehicleFourWheeled class 
//----------------------------------------------------------------------------
namespace Aftr
{

class WOForceThruster;

class WOF16Thrustable : public WOFlyer5Thruster
{
public:
   static WOF16Thrustable* New( const std::string& modelFileName, Vector scale = Vector(1,1,1) );
   virtual ~WOF16Thrustable();

   #ifdef AFTR_CONFIG_USE_TNL
      //Network Subsystem Specific ----------------------------------------------
      virtual void packNetState( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      virtual void unPackNetState( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      //-------------------------------------------------------------------------
   #endif

protected:
   WOF16Thrustable();

};
} //namespace Aftr
#endif
