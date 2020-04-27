#pragma once

#include "MeshSplitterFilter.h"
#include <vector>
#include "Vector.h"

namespace Aftr
{
   class GridTopology;

   class MeshSplitterFilterGridedUserSpecifiedNonRecursive : public MeshSplitterFilter
   {
   public:
      MeshSplitterFilterGridedUserSpecifiedNonRecursive( int binsx, int binsy );
      virtual ~MeshSplitterFilterGridedUserSpecifiedNonRecursive();
      virtual std::vector< std::vector< size_t > > filter( ModelMesh* mesh, GridTopology& gt );
      virtual std::vector< std::vector< size_t > > filter( ModelMesh* mesh );
      //virtual void calculateCenterAndExtents( ModelMesh* mesh );
   protected:
      void calculateExtents( ModelMesh* mesh );
      //Vector center;
      Vector extents;
      Vector min;
      Vector max;

      int binsx;
      int binsy;
   };
};

