#pragma once

#include "MeshSplitterFilter.h"
#include "Vector.h"
#include <vector>

//This is a filter meant to be used with the Mesh Splitter.
//It is intended to be used on a mesh of triangles.
//It subdivides the given mesh into 8 equal octets.

namespace Aftr
{
   class MeshSplitterFilterOctet : public MeshSplitterFilter
   {
   public:
      MeshSplitterFilterOctet();
      virtual ~MeshSplitterFilterOctet();
      virtual std::vector< std::vector< size_t > > filter( ModelMesh* mesh );
      void calculateCenter( ModelMesh* mesh );
   protected:
      Vector center;
   };
};

