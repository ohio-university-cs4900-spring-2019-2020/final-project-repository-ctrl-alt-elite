#pragma once

#include "Particle.h"
#include "Vector.h"

namespace Aftr
{
   class Camera;
   class MGLPointSet;
   class IndexedGeometryQuad;

   class ParticleDataPointSprite : public Particle
   {
   public:
      ParticleDataPointSprite( const Vector& point, MGLPointSet* parentModel, Camera** camPtrPtr, float radius, const aftrColor4f& color );
      virtual ~ParticleDataPointSprite();
      virtual void render( const Camera& cam );
      virtual bool update( unsigned int u );
      void setSize( float radius );
      void setColor( const aftrColor4f& newColor );
      void setColorRed( float red );
      void setColorGreen( float green );
      void setColorBlue( float blue );
      void setColorAlpha( float alpha );
      void setPosition( const Vector& position ) { origPos = position; }
      const Vector& getDataPoint() const;
      Vector& getDataPoint();

   protected:
      Camera** cam = nullptr;
      MGLPointSet* parentModel = nullptr; ///< Stores parent display matrix used for transformation in particle render
      Vector origPos = nullptr;
      aftrColor4f myColor;
      float diameter;

      IndexedGeometryQuad* quad = nullptr;
   };


} //namespace Aftr

