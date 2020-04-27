#pragma once

#include "MGL.h"
#include "AftrOpenGLIncludes.h"

namespace Aftr
{

class MGLPointSetShaderAccelerated : public MGL
{
public:
   static MGLPointSetShaderAccelerated* New( WO* parentWO, ModelDataShared* perInstanceVAModelData, bool autoSplitMeshDuringConstruction = false, int numSplits = 5 );
   static MGLPointSetShaderAccelerated* New( WO* parentWO, const std::vector< Vector >& verts,
                                            const std::vector< unsigned int >& indices,
                                            GLenum glPrimType = GL_TRIANGLES, bool autoSplitMeshDuringConstruction = false, int numSplits = 5,
                                            Aftr::aftrColor4ub color = aftrColor4ub(0,255,255,255) );
   virtual ~MGLPointSetShaderAccelerated();

   virtual bool isInViewingFrustum( const AftrGeometryFrustum& viewportFrustum );

   virtual void render( const Camera& cam );
   //virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
protected:
   MGLPointSetShaderAccelerated( WO* parentWO, int numSplits );
   virtual void onCreate( ModelDataShared* perInstanceVAModelData, bool autoSplitMeshDuringConstruction );
   virtual void onCreate( const std::vector< Vector >& verts,
                          const std::vector< unsigned int >& indices,
                          GLenum glPrimType, bool autoSplitMeshDuringConstruction, aftrColor4ub color );
   virtual void splitMyMeshes( std::vector< ModelMesh* >& meshes, GLenum primType );
   virtual void splitMyMeshes( ModelDataShared* mds );
   int numSplits;
};

} //namespace Aftr

