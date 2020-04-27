#pragma once
#include "MGL.h"

namespace Aftr
{

class WO;

class MGLNullModel : public MGL
{
public:
   static MGLNullModel* New( WO* parentWO );
   virtual ~MGLNullModel() {}
   virtual void render( const Camera& cam );
protected:
   MGLNullModel( WO* parentWO );
   virtual void onCreate();
};

}

