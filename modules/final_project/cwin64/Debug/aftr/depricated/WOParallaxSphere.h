#pragma once

#include "WO.h"
#include <string>

namespace Aftr
{
   class GLView;

   /**

   \author Chad Mourning

  */

class WOParallaxSphere : public WO
{
public:	
   static WOParallaxSphere* New(GLView* view, const std::string& texture, float radius = 100, float v = 0);
	virtual ~WOParallaxSphere();	
protected:
   virtual void onCreate(GLView* view, const std::string& texture, float radius, float v);
   WOParallaxSphere();		
};

}

