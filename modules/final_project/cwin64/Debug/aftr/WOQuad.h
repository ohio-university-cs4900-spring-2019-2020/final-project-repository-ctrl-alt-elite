#pragma once

#include "WO.h"
#include "IndexedGeometryQuad.h"

namespace Aftr
{

class AftrGeometryPlane;

/**
   \author Chad Mourning / Scott Nykl
*/

class WOQuad : public WO
{
public:
   static WOQuad* New( const std::string& texture, float height, float width );
   static WOQuad* New( QuadOrientation orientation, const std::string& texture, float xDim, float yDim );
   static WOQuad* New( QuadOrientation orientation, Texture* texture, float xDim, float yDim );
   static WOQuad* New( const AftrGeometryPlane& plane, float lengthX, float lengthY );
   static WOQuad* New( QuadOrientation orientation, float xDim, float yDim, const Vector& color, bool useTexCoords, bool useNormals, bool useColorsPerVertex );
   virtual ~WOQuad();

   /**
      Sets the planes values (pos/orientation) to the in passed plane.
   */
   void setToPlane( const AftrGeometryPlane& plane );
   /**
      Resets the planes values (pos/orientation) to the last plane that was set. This is
      either the most recent plane passed into setToPlane, or the original plane passed
      into the constructor. If neither of these methods were called, the plane will
      default to a global normal of <0,0,0> w/ a displacement of 0 (at the origin in
      XY plane).
   */
   void resetToPlane();
   void setScaleOfBothSizeAndTexture( const Vector& scale );
   void incrementScaleOfBothSizeAndTexture( const Vector& increment );

   void setNewSize( float height, float width );
   void setSizeScale( float scale );

protected:
   WOQuad();
   virtual void onCreate( const std::string& texture, float height, float width );
   virtual void onCreate( QuadOrientation orientation, const std::string& texture, float xDim, float yDim );
   virtual void onCreate( QuadOrientation orientation, Texture* mglqtexture, float xDim, float yDim );
   virtual void onCreate( const AftrGeometryPlane& plane, float lengthX, float lengthY );
   virtual void onCreate( QuadOrientation orientation, float xDim, float yDim, const Vector& color, bool useTexCoords, bool useNormals, bool useColorsPerVertex );
   Vector initialPlaneNormal;
   float initialPlaneDisplacement;

};

}

