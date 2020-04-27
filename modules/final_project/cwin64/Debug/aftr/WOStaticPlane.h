//----------------------------------------------------------------------------
//Description: The WOStaticPlane is an immovable plain with which moving 
//objects can collide. This serves as the simulation's FLOOR.
//
//Author: Scott Nykl (updated by Chad Mourning)
//----------------------------------------------------------------------------

#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOStatic.h"

//----------------------------------------------------------------------------
//Description: The WOFourWheeled class 
//----------------------------------------------------------------------------
namespace Aftr
{

class WOStaticPlane : public WOStatic
{

public:
   static WOStaticPlane* New( const std::string& modelFileName, const Vector& scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstFLAT );
   virtual ~WOStaticPlane();

   //Creates the ODE Geom of the static plain
   virtual void ODEinitializeInODE();

protected:
   WOStaticPlane();

};
} //namespace Aftr
#endif
