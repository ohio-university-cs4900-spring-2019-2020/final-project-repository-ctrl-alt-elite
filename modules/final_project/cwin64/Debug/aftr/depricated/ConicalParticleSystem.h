#pragma once

#include "ParticleSystem.h"
#include "SphericalVector.h"
#include "Vector.h"

namespace Aftr
{
   class WO;

class ConicalParticleSystem: public ParticleSystem
{
public:
   ConicalParticleSystem(WO* parent, float width, Vector offSet, unsigned int minTTL, unsigned int maxTTL);
   virtual ~ConicalParticleSystem(){}
   unsigned int getMaxTTL(){return maxTTL;}
   unsigned int getMinTTL(){return minTTL;}
   void setMaxTTL(unsigned int x){maxTTL = x;}
   void setMinTTL(unsigned int x){minTTL = x;}
   float getWidth(){return width;}
   void setWidth(float x){width = x;}
   Vector& getOffSet(){return offSet;}
   void setOffSet(Vector x){offSet = x;}
   //--------------------------------------------------
   virtual Particle* emit() = 0;
   virtual void update(unsigned int x) = 0;
   virtual void render( const Camera& cam );
protected:
   WO* parent;
   float width;
   Vector offSet;
   unsigned int minTTL, maxTTL;
};
}

