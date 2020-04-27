//----------------------------------------------------------------------------
//Description: The WOSimpleOrbiter class represents a composite object which has
//a single parent and multiple children spaced at a varius radii from the 
//parent.  The user shall rotate the parent, thus causing all children to
//orbit around the parent such that one full revolution results in one full
//rotation of that child.
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once

#include "WO.h"
#include "ManagerEnvironmentConfiguration.h"

//----------------------------------------------------------------------------
//Description: The WO class 
//----------------------------------------------------------------------------
namespace Aftr
{

class WOSimpleOrbiter : public WO
{

public:
   static WOSimpleOrbiter* New( const std::string modelFileName = ManagerEnvironmentConfiguration::getSMM() + "/models/sphereR15Sun.wrl" );
   virtual ~WOSimpleOrbiter();

   virtual void onUpdateWO(); //spin the planets around
   virtual void onPhysicsEngineTick();
   

protected:
   WOSimpleOrbiter();
   virtual void onCreate( const std::string& modelFileName );
   virtual void createChildren();


};
} //namespace Aftr
