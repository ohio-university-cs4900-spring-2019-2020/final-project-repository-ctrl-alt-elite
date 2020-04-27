#pragma once

#include "WOGUI.h"

namespace Aftr
{

   class WOGUILabel;

   class WOGUICursor : public WOGUI
   {
   public:
      static WOGUICursor* New( WOGUILabel* parent );
      virtual ~WOGUICursor();
      virtual void onUpdateWO();
   protected:
      WOGUICursor( WOGUILabel* parent );
      virtual void onCreate( WOGUILabel* parent );
      unsigned int internalTimer;
      unsigned int threshold;
   };


}

