#pragma once

#include "MeshSplitterFilterOctet.h"
#include <vector>
#include "Vector.h"

namespace Aftr
{
   class MeshSplitterFilterQuadXYPoints : public MeshSplitterFilterOctet
   {
   public:
      MeshSplitterFilterQuadXYPoints();
      virtual ~MeshSplitterFilterQuadXYPoints();
      virtual std::vector< std::vector< size_t > > filter( ModelMesh* mesh );
   };
};

