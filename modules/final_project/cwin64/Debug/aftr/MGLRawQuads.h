#pragma once
#include "MGL.h"

namespace Aftr
{
   class MGLRawQuads : public MGL
   {
   public:
      static MGLRawQuads* New( WO* parent, float* vertices, unsigned int numQuads );//3 float for each vertex in the model, topology is assumed that each triangle is seperate (flat), some sort of merging is possible
      static MGLRawQuads* New( WO* parent, float* vertices, unsigned int numQuads, const std::vector< aftrColor4ub >& perVertexColor );
      virtual ~MGLRawQuads();
      virtual void render( const Camera& cam );
      virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );

      virtual void getQuadGlobalPositionAndNormal( unsigned int quadIdx, Vector& outGlobalCenterPos, Vector& outGlobalNormalDir, Vector& outLengthInXHeightInYNothingInZ );
   protected:
      MGLRawQuads( WO* parent );
      virtual void onCreate( float* vertices, unsigned int numQuads );
      virtual void onCreate( float* vertices, unsigned int numQuads, const std::vector< aftrColor4ub >& perVertexColor );

      void createLineVertices(float* vertices, unsigned int numQuads);
      void createLineIndices(float* vertices, unsigned int numQuads);

      GLvoid* linesVAVtx;
      GLvoid* linesVAIdx;
      GLuint linesVAVtxSize;
      GLuint linesVAIdxSize;
      GLenum linesVAIdxMemType;
   };
};