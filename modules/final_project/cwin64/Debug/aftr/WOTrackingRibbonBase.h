#pragma once

#include "WO.h"

namespace Aftr
{
class TrackInfo;

class WOTrackingRibbonBase: public WO
{
public:
   static WOTrackingRibbonBase* New( WO* trackee = nullptr, Vector up = Vector(0,0,1) );
   virtual ~WOTrackingRibbonBase(){}

      /*
   User Functions
   */
   ///adds a track point to the ribbon
   void addTrackPoint(const TrackInfo& p);
   void addTrackPoint( const TrackInfo& p, aftrColor4ub color );
   std::vector< TrackInfo >& getTrackPoints();
   ///start or unpause
   void start();
   ///stop or pause
   void stop();
   ///toggle puase
   void toggle();
   ///reset
   virtual void reset();

   /// Destroys MGLTrackingRibbon and creates a new empty one
   void clear();

   ///Draws a plumbline every x data points, if 0, none are drawn
   void setPlumblineRatio(unsigned int x);
   ///Show how much of the path [0..1]
   void setRibbonLength(float x);
   ///Color of the Ribbon in RGB [0..1]
   void setRibbonColor(const Vector& x);

   float getCompletionPercentage();
   void setCompletionPercentage( float percentage );
   Vector getGravityDirection() { return g; }
protected:
   WOTrackingRibbonBase( WO* trackee, const Vector& g );
   virtual void onCreate();
   Vector g;
   WO* trackee;
   bool go;

   void adjustTrackee(float percentage);
};

}

