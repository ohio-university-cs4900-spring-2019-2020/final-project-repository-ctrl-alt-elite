#pragma once

#include "IndexedGeometry.h"
#include "Vector.h"
#include <vector>

namespace Aftr
{

class IndexedGeometryRibbon : public IndexedGeometry
{
public:
   static IndexedGeometryRibbon* New( bool useNormals = true, bool useColors = true, bool useTextures = false );
   virtual ~IndexedGeometryRibbon() {}

   virtual void render() override;

   /**
      When a point is appended, it becomes the new "front center" point of the ribbon.
      Internally, geometry is created about that point to make the ribbon have the 
      desired width and roll.
   */
   virtual void appendPoint( const Vector& pt, float rollDeg, const aftrColor4ub& color );

   std::string toString() const;

   const Vector& getRibbonUpDirection() const {return this->up;}
   void setRibbonUpDirection( const Vector& upNormalized ) { this->up = up; }

   aftrColor4ub& getColorAtPt( size_t idx );

   void updateRibbonData();
   int getNumAddedPoints() const { return static_cast<int>(this->verticesVec.size() / 6); } //each added pt becomes a left & right pt
   int getNumPointsInRibbon() const {return static_cast<int>(this->verticesVec.size() / 3);} //double num added points

   struct TrackPoint
   {
      Vector pt = { 0,0,0 };
      float rollDeg = 0;
      aftrColor4ub color = aftrColor4ub();
   };

   void setWidth( float w ) { this->width = w; }
   float getWidth() const { return this->width; }

protected:
   IndexedGeometryRibbon( bool useNormals, bool useColors, bool useTextures );
   virtual void createVertices() override;
   virtual void createIndices() override;
   virtual void createColors() override;
   virtual void createTextureCoords() override;
   virtual void createNormals() override;
   virtual void createVAO() override;

   /// Called by appendPoint. This inserts two new vertices centered about
   /// the in passed control point (via appendPoint). This also inserts the
   /// corresponding normals, colors, tex Coords, etc for each new GL vertex.
   /// Essentially, this appends the new ribbon segment to the front of this
   /// ribbon.
   /// No GPU memory allocation is performed when the GPU already has 
   /// sufficient VAO memory to handle a the vertex entry insertion.
   /// The GPU memory for each vertex array grows by matching the capacity of
   /// the corresponding CPU-side std::vectors of vertex entry data.
   /// This includes verticies, normals, indices, colors, and texture coords.
   /// The in passed bools notify this method if the CPU-side std::vector corresponding
   /// to a specific attribute grew in capacity during the most recent insertion.
   /// This method then uses that info to grow the GPU-side memory accordingly.
   void appendGLVertex( bool resizeVerts, bool resizeIndices, bool resizeColors, bool resizeTexCoords, bool resizeNormals );

   //IndexedGeometry base class already has a few member pointers for things like
   // colors, normals, textureCoords, vertices, indices...  However, in this class,
   // I'd like to replace those base members with std::vector to try to improve
   // testability and debugging. Furthermore, this ribbon will be somewhat dynamic in
   // the amount of points that may get added to it (the ribbon may grow over time)
   // so I will allocate more GPU RAM for points than are currently stored in the ribbon
   // and dynamically grow the GPU RAM by doubling just like a vector.

   std::vector< GLfloat > verticesVec; ///< (x,y,z) per vertex
   std::vector< GLfloat > normalsVec; ///< (x,y,z) per vertex (assumed to be normalized)
   std::vector< GLfloat > textureCoordsVec; ///< (u,v) per vertex
   std::vector< GLubyte > colorsVec; ///< (r,g,b,a) per vertex
   std::vector< GLuint > indicesVec; ///< assume the ribbon can easily surpass 65536 indices

   //std::vector< TrackPoint > controlPts; ///< Each control point added by user
   TrackPoint lastAddedTrackPt; /// if verticesVec.size() == 0 && hasAddedFirstPoint
   bool hasAddedFirstPoint = false; ///< Becomes true after the user adds at least 2 points to form a ribbon
   inline void computeAndInsertVertexEntryIntoGLBuffers( const Vector& newPoint, const aftrColor4ub& color, float rollDeg, Vector& lastTrackPt );

   /// Specifies the expected usage pattern of the data store.
   /// The symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, 
   /// GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, 
   /// GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
   GLenum usageModeForGLVertexAttributes = GL_DYNAMIC_DRAW;

   float width = 1.0f; ///< The initial width of the ribbon; defaults to 1.0
   Vector up = { 0,0,1.0f }; ///< The "up" direction for this ribbon (commonly,
                             /// it points against gravity, for example). Used to compute roll
};

}

