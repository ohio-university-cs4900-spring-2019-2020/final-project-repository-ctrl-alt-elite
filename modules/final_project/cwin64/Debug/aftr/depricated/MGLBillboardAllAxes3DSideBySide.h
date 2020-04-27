#pragma once

#include "MGLBillboardAllAxes.h"

namespace Aftr
{

class MGLBillboardAllAxes3DSideBySide : public MGLBillboardAllAxes
{
public:
   virtual ~MGLBillboardAllAxes3DSideBySide();
      static MGLBillboardAllAxes3DSideBySide* New( WO* parent, float height, float width );
      bool usingRightEye;
   protected:
      virtual void onCreate();
      MGLBillboardAllAxes3DSideBySide( WO* parent, float height, float width );
      virtual void render( const Camera& cam );
};

}

