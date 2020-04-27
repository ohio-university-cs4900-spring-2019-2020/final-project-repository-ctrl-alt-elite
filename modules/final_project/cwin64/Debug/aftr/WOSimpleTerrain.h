#pragma once

#include "WO.h"
#include <string>

namespace Aftr
{

   /**

   \author Chad Mourning

  */

class WOSimpleTerrain : public WO
{
public:
   static WOSimpleTerrain* New(const std::string& texture, float x = 1000, float y = 1000, float repeat = 1);
   virtual ~WOSimpleTerrain();
protected:
   WOSimpleTerrain();
   virtual void onCreate(const std::string& texture, float x, float y, float repeat);
private:

};

}

