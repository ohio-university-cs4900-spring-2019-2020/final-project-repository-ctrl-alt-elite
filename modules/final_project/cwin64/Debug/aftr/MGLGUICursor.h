#pragma once

#include "MGLGUI.h"

namespace Aftr
{

   class IndexedGeometryQuad;
   class WOGUILabel;

   class MGLGUICursor : public MGLGUI
   {
   public:
      static MGLGUICursor* New( WO* parent, WOGUILabel* parentString );
      virtual ~MGLGUICursor();
      virtual void render( const Camera& cam );
   protected:
      MGLGUICursor( WO* parent, WOGUILabel* parentString );
      virtual void onCreate();
      WOGUILabel* parentString;
   };

}

