#pragma once

#include <vector>
#include <limits>
#include <cstdlib>

namespace Aftr
{
   class ModelMesh;

   class MeshSplitterFilter
   {
   public:
      MeshSplitterFilter(){};
      virtual ~MeshSplitterFilter(){};
      virtual std::vector< std::vector< size_t > > filter( ModelMesh* mesh ) = 0;
   protected:
   };

};

