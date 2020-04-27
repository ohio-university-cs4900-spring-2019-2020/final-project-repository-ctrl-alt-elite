#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOStatic.h"

namespace Aftr
{

class WORampMovable : public WOStatic
{
public:
   static WORampMovable* New( const Vector& scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );
   virtual ~WORampMovable();

   bool isSpinningAboutAbsZ() { return this->IsSpinningAboutAbsZ; }
   void startSpinning( float radPerSecAboutGlobalZ );
   void stopSpinning();

   bool isMoving() { return this->IsMoving; }
   void startMoving( const Vector& vel );
   void stopMoving();

   virtual void onKeyDown( const SDL_KeyboardEvent& key );
	virtual void onKeyUp( const SDL_KeyboardEvent& key );


   ///Creates the ODE Prims of the car body and wheels and the joints between them.
   virtual void ODEinitializeInODE();

   ///1. Apply forces to the bodies as necessary.
   ///2. Adjust the joint parameters as necessary.
   virtual void ODEupdateForcesAndJoints();

protected:
   WORampMovable();

   float theta;
   bool IsSpinningAboutAbsZ;
   float angRotVel;
   bool IsMoving;
};

}

#endif
