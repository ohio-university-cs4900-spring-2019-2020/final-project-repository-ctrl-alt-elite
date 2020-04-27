#pragma once

#include "MGL.h"

namespace Aftr
{
class WO;
class IndexedGeometryRectangularPrism;
class IndexedGeometrySphereTriStrip;
class IndexedGeometryCylinder;
class IndexedGeometryLines;

   /**

   For a cube, the only governing parameter (0) is the cube's edge length.

   For a rectangular prism there are three governing parameters.  The local x-axis is the RPs length (0).
   The local y-axis is the RPs width (1).  The local z-axis is the RPs depth (2).

   For a sphere, the only governing parameter (0) is the sphere's radius.

   For a cylinder there are two governing parameters.  The radius (0), and the height (2).
   The default orientation of a cylinder is along it's z-axis. (double check this)

   For lines, a std::vector of Aftr::Vectors defines the geometry. There must be an even number
   of Aftr::Vectors in the input geometry. The line segments are drawn in the same order as their
   place in the input std::vector. The input std::vector< Vector >* is NOT OWNED by this instance and
   is NOT MODIFIED by this instance; an internal copy in a graphical format is made for efficient rendering.

   For lines, a std::vector of Aftr::aftrColor4ub defines the color at each vertex. The size of
   colors must match the size of lines; that is (lines->size() == colors->size()) evaluates to true.

   */
   enum class PRIMITIVE_SHAPE_TYPE { psCUBE = 0, psCYLINDER, psSPHERE, psRECTANGULAR_PRISM, psLINES, psNUM_PRIMITIVE_SHAPE_TYPE };

   class MGLPrimitiveShape : public MGL
   {
   public:
	   static MGLPrimitiveShape* New(WO* parentWO, PRIMITIVE_SHAPE_TYPE type, std::vector<float> parameters = std::vector<float>());
	   static MGLPrimitiveShape* New(WO* parentWO, const std::vector< Vector >& lines, const std::vector< aftrColor4ub >& colors);
	   void onCreate( PRIMITIVE_SHAPE_TYPE type, std::vector<float> parameters = std::vector<float>());
	   void onCreate( const std::vector< Vector >& lines, const std::vector< aftrColor4ub >& colors);
      ///This constructor creates an instance of psRECTANGULAR_PRISM, psSPHERE, or psCYCLINDER.
      
      virtual ~MGLPrimitiveShape();
      virtual void render( const Camera& cam );
	  virtual void renderGL32(const Camera& cam);
	  virtual void renderGL21(const Camera& cam);
	  virtual void renderSelection(const Camera& cam, GLubyte red, GLubyte green, GLubyte blue);
	  virtual void renderSelection32(const Camera& cam, GLubyte red, GLubyte green, GLubyte blue);
	  virtual void renderSelection21(const Camera& cam, GLubyte red, GLubyte green, GLubyte blue);
	  /**
      For a cube, sets the edge length and returns true.

      Otherwise returns false.
      */
      bool setEdge(float x);
      float getEdge();

      /**
      For a cube, sets the edge length and returns true.
      For a rectangular prism sets the length and returns true.

      Otherwise returns false.
      */
      bool setLength(float x);
      float getLength();

      /**

      etc

      */
      bool setWidth(float x);
      float getWidth();
      bool setDepth(float x);
      float getDepth();
      bool setRadius(float x);
      float getRadius();
      bool setHeight(float x);
      float getHeight();
      void setColor4f( float r, float g, float b, float a ) { this->r = r, this->g = g, this->b = b; this->a = a; }
      void setRed(float x) { r = x; }
      float getRed()const { return r; }
      void setBlue(float x) { b = x; }
      float getBlue()const { return b; }
      void setGreen(float x) { g = x; }
      float getGreen()const { return g; }
      void setAlpha(float x) { a = x; }
      float getAlpha()const { return a; }
      void setColor( const aftrColor4ub& c );

      IndexedGeometryRectangularPrism* getPrism() { return this->prism; }
      IndexedGeometrySphereTriStrip* getSphere() { return this->sphere; }
      IndexedGeometryCylinder* getCylinder() { return this->cylinder; }
      IndexedGeometryLines* getLines() { return this->lines; }

   protected:
	   ///Use other constructor to create a psLINES instance.
	   MGLPrimitiveShape(WO* parentWO);
	   ///This constructor creates an instance of psLINES.
	   MGLPrimitiveShape(WO* parentWO, std::vector< Vector >* lines, std::vector< aftrColor4ub >* colors);
      PRIMITIVE_SHAPE_TYPE type;
      float r, g, b, a;
      std::vector<float> parameters;
      //void drawCube();
      void drawCylinder( const Camera& cam, const Mat4& modelMat );
      void drawCylinderRenderSelection( GLubyte r, GLubyte g, GLubyte b);

      void drawSphere( const Camera& cam, const Mat4& modelMat );
      void drawSphereRenderSelection( GLubyte r, GLubyte g, GLubyte b);

      void drawRectangularPrism( const Camera& cam, const Mat4& modelMat );
      void drawRectangularPrismRenderSelection( GLubyte r, GLubyte g, GLubyte b);

      void drawLines( const Camera& cam );
      void drawLinesRenderSelection( GLubyte r, GLubyte g, GLubyte b);
      IndexedGeometryRectangularPrism* prism = nullptr;
      IndexedGeometrySphereTriStrip* sphere = nullptr;
      IndexedGeometryCylinder* cylinder = nullptr;
      IndexedGeometryLines* lines = nullptr;
   };
}

