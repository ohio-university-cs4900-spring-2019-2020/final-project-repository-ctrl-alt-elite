#pragma once

#include "WOGrid.h"
#include <vector>


namespace Aftr
{   /**

   \author Chad Mourning

   */

class WOGridECEF : public WOGrid
{
public:	
   static WOGridECEF* New(std::vector<std::vector<VectorD> > grid, VectorD offset, VectorD scale = VectorD(1,1,1));
	virtual ~WOGridECEF();
   virtual bool overTerrainLLA( Vector lla );
   virtual double getElevationAtLLA( Vector lla );
protected:
   virtual void onCreate(std::vector<std::vector<VectorD> > grid, VectorD offset, VectorD scale);
   WOGridECEF();		
};

}

