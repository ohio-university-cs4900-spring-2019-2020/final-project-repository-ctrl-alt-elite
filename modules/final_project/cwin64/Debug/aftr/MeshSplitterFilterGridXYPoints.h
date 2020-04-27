#pragma once

#include "MeshSplitterFilter.h"
#include <vector>
#include "Vector.h"

namespace Aftr
{
   class MeshSplitterFilterGridXYPoints : public MeshSplitterFilter
   {
   public:
      MeshSplitterFilterGridXYPoints();
      virtual ~MeshSplitterFilterGridXYPoints();
      virtual std::vector< std::vector< size_t > > filter( ModelMesh* mesh );
      virtual void calculateCenterAndExtents( ModelMesh* mesh );
   protected:
      Vector center;
      Vector extents;
      Vector min;
      Vector max;
   };
};

