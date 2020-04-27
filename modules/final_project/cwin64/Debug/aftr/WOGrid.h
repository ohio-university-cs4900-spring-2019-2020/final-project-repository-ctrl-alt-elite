#pragma once

#include "WO.h"
#include "Vector.h"

namespace Aftr
{

   /**

   \author Chad Mourning

   */

class WOGrid : public WO
{
public:	
   static WOGrid* New(std::vector<std::vector<VectorD> > grid, VectorD scale = VectorD(1,1,1), std::vector< std::vector< aftrColor4ub > > colors = std::vector< std::vector< aftrColor4ub > >());	
	virtual ~WOGrid();
protected:
   virtual void onCreate(std::vector<std::vector<VectorD> > grid, VectorD scale, std::vector< std::vector< aftrColor4ub > > colors);
   WOGrid();		
};

}

