#pragma once

#include "WO.h"

namespace Aftr
{
class WOAxesTubes : public WO
{
public:
   static WOAxesTubes* New( Vector lengths, float tubeRadius = 0.1f );
   virtual ~WOAxesTubes();
   //virtual void setLineWidth( float lineWidthInPixels );
   //virtual float getLineWidth();
protected:
   WOAxesTubes();
   virtual void onCreate( Vector lengths, float tubeRadius );
};

}

