#pragma once

#include "WOSimpleOrbiter.h"
#include "IFaceShadowCaster.h"

namespace Steamie
{

class WOSimpleOrbiterShadowCasting : public WOSimpleOrbiter, public IFaceShadowCaster
{
public:
   static WOSimpleOrbiterShadowCasting* New(const std::string& str);
   virtual ~WOSimpleOrbiterShadowCasting();
protected:
   virtual void createChildren();
   virtual void onCreate(const std::string& str);
   WOSimpleOrbiterShadowCasting();

};


}

