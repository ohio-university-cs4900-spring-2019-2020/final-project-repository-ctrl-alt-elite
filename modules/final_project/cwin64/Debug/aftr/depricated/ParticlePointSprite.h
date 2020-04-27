#pragma once

#include "Particle.h"
#include "Vector.h"

namespace Aftr
{
   class Camera;

   class IndexedGeometryQuad;

   class ParticlePointSprite : public Particle
   {
   public:
      ParticlePointSprite( const aftrColor4f& color, const Vector& originalPosition, const Vector& orientation, unsigned int ttl, Camera** cam, float size);
      virtual ~ParticlePointSprite();
      virtual void render( const Camera& cam );
      virtual bool update(unsigned int x);
   protected:
      unsigned int internalTimer;
      unsigned int ttl;
      aftrColor4f myColor;
      Vector originalPosition;
      Vector currentPosition;
      Vector orientation;
      Camera** cam;
 
      IndexedGeometryQuad* quad;
   };

}

