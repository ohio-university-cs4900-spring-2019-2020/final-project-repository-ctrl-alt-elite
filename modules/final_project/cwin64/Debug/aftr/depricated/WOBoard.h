#pragma once

#include "WO.h"
#include <string>

namespace Steamie
{

   /**
   \class WOBoard
   \author Chad Mourning
   \brief A trifold board.

   Note: This class was made before onPhysicsEngineTick - should probably have its timing reworked.

   */

   enum BoardRotationPhase { brpFIRST = 0, brpSECOND, brpTHIRD, brpMAX_PHASES };

class WOBoard : public WO
{
public:	
   static WOBoard* New(std::string textures[3], float length = 2, float width = 1, int slices = 10, bool vert = false, Vector color = Vector(0,0,0), unsigned int updateTimer = 75000, float updateSpeed = .004f);
	virtual ~WOBoard();
   virtual void onPhysicsEngineTick();
protected:
   virtual void onCreate(std::string textures[3], float length, float width, int slices, bool vert, Vector color);
   WOBoard( unsigned int updateTime, float updateSpeed);
private:
   unsigned int updateTimer;
   unsigned int internalTimer;
   bool rotatePhase;
   BoardRotationPhase myRotationPhase;
   float rotateSpeed;
   float rotateAngle;
};

}

