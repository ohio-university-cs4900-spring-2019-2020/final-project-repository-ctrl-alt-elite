#pragma once

#include "ModelMeshRenderData.h"

namespace Aftr
{

   class ModelMeshRenderDataGL_POINTS : public ModelMeshRenderData
   {
   public:
      ModelMeshRenderDataGL_POINTS();

      ModelMeshRenderDataGL_POINTS(
         GLvoid* VAIdx, 
         void* VAVtx,
         GLsizei idxSize,
         GLsizei vtxSize,
         GLenum idxMemType,
         GLsizei vtxStride,
         bool isUsingColorsArray,
         GLenum numColorChannels,
         unsigned int vertsOffset,
         unsigned int colorsOffset,
         unsigned int normalsOffset,
         const std::vector< unsigned int >& texCoordsOffset,
         const std::vector< unsigned int >& attributesOffset,
         const std::vector< GLSLAttributeType >& attributesType,
         const std::map< std::string, GLuint >& attributesNameToIndex );

      ModelMeshRenderDataGL_POINTS( const ModelMeshRenderDataGL_POINTS& toCopy );
      virtual ~ModelMeshRenderDataGL_POINTS();

      ModelMeshRenderDataGL_POINTS& operator =( const ModelMeshRenderDataGL_POINTS& r );

   protected:

   };


} //namespace Aftr

