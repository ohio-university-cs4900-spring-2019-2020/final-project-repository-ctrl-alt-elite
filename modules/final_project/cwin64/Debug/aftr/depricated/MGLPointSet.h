#pragma once

#include "MGL.h"
#include "Particle.h"

namespace Aftr
{

class ParticleDataPointSprite;
class Camera;

class MGLPointSet : public MGL
{
public:
   MGLPointSet( WO* parentWO, Camera** camPtrPtr );
   virtual ~MGLPointSet();
   virtual void render( const Camera& cam );
   virtual void populatePointSet(); ///< Associate the ParticleDataPointSprites w/ the Model's compositeVertexList and compositeIndexList
   virtual void populatePointSet( const std::vector< Vector >& pointSet ); ///< Associate the ParticleDataPointSprites w/ the Model's compositeVertexList and compositeIndexList
   virtual void setAllPointsToSize( float size );
   virtual void setAllPointsToColor( const aftrColor4f& newColor );
   virtual void setColorRed( float red );
   virtual void setColorGreen( float green );
   virtual void setColorBlue( float blue );
   virtual void setColorAlpha( float alpha );
   virtual void setColorRed( unsigned int index, float red );
   virtual void setColorGreen( unsigned int index, float green );
   virtual void setColorBlue( unsigned int index, float blue );
   virtual void setColorAlpha( unsigned int index, float alpha );
   void setScaleFactorForAllPoints( float scaleFactor );
   void updatePointSetPositions( const std::vector< Vector >& positions );

protected:

   std::vector< ParticleDataPointSprite* > points;
   Camera** camPtrPtr;
};

} //namespace Aftr

