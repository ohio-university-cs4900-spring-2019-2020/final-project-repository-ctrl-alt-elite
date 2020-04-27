#pragma once

#include "WOGrid.h"
#include <vector>


namespace Aftr
{
   /**
      \author Chad Mourning
   */

class WOGridLinesRegular2D : public WOGrid
{
public:	
   static WOGridLinesRegular2D* New(float xDim, float xGranularity, float yDim, float yGranularity,
                                    const aftrColor4ub& color = aftrColor4ub(255,255,255,255 ) );
	virtual ~WOGridLinesRegular2D();
   virtual void setGlLineWidth( float GlLineWidth );
   virtual float getGlLineWidth();
protected:
   virtual void onCreate( float xDim, float xGranularity, float yDim, float yGranularity,
                          const aftrColor4ub& color );
   WOGridLinesRegular2D();
};

}

