#pragma once
#include "SteamieConfig.h"
#ifdef STM_CONFIG_USE_ODE
#include "WOHuman.h"
#include "IFaceShadowCaster.h"

namespace Steamie
{

   class WOHumanCyborgShadowCaster : public WOHuman, public IFaceShadowCaster
{
public:
   static WOHumanCyborgShadowCaster* New(const Vector& lxlylz, float mass);
   virtual ~WOHumanCyborgShadowCaster();
   virtual void onPhysicsEngineTick();
protected:
   virtual void onCreate(const Vector& lxlylz, float mass);
   WOHumanCyborgShadowCaster( float mass );
   virtual void constructHuman();
};

}

#endif
