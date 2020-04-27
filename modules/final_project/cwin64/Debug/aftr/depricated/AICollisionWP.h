#pragma once

#include "WOWayPointSpherical.h"
#include <vector>

namespace Aftr
{

class WayPointParametersBase;

class AICollisionWayPoint : public WOWayPointSpherical
{
public:	
AICollisionWayPoint( const WayPointParametersBase& params,
                    float radius,
		 float force = 10,
		 float maxDistance = 3.1
      );
virtual ~AICollisionWayPoint();
virtual void onTrigger();
virtual void render( const Camera& cam );
float getForce(){return force;}
float getMaxDistance(){return maxDistance;}
void setColor(int r, int g, int b);
private:
	float force;
	float maxDistance;
   int r;
	int g;
	int b;
};

}

