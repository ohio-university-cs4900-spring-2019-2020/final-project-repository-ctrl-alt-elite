#pragma once

#include "WO.h"

namespace Aftr
{

   class WOBillboardAllAxes : public WO
   {
   public:
      static WOBillboardAllAxes* New( float height, float width );
      virtual ~WOBillboardAllAxes();
   protected:
      WOBillboardAllAxes();
      virtual void onCreate( float height, float width );
   };

};

