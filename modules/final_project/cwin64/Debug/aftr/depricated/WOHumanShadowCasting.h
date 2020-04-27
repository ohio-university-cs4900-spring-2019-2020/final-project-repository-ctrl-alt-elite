#pragma once
#include "SteamieConfig.h"
#ifdef STM_CONFIG_USE_ODE
#include "WOHuman.h"
#include "IFaceShadowCaster.h"

namespace Steamie
{

   class WOBodyPartShadowCasting;

class WOHumanShadowCasting : public WOHuman, public IFaceShadowCaster
{
public:
   static WOHumanShadowCasting* New( const Vector& lxlylz, float mass );
   virtual ~WOHumanShadowCasting() {};
protected:
   WOHumanShadowCasting( float mass );
   virtual void constructHuman();
};

}

#endif
