#pragma once

#include "IFace.h"
#include "AftrODEIncludes.h"
#include <vector>

namespace Aftr
{

class WOODE;

class IFaceWOODE : public virtual IFace
{
public:
   IFaceWOODE( WO* woUsingThisInterface );
   virtual ~IFaceWOODE();

   //ODE Specific
   //-------------------------------------------------------------------------
   //Methods specific for integrating this WOODE with ODE
   //Children of this class need to overload these methods so ODE can use these WorldObjects appropriately

   /**
      ONE of FOUR virtual ODE callback functions required for proper interaction with the Physics Engine.

      This method is automatically called by ODE when the user invokes the Physics Engine constructor; ie, "new's" the
      Physics Engine.

      For any children WOODE objects of this parent to have their ODE callbacks invoked, 
      the parent must push the child pointers into the 'std::vector< WO* > children' 
      list AND also into the 'std::vector< WOODE* > WOODEPtrsIntoChildren' list. The user
      must also ensure that for any additions/removals of a WOODE child to/from 
      the 'std::vector< WO* > children' list, the corresponding pointer must be added/removed
      from the 'std::vector< WOODE* > WOODEPtrsIntoChildren' list.

      This method creates the ODE representation of this WOODE. That is, this creates a body and geometric shape that is used
      by ODE for collision detection and force accumulation.
      
      For example, if this WOODE's \see ODE_PRIM_TYPE is set to a BOX, then when ODE invokes
      this method, an ODE "Box" will be created. This WOODE's \see odeID represent's an "ODE Pointer" to the
      cooresponding ODE body.
      
      The box's geometric dimensions will be taken from this WOODE's Model's Bounding Box. 
      The box's mass will be taken from this WOODE's mass.
      The box's initial orientation will be taken from this WOODE's Model's displayMatrix.
      Again, this WOODE's \see odeID shall point to the newly created ODE body (Physics Object).

      If you will be created complex objects with engines and joints, etc. Visit this site for the official
      ODE API documentation and VERY useful description of how ODE works:
      http://www.ode.org/ode-latest-userguide.html
   */
   virtual void ODEinitializeInODE() = 0;

   /**
      ONE of FOUR virtual ODE callback functions required for proper interaction with the Physics Engine.

      This method destroys all corresponding physics engine objects (ODE objects) created within
      \see ODEinitializeInODE(). This method does not touch any graphical elements of the WOODE
      such as the model, etc; it simply removes all bodies, joints, etc that were created when this object
      was initialized within ODE.

      This method is called in a clustered environment, when a WOODE residing on this server cluster instance
      is handed off to a neighboring server. This method essentially removes all phsyics pertaining to this
      WOODE out of the current simulation thereby reducing the computational load of this cluster server.

      Note that after invokation of this method, this WOODE should be removed from the GLView::worldLst, otherwise,
      during the next physics tick, the ODEupdateForcesAndJoints will attempt to use ODE objects (bodies, joint,etc)
      that no longer exist causing an error.

      This method only needs to be overloaded for "complex" physics objects; that is, any object that uses
      multiple ODE bodies that are connected to each other via joints.
      
      In otherwords, if the ODEinitializeInODE creates more ODE objects than the default WOODE::ODEinitializeInODE 
      method, then this method will need to be overloaded to properly destroy ALL of those ODE objects created
      in the corresponding ODEinitializeInODE.

      For any children WOODE objects of this parent to have their ODE callbacks invoked, 
      the parent must push the child pointers into the 'std::vector< WO* > children' 
      list AND also into the 'std::vector< WOODE* > WOODEPtrsIntoChildren' list. The user
      must also ensure that for any additions/removals of a WOODE child to/from 
      the 'std::vector< WO* > children' list, the corresponding pointer must be added/removed
      from the 'std::vector< WOODE* > WOODEPtrsIntoChildren' list.
   */
   virtual void ODEdestroyInODE() = 0;

   /**
      ONE of FOUR virtual ODE callback functions required for proper interaction with the Physics Engine.

      This method is automatically called by ODE JUST BEFORE an ODE physics step is taken; ie, just before the
      physics engine detects collisions and applies all the accumulated forces over the last
      time step interval.

      For any children WOODE objects of this parent to have their ODE callbacks invoked, 
      the parent must push the child pointers into the 'std::vector< WO* > children' 
      list AND also into the 'std::vector< WOODE* > WOODEPtrsIntoChildren' list. The user
      must also ensure that for any additions/removals of a WOODE child to/from 
      the 'std::vector< WO* > children' list, the corresponding pointer must be added/removed
      from the 'std::vector< WOODE* > WOODEPtrsIntoChildren' list.

      Typically, most objects will be "dumb" like a pile of bricks sitting in a playground. Because the only
      motion these type of object are exposed to are collisions, nothing needs to be performed here. In fact, typically,
      only "smart" objects like a "user controlled human avatar, car, boat, or other complex object" will need any thing
      done in this method.

      This method is responsible for updating this WOODE's force and/or joint information of the ODE Body 
      JUST BEFORE an ODE step is taken.

      For example, if this WOODE is a car, the torque force from the engines and joints attaching the wheels to 
      the car body shall be updated here.

      If the object is made up of more than one ODE Prim (This WOODE has 1 or more Children with corresponding physics objects),
      the associated joints linking the Prims together are updated in this method.

      This method will be used ONLY by ODE. Do not manually call this, otherwise ODE's state machine will become undefined.
      
      All one needs to do here is:
      1. Apply forces to the bodies as necessary.
      2. Adjust the joint parameters as necessary.

      Look at \see WOFourWheeled::ODEupdateForcesAndJoints() for an example of updating a car's wheels and
      steering column.

      If you will be created complex objects with engines and joints, etc. Visit this site for the official
      ODE API documentation and VERY useful description of how ODE works:
      http://www.ode.org/ode-latest-userguide.html
   */
   virtual void ODEupdateForcesAndJoints() = 0;

   /**
      ONE of FOUR virtual ODE callback functions required for proper interaction with the Physics Engine.

      This methos is automatically invoked by ODE JUST BEFORE a render of the world occurs; ie, all the ODE body's
      are now in their new locations AND new orientations; however, the corresponding WorldObjects now need to be
      synchronized to its corresponding ODE body.

      For any children WOODE objects of this parent to have their ODE callbacks invoked, 
      the parent must push the child pointers into the 'std::vector< WO* > children' 
      list AND also into the 'std::vector< WOODE* > WOODEPtrsIntoChildren' list. The user
      must also ensure that for any additions/removals of a WOODE child to/from 
      the 'std::vector< WO* > children' list, the corresponding pointer must be added/removed
      from the 'std::vector< WOODE* > WOODEPtrsIntoChildren' list.

      This method is responsible for updating this WOODE's position and orientation according to 
      ODE's calculations JUST BEFORE the entire world is rendered. This means that GLView->numPhysicsStepsPerRender
      ODE steps have been taken.
      
      The DEFAULT action simply updates the position and orientation of this WOODE based on the newly calculated
      position and orientation of this WOODE's corresponding ODE body. If the WOODE contains any children
      this method is invoked on them as well.

      If you will be created complex objects with engines and joints or you need to do something "non-standard" here.
      Visit this site for the official ODE API documentation and VERY useful description of how ODE works:
      http://www.ode.org/ode-latest-userguide.html
   */
   virtual void ODEupdateToNewPositionOrientation() = 0;

   /**
      When a user creates an IFaceWOODE, the corresponding callbacks are invoked to simulate
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
      through a parent IFaceWOODE or another manual method.

      When this is set to false, it means the physics engine will automatically invoke
      all ODE callbacks on this IFaceWOODE.

      ODE callbacks should be invoked the proper number of times during each main simulation
      step.

      This value defaults to false. It must be set to true manually by the user when
      creating hiearchical objects that are callback-order dependent or when another
      manual invokation method is being used.
   */
   bool ODEUserInvokesODECallbacksManuallyOnThisInstance;

   /**
      Returns a pointer to a vector containing all IFaceWOODE instances.

      That is, if any object inherits from IFaceWOODE (and therefore implements the
      cooresponding abstract methods declared in IFaceWOODE) a pointer to the IFaceWOODE
      corresponding to that object resides in this vector. Each IFaceWOODE instance has a
      getWO() method which returns a WO* associated with this specific IFaceWOODE instance.

      For example, if a WOODE* x exists, then the corresponding IFaceWOODE y exists in this
      list. And a WOODE* to x can be gotten via:
      IFaceWOODE* ptrToY = IFaceWOODE::getIFaceMemberList()->at(i);
      WOODE* ptrToX = (WOODE*) ptrToY->getWO();

      This mechanism allows call backs associated with a given IFace to be invoked. For example,
      a PhysicsEngine may use this vector to invoke a physics callback on each physics object
      at the appropriate time during each tick of the simulation. Determining if the callback
      is called directly from here (automatically) or indirectly from another IFaceWOODE's
      hiearchical callback is determined by this->ODEUserInvokesODECallbacksManuallyOnThisInstance.
   */
   static std::vector< IFaceWOODE* >* getIFaceWOODEMemberList();

protected:
   static std::vector< IFaceWOODE* > IFaceWOODEMemberList;

};

} //namespace Aftr

