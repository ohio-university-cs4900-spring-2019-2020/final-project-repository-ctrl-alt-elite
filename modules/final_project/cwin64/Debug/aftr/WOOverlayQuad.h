#pragma once

#include "WO.h"

namespace Aftr
{

   /**

   \author Chad Mourning

   */

class WOOverlayQuad : public WO
{
public:
   static WOOverlayQuad* New( const std::string& texture, float height, float width );
   static WOOverlayQuad* New( float height, float width );
   virtual ~WOOverlayQuad();
protected:
   virtual void onCreate( const std::string& texture, float height, float width );
   virtual void onCreate( float height, float width );
   WOOverlayQuad();

};

}

