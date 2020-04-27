#pragma once
#include "AftrConfig.h"

#ifdef AFTR_CONFIG_USE_ODE
#include "ode/ode.h"
#include "AftrGlobals.h"

namespace Aftr
{
   class IFaceWOODE;
   enum class ODE_PRIM_TYPE : unsigned char;

   /**
      These global methods should only exist if ODE is being used
      ODE Interface Prototypes
   */
      
   ///Synchronizes the graphical model to ODE's corresponding position and orientation after and ODE worldStep()
   void updateObjectPositionOrientation( IFaceWOODE* ifaceWO );
   /**
      Creates one (of the possibly many) ODE primitives that represent the graphical model inside 
      corresponding the WO. The model's dimensions are available within this method for ODE to use.
   */
   void createODEPrimitive( IFaceWOODE* ifaceWO, ODE_PRIM_TYPE primType );
   void createODEStaticPrimitive( IFaceWOODE* ifaceWO, ODE_PRIM_TYPE primType );
   dWorldID getODEdWorldID();
   dSpaceID getODEdSpaceID();
   ///ODE Utility function used to convert a 4x3 ODE Matrix to a 4x4 Aftr::Model Matrix
   void convertToModelDMat( const dReal* geomDMat, float* modelDMat );
   ///ODE Utility function used to convert a 4x4 Aftr::Model Matrix to a 4x3 ODE Matrix  
   void convertToGeomDMat( dReal* geomDMat, const float* modelDMat );

} //namespace Aftr
#endif

