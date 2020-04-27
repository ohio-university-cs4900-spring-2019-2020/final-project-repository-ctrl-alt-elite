#pragma once

#include "WOBillboardAllAxes.h"

namespace Aftr
{
   class WOBillboardAllAxes3DSideBySide : public WOBillboardAllAxes
   {
   public:
      static WOBillboardAllAxes3DSideBySide* New( float height, float width );
      virtual ~WOBillboardAllAxes3DSideBySide();
   protected:
      WOBillboardAllAxes3DSideBySide();
      virtual void onCreate( float height, float width );
   };
}

