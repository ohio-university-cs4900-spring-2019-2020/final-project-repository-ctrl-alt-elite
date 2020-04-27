#pragma once

#include "MGL.h"
#include "IndexedGeometryQuad.h"

namespace Aftr
{

class IndexedGeometryQuad;

class MGLQuad : public MGL
{
public:
   //MGLQuad* New( WO* parentWO, std::string texture, float height, float width );
   //MGLQuad* New( WO* parentWO, const AftrGeometryPlane& plane, float lengthX, float lengthY );
   //MGLQuad* New( QuadOrientation orientation, float xDim, float yDim, const Vector& color, bool useTexCoords, bool useNormals, bool useColors );
   MGLQuad( WO* parentWO, const std::string& texture, float height, float width );
   MGLQuad( WO* parentWO, QuadOrientation orientation, Texture* texture, float height, float width );
   MGLQuad( WO* parentWO, const AftrGeometryPlane& plane, float lengthX, float lengthY );
   MGLQuad( WO* parentWO, QuadOrientation orientation, float xDim, float yDim, const Vector& color = Vector( 1, 1, 1 ), bool useTexCoords = false, bool useNormals = false, bool useColors = false );
   MGLQuad( WO* parentWO, QuadOrientation orientation, const std::string& tex, float xDim, float yDim, const Vector& color = Vector( 1, 1, 1 ), bool useTexCoords = true, bool useNormals = true, bool useColors = false );
   virtual ~MGLQuad();
   virtual void render( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   void setToPlane( const AftrGeometryPlane& plane );
   IndexedGeometryQuad* getQuad() { return quad; }
   void isUsingShearMatrix( bool useShearMatrix );
   bool isUsingShearMatrix();
   void isUsingBlending( bool useBlending ) { this->useBlending = useBlending; }
   bool isUsingBlending() { return useBlending; }
   void isUsingDepthTesting( bool useDepthTesting ) { this->useDepthTesting = useDepthTesting; }
   bool isUsingDepthTesting() { return this->useDepthTesting; }
   void updateShearMatrix( float roll, float aspectRatioWidthToHeight );
protected:
   bool useBlending;
   bool useDepthTesting;
   IndexedGeometryQuad* quad;
   float shearMat[16];
   bool IsUsingShearMatrix;
};

} //namespace Aftr

