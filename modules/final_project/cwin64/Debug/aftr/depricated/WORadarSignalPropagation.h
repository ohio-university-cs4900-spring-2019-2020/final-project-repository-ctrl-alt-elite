#pragma once

#include "WO.h"

namespace Steamie
{

class WOLightWave;
class Camera;

class WORadarSignalPropagation : public WO
{
public:
   static WORadarSignalPropagation* New( Camera** camPtrPtr, float radius, float height );
   virtual ~WORadarSignalPropagation();

   virtual void onUpdateWO();

   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );
   void setRadius( float radius );

protected:
   WORadarSignalPropagation();
   virtual void onCreate( Camera** camPtrPtr, float radius, float height );

   WO* sink;
   WOLightWave* wave;
   unsigned int internalTimer;
};

} //namespace Steamie

