#pragma once
#ifdef AFTR_CONFIG_USE_CAL3D

#include "MGL.h"

class CAL3DModel;

namespace Aftr
{
class WO;

class MGLCal3D : public MGL
{
public:
   MGLCal3D( WO* parentWO, const std::string& cal3DConfigFile );
   virtual ~MGLCal3D();
   virtual void render( const Camera& cam );
   
   CAL3DModel* getCalModel();
protected:

   CAL3DModel* CalModel;

};

}

#endif //AFTR_CONFIG_USE_CAL3D
