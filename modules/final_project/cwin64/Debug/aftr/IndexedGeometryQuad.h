#pragma once

#include "IndexedGeometry.h"
#include "AftrGlobals.h"
#include "Vector.h"

namespace Aftr
{

//orientations for quads
enum class QuadOrientation : unsigned char { qoXY = 0, qoXZ, qoYZ, qoMAX_TYPES };
std::ostream& operator<<( std::ostream& out, const QuadOrientation& mrt );

class IndexedGeometryQuad : public IndexedGeometry
{
public:
   static IndexedGeometryQuad* New( QuadOrientation orientation, float xDim, float yDim, const Vector& color, bool useTextureCoords = false, bool useNormals = false, bool useColors = false );
   virtual ~IndexedGeometryQuad() {};
   void resize( float newXDim, float newYDim );
   ///scale.x - first dimension with respect to orientation (xDim)
   ///scale.y - second dimension with respect to orientation (yDim)
   ///scale.z - Not used (because it's a 2D object)
   void setScaleOfBothSizeAndTexture( Vector scale );
	void setScaleOfSize( Vector sizeScale );
	void setScaleOfTexture( Vector textureScale );
   Vector getSizeScale() { return sizeScale; }
	Vector getTextureScale() { return textureScale; }
   Vector getXYDim() { return Vector( xDim, yDim, 0 ); }
	void setXYDim( Vector v );
	QuadOrientation getOrientation() { return orientation; }
protected:
   IndexedGeometryQuad( QuadOrientation orientation, float xDim, float yDim, const Vector& color, bool useTextureCoords, bool useNormals, bool useColors );
   virtual void createVertices();
   virtual void createIndices();
   virtual void createTextureCoords();
   virtual void createNormals();
   virtual void createColors();
   QuadOrientation orientation;
   float xDim;
   float yDim;
   Vector color;

   Vector sizeScale;
	Vector textureScale;

   //used by both createVertices() and resize()
   virtual void assignVertices();

   void assignTexture();
};

}

