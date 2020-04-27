#pragma once

#include "WO.h"

namespace Aftr
{

class Camera;

class WOPointSet : public WO
{
public:
   static WOPointSet* New( Camera** camPtrPtr );
   static WOPointSet* New( const std::vector< Vector >& pointSet, Camera** camPtrPtr );
   virtual ~WOPointSet();
   virtual void setAllPointsToColor( float r, float g, float b, float a );
   virtual void setAllPointsToSize( float radius );
   virtual void setColorRed( float red );
   virtual void setColorGreen( float green );
   virtual void setColorBlue( float blue );
   virtual void setColorAlpha( float alpha );
   virtual void setColorRed( unsigned int index, float red );
   virtual void setColorGreen( unsigned int index, float green );
   virtual void setColorBlue( unsigned int index, float blue );
   virtual void setColorAlpha( unsigned int index, float alpha );
   void setScaleFactorForAllPoints( float scaleFactor );

   //assumes that the new vector contains an equal number of points as the original point set
   //updates the positions of the internal point sprite to match the new locations
   //this is more efficient than repopulating the point set by destroying the entire existing
   //point set and creating a new one
   void updatePointPositions( const std::vector< Vector >& positions );


protected:
   WOPointSet( Camera** camPtrPtr );
   virtual void onCreate();
   virtual void onCreate( const std::vector< Vector >& pointSet );
   Camera** camPtrPtr; ///< Used by the MGLPointSet to render the billboard sprites

};

} //namespace Aftr

