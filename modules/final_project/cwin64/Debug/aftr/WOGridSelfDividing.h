#pragma once

#include "WOGrid.h"


namespace Aftr
{

   /**

   \author Chad Mourning

   */

class WOGridSelfDividing : public WOGrid
{
public:	
   static WOGridSelfDividing* New(float x, float y, float z, float t, int n, int s = 0);	
	virtual ~WOGridSelfDividing();
protected:
   virtual void onCreate(float x, float y, float z, float t, int n, int s);
   WOGridSelfDividing();		
};

}
