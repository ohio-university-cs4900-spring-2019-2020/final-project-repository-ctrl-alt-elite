#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include "ModelParser.h"
#include "ModelMeshRenderDataGenerator.h"
#include "Vector.h"

namespace Aftr
{

   class ModelParserOBJ : public ModelParser
   {
   public:
      ModelParserOBJ( const std::string& filename, const Vector& scale, const MESH_SHADING_TYPE& shadingType );
      virtual ~ModelParserOBJ();
      ModelDataShared* parse();
   protected:

      struct Material
      {
         Material() {}
         float Kdr = 0, Kdg = 0, Kdb = 0; //diffuse color
         float Kar = 0, Kag = 0, Kab = 0; //ambient color
         float Ksr = 0, Ksg = 0, Ksb = 0; //specular color
         //float Ni;//ignoring optical density (refraction)
         //defaulting to 1, some materials (reasonably) omit transparency for non-transparent object
         float Tfr = 1, Tfg = 1, Tfb = 1; //don't know any obvious way to support this in OpenGL, without using an on the fly texture to store the information  will assume it's equipotent and use first value
         //int illum;//ignorning illumination model
         std::string map_Kd;//diffuse map
      };

      void parseMaterialLib( const std::string& filename );
      std::map< std::string, Material > materials;

      void duplicateVerticesWithUTextureCoordinatesNear0InFacesNear1(ModelMeshRenderDataGenerator* data);
      void duplicateVerticesWithVTextureCoordinatesNear0InFacesNear1(ModelMeshRenderDataGenerator* data);
   };

}

#endif
