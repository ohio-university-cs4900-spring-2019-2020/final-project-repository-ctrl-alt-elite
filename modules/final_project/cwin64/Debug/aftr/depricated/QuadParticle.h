#pragma once

#include "Particle.h"
#include "Vector.h"

namespace Aftr
{

   class IndexedGeometryQuad;

   class QuadParticle : public Particle
   {
   public:
      QuadParticle(const Vector& originalPosition, const Vector& orientation, unsigned int ttl, float size);
      virtual void render( const Camera& cam );
      virtual bool update(unsigned int x);
      Vector currentPosition;
   private:
      unsigned int internalTimer;
      unsigned int ttl;
      Vector originalPosition;
      Vector orientation;
      IndexedGeometryQuad* quad;
   };

}

