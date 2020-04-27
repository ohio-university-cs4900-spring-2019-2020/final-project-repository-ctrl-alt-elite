#pragma once

#include "MeshSplitterFilter.h"
#include <vector>

namespace Aftr
{
   class MeshSplitterFilterGridXYZPoints : public MeshSplitterFilter
   {
   public:
      MeshSplitterFilterGridXYZPoints();
      virtual ~MeshSplitterFilterGridXYZPoints();
      virtual std::vector< std::vector< size_t > > filter( ModelMesh* mesh );
   protected:

   };
};

