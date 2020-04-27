#pragma once

#include "WO.h"

namespace Aftr
{
class WOAxes : public WO
{
public:
   static WOAxes* New( Vector lengths, float lineWidthInPixels = 1.0f );
   virtual ~WOAxes();
   virtual void setLineWidth( float lineWidthInPixels );
   virtual float getLineWidth();
protected:
   WOAxes();
   virtual void onCreate( Vector lengths, float lineWidthInPixels );
};

}

