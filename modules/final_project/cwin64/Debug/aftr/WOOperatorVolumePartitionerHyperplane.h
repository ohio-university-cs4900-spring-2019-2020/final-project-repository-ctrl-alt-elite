#pragma once

#include "WO.h"

namespace Aftr
{

class WOQuad;

class WOOperatorVolumePartitionerHyperplane : public WO
{
public:
   static WOOperatorVolumePartitionerHyperplane* New( const std::vector< WO* >& targetPointSets,
                                                      const std::vector< WOQuad* >& dividingPlanes );

   virtual ~WOOperatorVolumePartitionerHyperplane();

   virtual void render( const Camera& cam );
   virtual void onUpdateWO();
   void updateVolume();
   void addHyperplane( WOQuad* hyperplane );
   bool removeHyperplane( WOQuad* hyperplane );
   void resetHyperplaneOrientation();
   void resetHyperplaneColors( aftrColor4ub color = aftrColor4ub( 0, 255, 255, 255 ) );
   void setPointSetColors( aftrColor4ub color = aftrColor4ub( 0, 255, 255, 255 ) );
   void setPointSize( float dimX, float dimY );
   void scalePointSize( float scaleX, float scaleY );
   void getPointSize( float& xSize, float& ySize );
   void setTogglePlaneVisibility();
   size_t getHyperplaneCount() { return this->planes.size(); }
   WOQuad* getHyperPlaneAtIndex( size_t i ) { return this->planes.at(i); }
   size_t getTargetCount() { return this->targets.size(); }
   WO* getTargetAtIndex( size_t i ) { return this->targets.at(i); }

protected:
   WOOperatorVolumePartitionerHyperplane();

   virtual void onCreate( const std::vector< WO* >& targetPointSets,
                          const std::vector< WOQuad* >& dividingPlanes );

   std::vector< WOQuad* > planes; ///< Planes intersect WOs in the target vector
   std::vector< WO* > targets; ///< Targets are intersected by the planes in the planes vector

   bool performUpdate;
   
};

} //namespace Aftr

