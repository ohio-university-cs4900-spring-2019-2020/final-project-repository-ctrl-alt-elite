#pragma once
#include "SteamieConfig.h"
#ifdef STM_CONFIG_USE_ODE
#include "WOBodyPart.h"
#include "IFaceShadowCaster.h"

namespace Steamie
{

class WOBodyPartShadowCasting : public WOBodyPart, public IFaceShadowCaster
{
public:
   static WOBodyPartShadowCasting* New( WO* parent, const std::string& bodyPartFile );
   virtual ~WOBodyPartShadowCasting() {}
protected:
   virtual void onCreate( const std::string& filename );
   WOBodyPartShadowCasting( WO* parent );
};

}

#endif
