#pragma once

#include "MGLGrid.h"

namespace Aftr
{   class MGLGridECEF : public MGLGrid
   {
   public:
      MGLGridECEF( WO* parentWO );
      MGLGridECEF( WO* parentWO, std::vector<std::vector<VectorD> > grid, VectorD offset, VectorD scale );
      MGLGridECEF( WO* parentWO, std::vector< std::vector< VectorD > > grid, VectorD scale );
      virtual ~MGLGridECEF();
      virtual void defineVertices();
      virtual void defineTextureCoords();
      virtual bool overTerrainLLA( Vector lla );
      virtual double getElevationAtLLA( Vector lla );
   protected:
      VectorD offset;
      float exageration;
   };

}

