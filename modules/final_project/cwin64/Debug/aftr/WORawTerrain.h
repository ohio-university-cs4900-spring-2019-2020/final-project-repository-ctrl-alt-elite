#pragma once

#include "WO.h"

namespace Aftr
{
   class WORawTerrain : public WO
   {
   public:
      static WORawTerrain* New( float* vertices, unsigned int x, unsigned int y, double xIgnoredPercentage, double yIgnoredColorPercentage );//3 float for each vertex in the model, x*y vertices, will need triangularized
      virtual ~WORawTerrain();
   protected:
      WORawTerrain();
      virtual void onCreate( float* vertices, unsigned int x, unsigned int y, double xIgnoredPercentage, double yIgnoredColorPercentage ); 
   };
};

