#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"

namespace Aftr
{

   /**

   \author Chad Mourning

  */

class WOTimedReset : public WOODE
{
public:
   static WOTimedReset* New( unsigned int timer, const std::string& model, Vector scale = Vector(1,1,1), bool enabled = true);
   virtual ~WOTimedReset();
   void enableReset() { enabled = true; }
   void disableReset() { enabled = false; }
   virtual void onPhysicsEngineTick();
   virtual void setPosition( const Vector& newXYZ );

protected:
   WOTimedReset( unsigned int timer, bool enabled = true );
   Vector positionToResetTo;
   unsigned int internalTimer;
   unsigned int resetTimer;
   bool enabled;

};

}

#endif
