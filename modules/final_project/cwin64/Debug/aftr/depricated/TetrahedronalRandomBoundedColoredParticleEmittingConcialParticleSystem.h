#pragma once

#include "ConicalParticleSystem.h"

namespace Steamie
{
      class SphericalVector;
   class Particle;


   class TetrahedronalRandomBoundedColoredParticleEmittingConicalParticleSystem : public ConicalParticleSystem
   {
   private:
   public:
      TetrahedronalRandomBoundedColoredParticleEmittingConicalParticleSystem(WO* parent, float width, Vector offSet, unsigned int minTTL, unsigned int maxTTL, ColorGLubyte high, ColorGLubyte low, unsigned int emitTimer);
      virtual ~TetrahedronalRandomBoundedColoredParticleEmittingConicalParticleSystem(){};
      virtual Particle* emit();
      virtual void update(unsigned int x);
   protected:
      ColorGLubyte low;
      ColorGLubyte high; 
      unsigned int internalTimer;
      unsigned int emitTimer;
   };
}

