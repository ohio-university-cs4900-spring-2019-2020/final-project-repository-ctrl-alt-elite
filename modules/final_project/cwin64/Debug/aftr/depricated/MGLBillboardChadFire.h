#pragma once


#include "MGLBillboard.h"
#include <vector>
#include <string>

namespace Aftr
{

   class IndexedGeometryQuad;

   class MGLBillboardChadFire : public MGLBillboard
   {

   public:

      MGLBillboardChadFire( WO* parentWO, std::vector<std::string> textures,
                            Camera** cam, int slices, float height, float width,
                            int startFrame = 0 );
      virtual ~MGLBillboardChadFire();
      virtual void render( const Camera& cam );
      int currentIndex;
   protected:
      bool swap;
      bool seam;
   };

} //namespace Aftr

