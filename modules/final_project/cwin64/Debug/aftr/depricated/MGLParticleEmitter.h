#pragma once

#include "ParticleSystem.h"
#include "MGL.h"
#include <vector>

namespace Aftr
{

   class MGLParticleEmitter : public MGL
   {
   public:
      MGLParticleEmitter(std::vector<ParticleSystem*> particleSystems = std::vector<ParticleSystem*>());
      MGLParticleEmitter(std::vector<ParticleSystem*> particleSystems, std::string texture);//particularly useful for point sprite emitters
      virtual ~MGLParticleEmitter();
      void addNewEmitter(ParticleSystem* n){particleSystems.push_back(n);}
      virtual void render( const Camera& cam );
      std::vector<ParticleSystem*> getParticleSystems(){return particleSystems;}
   protected:
      std::vector<ParticleSystem*> particleSystems;
   private:
   };

}

