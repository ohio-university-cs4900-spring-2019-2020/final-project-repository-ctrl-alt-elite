#pragma once

#include "ModelMeshRenderDataGenerator.h"

namespace Aftr
{

class ModelMeshRenderDataGeneratorGL_POINTS : public ModelMeshRenderDataGenerator
{
public:
   ModelMeshRenderDataGeneratorGL_POINTS();
   virtual ~ModelMeshRenderDataGeneratorGL_POINTS();

   virtual ModelMeshRenderData generate( MESH_SHADING_TYPE shadingType );
   virtual ModelMeshRenderData generateFlat();
   virtual ModelMeshRenderData generateSmooth();
   virtual ModelMeshRenderData generateNoNormals();

protected:

};

} //namespace Aftr

