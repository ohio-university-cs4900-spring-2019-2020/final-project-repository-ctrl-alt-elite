#pragma once

#include "Model.h"
//#include "GridTopology.h"
#include <vector>
#include <map>

namespace Aftr
{

   class MeshSplitterFilter;

   struct SplitMeshData
   {
      GLfloat* vertices;
      size_t numVertices;
      GLvoid* indices;
      size_t numIndices;
      GLenum indexMemoryType;
   };

class MeshSplitter
{
public:
   MeshSplitter();
   virtual ~MeshSplitter();
   virtual std::vector< ModelMesh* > splitMesh( ModelMesh* mesh, MeshSplitterFilter* filter, int depth = 2 );
   virtual void splitMesh( ModelDataShared* mesh, int depth = 2 );
   //virtual std::vector< ModelMesh* > splitMesh( ModelMesh* mesh, MeshSplitterFilter* filter, GridTopology& gt);
protected:
   std::vector< ModelMesh* > assignNewData( ModelMesh* mesh, std::vector< std::vector< size_t > > splitIndices,
                                            std::vector< std::map< size_t, size_t > >& indexMaps, 
                                            std::vector< size_t >& skipped );

};

}

