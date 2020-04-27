#pragma once

#include "WO.h"

namespace Aftr
{
class GLView;

class WOBillboardConstrainedMajorAxis : public WO
{
public:
   static WOBillboardConstrainedMajorAxis* New( const std::string& texturePath, WO* dataSource, WO* dataSink, Camera** cam, float width,
                            float xTexRepeats = 1.0f, float yTexRepeats = 1.0f,
                            float xTexRepeatsPerSecond = 0, float yTexRepeatsPerSecond = 0 );
   virtual ~WOBillboardConstrainedMajorAxis();
   virtual void onUpdateWO();
   void setXTexRepeatsPerSecond( float xTexRepeatsPerSecond ) { this->xTexRepeatsPerSecond = xTexRepeatsPerSecond; }
   void setYTexRepeatsPerSecond( float yTexRepeatsPerSecond ) { this->yTexRepeatsPerSecond = yTexRepeatsPerSecond; }
   float getXTexRepeatsPerSecond() { return this->xTexRepeatsPerSecond; }
   float getYTexRepeatsPerSecond() { return this->yTexRepeatsPerSecond; }
   void setLightWaveWidth( float width );
   float getLightWaveWidth();

protected:
   virtual void onCreate( const std::string& texturePath, WO* dataSource, WO* dataSink, Camera** cam, float width,
                          float xTexRepeats, float yTexRepeats,
                          float xTexRepeatsPerSecond, float yTexRepeatsPerSecond );
   WOBillboardConstrainedMajorAxis();
   WO* source;
   WO* sink;
   float xTexRepeatsPerSecond;
   float yTexRepeatsPerSecond;
   unsigned int internalTimer;
   float updateThresholdInMS;

};

}

