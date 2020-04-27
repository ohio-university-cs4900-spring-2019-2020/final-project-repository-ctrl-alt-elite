#pragma once

#include "WO.h"
#include <string>

namespace Aftr
{
   class MGLQuadStripSphere;

/**

   \author Chad Mourning

  */

class WOQuadStripSphere : public WO
{
public:	
   static WOQuadStripSphere* New(const std::string& texture, float radius = 1, int r = 4, int col = 4, float portion = 1);
	virtual ~WOQuadStripSphere();
	void spoofTextureIndex(int i);
protected:
   virtual void onCreate(const std::string& texture, float radius, int r, int col, float portion);
   WOQuadStripSphere();					
};

}

