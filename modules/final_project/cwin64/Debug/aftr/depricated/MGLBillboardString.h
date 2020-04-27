#pragma once

#include "MGLString.h"
#include "IFaceBillboard.h"

namespace Aftr
{

   class Font; 

   class MGLBillboardString : public MGLString, public IFaceBillboard
   {
   public:
      static MGLBillboardString* New(WO* parent, std::string str, std::string fontPath, size_t fontSize );
      virtual void render( const Camera& cam );
   protected:
      MGLBillboardString(WO* parent, std::string str, std::string fontPath, size_t fontSize);
   };
}

