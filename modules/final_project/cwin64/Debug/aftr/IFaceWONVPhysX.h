#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_NV_PHYSX

#include "IFace.h"
#include <vector>
#include "PxPhysicsAPI.h"

using namespace physx;

namespace Aftr
{

class PhysicsEngineNVPhysX;

class IFaceWONVPhysX : public virtual IFace
{
public:
   IFaceWONVPhysX( WO* woUsingThisInterface );
   virtual ~IFaceWONVPhysX();

   /**
      Returns a pointer to a vector containing all IFaceWONVPhysX instances.

      That is, if any object inherits from IFaceWONVPhysX (and therefore implements the
      cooresponding abstract methods declared in IFaceWONVPhysX) a pointer to the IFaceWONVPhysX
      corresponding to that object resides in this vector. Each IFaceWONVPhysX instance has a
      getWO() method which returns a WO* associated with this specific IFaceWONVPhysX instance.

      For example, if a WOODE* x exists, then the corresponding IFaceWONVPhysX y exists in this
      list. And a WOODE* to x can be gotten via:
      IFaceWONVPhysX* ptrToY = IFaceWONVPhysX::getIFaceMemberList()->at(i);
      WOODE* ptrToX = (WOODE*) ptrToY->getWO();

      This mechanism allows call backs associated with a given IFace to be invoked. For example,
      a PhysicsEngine may use this vector to invoke a physics callback on each physics object
      at the appropriate time during each tick of the simulation. Determining if the callback
      is called directly from here (automatically) or indirectly from another IFaceWONVPhysX's
      hiearchical callback is determined by this->ODEUserInvokesODECallbacksManuallyOnThisInstance.
   */
   static std::vector< IFaceWONVPhysX* >* getIFaceWONVPhysXMemberList();

   /**
      When a user creates an IFaceWONVPhysX, the corresponding callbacks are invoked to simulate
      phyisical behavior. For simple objects like a falling brick, the callbacks are simple 
      and can be invoked in any order without loss of determinism. However, if hierarchical
      objects (such as a car) exist, the order in which all child bodies are updated is
      important. For example, updating a tire's force on a car chassis is not helpful if
      the chassis hasn't yet told the tire which direction it should point for the current 
      tick. In this case, the chassis's ODE callback should also be  responsible for updating 
      all children that need the parent's information up to date prior to updating themselves;
      that is, the car chassis (parent body) should invoke ODEupdateForcesAndJoints() on 
      each child manually after updating itself.

      The user should ensure this bool is set to false for the parent chassis and set to true
      for all children wheels. This way, the parent ODE callbacks are automatically
      invoked while the children callbacks are indirectly invoked via the parent. If the user
      fails to set this bool to false for each wheel, then the wheel's ODE callbacks
      will be invoked twice, (once by the parent chassis and once by the automatic 
      ODE callbacks) possibly causing incorrect force/state to be set upon
      the parent chassis as well as the wheel.

      When this is set to true, it means the user is manually invoking these callbacks
      through a parent IFaceWONVPhysX or another manual method.

      When this is set to false, it means the physics engine will automatically invoke
      all ODE callbacks on this IFaceWONVPhysX.

      ODE callbacks should be invoked the proper number of times during each main simulation
      step.

      This value defaults to false. It must be set to true manually by the user when
      creating hiearchical objects that are callback-order dependent or when another
      manual invokation method is being used.
   */
   bool NVPhysXUserInvokesPhysXCallbacksManuallyOnThisInstance;

   PxActor* getPxActor();
   void setPxActor( PxActor* actor );
   void setPhysicsEngine( PhysicsEngineNVPhysX* pe );
   PhysicsEngineNVPhysX* getPhysicsEngine();

   //PxActorDesc* getNxActorDesc();

   virtual void onCreateNVPhysXActor() = 0;
   virtual void updatePoseFromPhysicsEngine( const PxActiveTransform* trans ) = 0;

protected:
   static std::vector< IFaceWONVPhysX* > IFaceWONVPhysXMemberList;

   //NVIDIA PhysX member variables for an actor
   //PxActorDesc actorDesc;
   PxActor* actor;

   PhysicsEngineNVPhysX* NVPhysXEngine;
};

} //namespace Aftr

#endif //AFTR_CONFIG_USE_NV_PHYSX
