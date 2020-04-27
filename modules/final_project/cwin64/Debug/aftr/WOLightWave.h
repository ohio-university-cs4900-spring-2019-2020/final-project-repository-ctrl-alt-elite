#pragma once

#include "WO.h"

namespace Aftr
{
class GLView;

class WOLightWave : public WO
{
public:
   static WOLightWave* New( WO* dataSource, WO* dataSink, Camera** cam, float width,
                            float xTexRepeats = 1.0f, float yTexRepeats = 1.0f,
                            float xTexRepeatsPerSecond = 0, float yTexRepeatsPerSecond = 0 );

   static WOLightWave* New( const Vector& source, const Vector& sink, Camera** cam, float width,
                            float xTexRepeats = 1.0f, float yTexRepeats = 1.0f,
                            float xTexRepeatsPerSecond = 0, float yTexRepeatsPerSecond = 0 );

   virtual ~WOLightWave();
   virtual void onUpdateWO();
   void setXTexRepeatsPerSecond( float xTexRepeatsPerSecond ) { this->xTexRepeatsPerSecond = xTexRepeatsPerSecond; }
   void setYTexRepeatsPerSecond( float yTexRepeatsPerSecond ) { this->yTexRepeatsPerSecond = yTexRepeatsPerSecond; }
   float getXTexRepeatsPerSecond() { return this->xTexRepeatsPerSecond; }
   float getYTexRepeatsPerSecond() { return this->yTexRepeatsPerSecond; }
   void setLightWaveWidth( float width );
   float getLightWaveWidth();

   void setSourceOfLightWave( const Vector& src );
   void setSinkOfLightWave( const Vector& sink );

   void setCamera( Camera** camPtr );
   Camera** getCamera();

protected:
   virtual void onCreate( WO* dataSource, WO* dataSink, Camera** cam, float width,
                          float xTexRepeats, float yTexRepeats,
                          float xTexRepeatsPerSecond, float yTexRepeatsPerSecond );
   
   virtual void onCreate( const Vector& source, const Vector& sink, Camera** cam, float width,
                          float xTexRepeats, float yTexRepeats,
                          float xTexRepeatsPerSecond, float yTexRepeatsPerSecond );

   WOLightWave();
   WO* source;
   WO* sink;
   float xTexRepeatsPerSecond;
   float yTexRepeatsPerSecond;
   unsigned int internalTimer;
   float updateThresholdInMS;

};

}

