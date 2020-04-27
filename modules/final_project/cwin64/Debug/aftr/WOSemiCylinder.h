#pragma once

#include "WO.h"

namespace Aftr
{
   class WOSemiCylinder: public WO
   {
   public:
      static WOSemiCylinder* New( float topRadius = 1, float bottomRadius = 1, float height = 1, unsigned int slices = 5, unsigned int stacks = 1, bool useNormals = false, bool useTextureCoords = false ); 
      virtual ~WOSemiCylinder();
   protected:
      WOSemiCylinder();
      virtual void onCreate( float topRadius = 1, float bottomRadius = 1, float height = 1, unsigned int slices = 5, unsigned int stacks = 1, bool useNormals = false, bool useTextureCoords = false );
   };
}

