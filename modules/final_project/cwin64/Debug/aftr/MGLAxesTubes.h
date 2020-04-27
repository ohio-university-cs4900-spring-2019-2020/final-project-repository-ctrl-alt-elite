#pragma once

#include "MGL.h"

namespace Aftr
{
class IndexedGeometryAxes;
class IndexedGeometryCylinder;
class GLSLShaderDefaultIndexedGeometryLinesGL32;

class MGLAxesTubes : public MGL
{
public:
   MGLAxesTubes( WO* parentWO, Vector lengths, float tubeRadius );
   virtual ~MGLAxesTubes();
   virtual void render( const Camera& cam );
   virtual void renderGL32( const Camera& cam );
   virtual void renderCompatibility( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   virtual void renderSelectionCompatibility( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   virtual void renderSelectionGL32( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   //virtual void setLineWidth( float lineWidthInPixels ) { this->lineWidthInPixels = lineWidthInPixels; }
   //virtual float getLineWidth() { return this->lineWidthInPixels; }

protected:
   Vector lengths;
   IndexedGeometryAxes* axes = nullptr;
   float tubeRadius = 0.1f;
   static const int NUM_AXIS = 3;
   std::array< std::unique_ptr<IndexedGeometryCylinder>, NUM_AXIS > axisTubes;//x,y,z
   std::array< std::unique_ptr<IndexedGeometryCylinder>, NUM_AXIS > axisCaps; //x,y,z
   std::array< aftrColor4f, NUM_AXIS > colors{ aftrColor4f{1.0f,    0,    0, 1.0f },
                                               aftrColor4f{0.0f, 1.0f,    0, 1.0f},
                                               aftrColor4f{0.0f,    0, 1.0f, 1.0f} };

   //The cylinder effectively has the coordinate system of a cup sitting flat on a table.
   //That is, the +z axis runs parallel to the hole in the middle, +x is forward, and +y is
   //left. The origin is in the center of the cup...
   std::array< Mat4, NUM_AXIS > axisTransform{
                                       Mat4{ Vector{0,0,-1},Vector{0,1,0},Vector{1,0,0} },
                                       Mat4{ Vector{1,0,0},Vector{0,0,-1},Vector{0,1,0} },
                                       Mat4{ Vector{1,0,0},Vector{0,1,0},Vector{0,0,1} } };

   std::array< Vector, NUM_AXIS > axisOffset{ Vector{1,0,0},
                                              Vector{0,1,0},
                                              Vector{0,0,1} };
};
}

