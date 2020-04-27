#pragma once
#ifdef AFTR_CONFIG_USE_CAL3D

#include "WOCal3D.h"

namespace Aftr
{

class WOCal3DPaladin : public WOCal3D
{
public:
   static WOCal3DPaladin* New();
   virtual ~WOCal3DPaladin();
   virtual void render( const Camera& cam );

protected:
   WOCal3DPaladin();
   virtual void onCreate( const std::string& cal3DConfigFile );

};

} //namespace Aftr
#endif //AFTR_CONFIG_USE_CAL3D
