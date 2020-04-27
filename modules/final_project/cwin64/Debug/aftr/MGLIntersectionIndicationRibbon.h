#pragma once

#include "MGL.h"
#include <map>

namespace Aftr
{

   struct RibbonDataPoint
   {
      Vector position;
      Vector lookDirection;
      Vector normal;
      bool color;
   };

   class MGLIntersectionIndicationRibbon : public MGL
   {
   public:
      MGLIntersectionIndicationRibbon( WO* parentWO );
      virtual ~MGLIntersectionIndicationRibbon();
      void setDataPoint(unsigned int slot, const Vector& position, const Vector& lookDirection, const Vector& normalDirection, bool color);
      virtual void render( const Camera& cam );
      void clear();
   protected:
      std::map<unsigned int, RibbonDataPoint> m;
   };

}

