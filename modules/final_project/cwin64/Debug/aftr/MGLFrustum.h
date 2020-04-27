#pragma once

#include "MGL.h"
#include "ManagerTexture.h"
#include "Vector.h"
#include "IndexedGeometryLines.h"
#include "IndexedGeometryRectangularPrism.h"

namespace Aftr
{

//class IndexedGeometryLines; //needed to include header so unique_ptr uses fully defined object.
//class IndexedGeometryRectangularPrism;

class MGLFrustum : public MGL
{
public:
   static MGLFrustum* New( WO* parentWO, float nearPlane, float farPlane, float horzFOVDeg, float aspectRatioWidthToHeight );
   virtual ~MGLFrustum(); 
   virtual void render( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   float getNearPlane()                const { return this->nearPlane; }
   float getFarPlane()                 const { return this->farPlane; }
   float getHorzFOVDeg()               const { return this->horzFOVDeg; }
   float getAspectRatioWidthToHeight() const { return this->aspectRatioWidthToHeight; }

protected:
   virtual void onCreate();
   MGLFrustum( WO* parentWO, float nearPlane, float farPlane, float horzFOVDeg, float aspectRatioWidthToHeight );
   
   void createOutlineGeometry( std::vector< Vector >& lines, std::vector< aftrColor4ub >& colors ) const;

   float nearPlane = 1.0f; ///< Distance from "eyeball" to the frustum's near plane
   float farPlane = 10.0f; ///< Distance from "eyeball" to the frustum's far plane
   float horzFOVDeg = 45.0f; ///< Horizontal Field-of-view in degrees
   float aspectRatioWidthToHeight = 4.0f/3.0f; ///< Vertical Field-of-view in degrees
   
   //This model will have a GL_LINE skeleton as well as a set of 2D planes encapsulating its volume
   std::unique_ptr< IndexedGeometryLines > outline = nullptr;
   float lineWidthInPixels = 1.0f; ///< Line width, in pixels of this.outline
   std::unique_ptr< IndexedGeometryRectangularPrism > hull = nullptr;
};

}  //namespace Aftr
