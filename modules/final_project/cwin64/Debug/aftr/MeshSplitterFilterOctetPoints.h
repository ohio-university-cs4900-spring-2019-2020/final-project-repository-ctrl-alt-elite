#pragma once

#include "MeshSplitterFilterOctet.h"
#include <vector>

//This is a filter meant to be used with the Mesh Splitter.
//It is intended to be used on a mesh of points.
//It subdivides the given mesh into 8 equal octets.

namespace Aftr
{
   class MeshSplitterFilterOctetPoints : public MeshSplitterFilterOctet
   {
   public:
      MeshSplitterFilterOctetPoints();
      virtual ~MeshSplitterFilterOctetPoints();
      virtual std::vector< std::vector< size_t > > filter( ModelMesh* mesh );
   protected:
   };
};

