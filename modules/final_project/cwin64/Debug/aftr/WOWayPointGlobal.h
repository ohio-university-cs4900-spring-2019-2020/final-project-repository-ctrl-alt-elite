#pragma once

#include "WOWayPointAbstract.h"

namespace Aftr
{

class WOWayPointGlobal : public WOWayPointAbstract
{
public:
   static WOWayPointGlobal* New(const WayPointParametersBase& params);
   virtual void onPhysicsEngineTick();
protected:
   WOWayPointGlobal(const WayPointParametersBase& params);
   virtual void onCreate();
   virtual bool activate(WO* activator);
   virtual void onTrigger();
};

}

