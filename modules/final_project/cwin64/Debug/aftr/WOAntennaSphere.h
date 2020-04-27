#pragma once

#include "WO.h"

namespace Aftr
{

class WOAntennaSphere : public WO
{
public:
   static WOAntennaSphere* New( float radiusMin, float radiusMax, float transparencyAtMin, float transparencyAtMax );
   virtual ~WOAntennaSphere();

   virtual void onUpdateWO();

protected:
   WOAntennaSphere( float radiusMin, float radiusMax, float transparencyAtMin, float transparencyAtMax );
   virtual void onCreate();

   float radiusMin;
   float radiusMax;
   float alphaMin;
   float alphaMax;
   float scaleFactor;
   Vector scale;

   unsigned int counter;

};

} //namespace Aftr

