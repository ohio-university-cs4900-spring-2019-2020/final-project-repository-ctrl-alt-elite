#pragma once

#include "Particle.h"
#include <vector>


namespace Aftr
{
   class ParticleSystem
   {
   public:
      virtual void update(unsigned int x) = 0;
      virtual Particle* emit() = 0;
      virtual void render() = 0;
      virtual ~ParticleSystem(){children.clear();}
   private:
   protected:
      std::vector<Particle*> children;
   };
}

