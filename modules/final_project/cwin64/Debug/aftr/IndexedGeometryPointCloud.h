#pragma once

#include "IndexedGeometry.h"
#include "Vector.h"
#include <vector>

namespace Aftr
{

class IndexedGeometryPointCloud : public IndexedGeometry
{
public:
   static IndexedGeometryPointCloud* New( const std::vector<Vector>& pts,  bool useColors = false,
                                          bool useNormals = false, bool useTextures = false );
   virtual ~IndexedGeometryPointCloud() {}

   virtual void render() override;

   /**
      When a point is appended, it becomes the new "front center" point of the ribbon.
      Internally, geometry is created about that point to make the ribbon have the 
      desired width and roll.
   */
   void setPoints( const std::vector<Vector>& pts );
   void setColors( const std::vector<aftrColor4ub>& colors );
   void setColor( const aftrColor4ub& color );
   //void setNormals( const std::vector<Vector>& normals );  //SLN < Not implemented yet!
   //void setTexCoords( const std::vector<Vector>& normals );//SLN < Not implemented yet!
   //template< typename T >
   //void setVertexAttrib( const std::vector<T>& attribs );//SLN < Not implemented yet!

   std::string toString() const;

   aftrColor4ub& getColorAtPt( size_t idx );

   int getNumPointsInCloud() const {return static_cast<int>(this->verticesVec.size() / 3);} //double num added points

   virtual const std::vector< Vector >& getCompositeVertexList() const;
   virtual const std::vector< unsigned int >& getCompositeIndexList() const;

protected:
   IndexedGeometryPointCloud( bool useNormals, bool useColors, bool useTextures );
   virtual void createVertices() override;
   virtual void createIndices() override;
   virtual void createColors() override;
   virtual void createTextureCoords() override;
   virtual void createNormals() override;
   virtual void createVAO() override {};
   void createVAO(const std::vector<Vector>& pts);

   /// Called by appendPoint. This overwrites the corresponding Vertex attribute
   /// (Vertex, Index, Color, etc).
   /// No GPU memory allocation is performed when the GPU already has 
   /// sufficient VAO memory to handle a the vertex entry insertion.
   /// The GPU memory for each vertex array grows by matching the size of
   /// the corresponding CPU-side std::vectors of vertex entry data.
   /// The in passed bools notify this method if the CPU-side std::vector corresponding
   /// to a specific attribute grew in capacity during the most recent insertion.
   /// This method then uses that info to grow the GPU-side memory accordingly.
   void updateGPUBufferVerts( bool growVerts, const std::vector<float>& v ) const noexcept;
   void updateGPUBufferIndices( bool growIndices, const std::vector<unsigned int>& idx ) const noexcept;
   void updateGPUBufferColors( bool growColors, const std::vector<uint8_t>& c ) const noexcept;
   //void updateGPUBufferNormals( bool growNormals, const std::vector<float>& v ) const noexcept;
   //void updateGPUBufferTextCoords( bool growTexCoords, const std::vector<float>& uv ) const noexcept;

   //IndexedGeometry base class already has a few member pointers for things like
   // colors, normals, textureCoords, vertices, indices...  However, in this class,
   // I'd like to replace those base members with std::vector to try to improve
   // testability and debugging. Furthermore, this point cloud will be somewhat dynamic in
   // the amount of points that may get added to it (the ribbon may grow over time)
   // so I will allocate more GPU RAM for points than are currently stored in the ribbon
   // and dynamically grow the GPU RAM by doubling just like a vector.

   std::vector< GLfloat > verticesVec; ///< (x,y,z) per vertex
   std::vector< GLubyte > colorsVec; ///< (r,g,b,a) per vertex
   std::vector< GLuint > indicesVec; ///< assume the ribbon can easily surpass 65536 indices
   //std::vector< GLfloat > normalsVec; ///< (x,y,z) per vertex (assumed to be normalized)
   //std::vector< GLfloat > textureCoordsVec; ///< (u,v) per vertex

   /// Specifies the expected usage pattern of the data store.
   /// The symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, 
   /// GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, 
   /// GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
   GLenum usageModeForGLVertexAttributes = GL_DYNAMIC_DRAW;
};

}

