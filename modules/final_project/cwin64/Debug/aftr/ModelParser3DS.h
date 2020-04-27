#pragma once

#include "ModelParser.h"
#include "ModelMeshRenderDataGenerator.h"
#include "Vector.h"

namespace Aftr
{

   class ModelParser3DS : public ModelParser
   {
   public:
      ModelParser3DS( const std::string& filename, const Vector& scale, const MESH_SHADING_TYPE& shadingType );
      virtual ~ModelParser3DS();
      ModelDataShared* parse();
      struct indexData
      {
         unsigned int a, b, c;
         unsigned int materialIndex;
      };

      struct vertexData
      {
         Vector* v;
         aftrTexture4f tex;
      };
   protected:
   };

}

