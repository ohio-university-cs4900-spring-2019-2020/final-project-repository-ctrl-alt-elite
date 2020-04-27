#pragma once

#include "MGL.h"

namespace Aftr
{
class IndexedGeometryPointCloud;
class Camera;

class MGLPointCloud : public MGL
{
public:
   static MGLPointCloud* New( WO* parent, Camera** cam, bool useColors, bool useNormals, bool useTexCoords );
   virtual ~MGLPointCloud();
   virtual void render( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   virtual void setIndexedGeometry( IndexedGeometryPointCloud* geom, bool deleteExistingGeomIfNotNull = true );
   virtual IndexedGeometryPointCloud* getIndexedGeometryPointCloud() { return this->geom; }

   /// Returns a pointer to a list containing all verticies within this model.
   /// This list is indexed by the corresponding CompositeIndexList.
   virtual const std::vector< Vector >& getCompositeVertexList() const override;

   /// Returns a pointer to a list containing all indicies into the corresponding
   /// CompositeVertexList.
   virtual const std::vector< unsigned int >& getCompositeIndexList() const override;

   virtual void setPoints( const std::vector<Vector>& pts );
   virtual void setColors( const std::vector<aftrColor4ub>& colors );

protected:
   MGLPointCloud( WO* parent );
   virtual void onCreate( Camera** cam, bool useColors, bool useNormals, bool useTexCoords );

   IndexedGeometryPointCloud* geom = nullptr;
};

} //namespace Aftr

