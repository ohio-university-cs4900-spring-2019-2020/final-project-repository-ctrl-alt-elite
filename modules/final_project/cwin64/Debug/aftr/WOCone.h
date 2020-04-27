#pragma once

#include "WO.h"

namespace Aftr
{
   class WOCone: public WO
   {
   public:
      static WOCone* New( float bottomRadius = 1, float height = 1, unsigned int slices = 5, unsigned int stacks = 1, bool useNormals = false, bool useTextureCoords = false ); 
      virtual ~WOCone();
   protected:
      WOCone();
      virtual void onCreate( float bottomRadius = 1, float height = 1, unsigned int slices = 5, unsigned int stacks = 1, bool useNormals = false, bool useTextureCoords = false );
   };
}

