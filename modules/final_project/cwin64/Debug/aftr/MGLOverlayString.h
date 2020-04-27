#pragma once

#include "MGLString.h"

namespace Aftr
{

   class Font; 

   class MGLOverlayString : public MGLString
   {
   public:
      static MGLOverlayString* New(WO* parent, std::string str, std::string fontPath, size_t fontSize);
      virtual void render( const Camera& cam );
   protected:
      MGLOverlayString(WO* parent, std::string str, std::string fontPath, size_t fontSize);
   };
}

