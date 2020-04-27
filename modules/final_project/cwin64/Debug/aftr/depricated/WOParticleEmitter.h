#pragma once

#include "WO.h"
#include "ParticleSystem.h"
#include <vector>


namespace Aftr
{


class WOParticleEmitter : public WO
{
public:
   static WOParticleEmitter* New(std::vector<ParticleSystem*> particleSystems = std::vector<ParticleSystem*>());
   
   void addNewEmitter(ParticleSystem* n);
   virtual ~WOParticleEmitter();
   void onPhysicsEngineTick();
   
   #ifdef AFTR_CONFIG_USE_TNL
      virtual void packNetState( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      virtual void unPackNetState( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
   #endif
protected:
   virtual void onCreate(const std::vector<ParticleSystem*>& particleSystems);
   WOParticleEmitter();
   unsigned int lastPacketSent;
private:

};

}

