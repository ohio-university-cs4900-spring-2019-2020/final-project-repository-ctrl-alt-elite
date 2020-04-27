#pragma once

#include "AftrConfig.h"
#include "IFace.h" 
#include "AftrOpenGLIncludes.h"
#include "AftrSDLIncludes.h"
#include "AftrManagers.h"
#include <iostream>
#include <string>
#include "Vector.h"
#include "WOMacroMethods.h"
#include "WorldObjectChildContainer.h"

#ifdef AFTR_CONFIG_USE_TNL
   #include "tnlVector.h"
#endif


namespace Aftr
{

class Animation;
class Model;
class ManagerSDLTime;
class NetWO;
class ConnClientGhost;
class Camera;
class NetClusterWOCloneManager;
class AftrGeometryFrustum;
class WOGJoint;
class AftrGeometryRayVsFace;
enum class AftrGeometricTerm : unsigned char;

enum class RENDER_ORDER_TYPE : unsigned char { roLIGHT = 0, roOPAQUE, roBLEND_FUNC_GL_ONE, roTRANSPARENT, roOVERLAY };// , roNUM_RENDER_ORDER_TYPE };
std::ostream& operator<<( std::ostream& out, const RENDER_ORDER_TYPE& rot );

/** 
   \class WO
   \author Scott Nykl
   \brief A WO and all children do not have an associated ODE Body. Therefore, it cannot collide with
   other objects. WOGhosts can be linked together hierarchically and can be animated ( \see WOHuman ).

   The WO class is a world object with NO associated
   ODE physics object. These objects are useful for visual representation of
   things that do not need to utilize ODE/collision detection. For example, a
   bird, distant orbiting planet, a particle effect, a "virtual force field"
   that is merely a transparent plane, an animated walking human, etc.

   A unique feature of the WO is its ability to create joints between different
   WO objects. These joints can be animated/modified via the
   changeOrientationWRTparent... method calls.

   A common technique to create an 'advanced' object is to use a hierarchical collection of WOGhosts as
   children of a WOBoundingShell. Remember that a WOBoundingShell inherits from WO (not WO) and
   therefore has a corresponding ODE body. This way, an animated object, such as a walking human, 
   can be linked combined with ODE's physics. Simply imagine bounding box around an animated human, where
   the bounding box is used for collision detection, gravity, surface properties, etc, and the children
   ghost objects animate the human to make it look realistic.
    \{
*/

class WO : public virtual IFace
{

public:

   /**
      This macro must be invoked at the beginning of each WO header file to support serialization and
      other macro-based methods described in this comment text below.
      Similarly, a corresponding macro must be invoked at the beginning of each WO .cpp file.
      
      The first token to pass in is the case-sensitive class name of this class. The second 
      token to pass in is the case-sensitive parent class name this class inherits from.
      The base WO is a special case because it does not inherit from any class, thus it
      simply sets its parent to itself.
      Typically, let's say one creates a new class declaration such as:
         'class WOMyObject : public WO'
      In this case, within the public: section of the class declaration, the developer
      would invoke:
         'WOMacroDeclaration( WOMyObject, WO );'

      This macro invocation inserts several useful prototypes into this header file.
      -# std::string getClassName() // Returns a string containing the name of this class
      -# std::string getSuperClassName() // Returns a string containing the name of the class inherited from
      -# ThisClassType is defined as a type which refers to the class type of an instance of this class.
      -# SuperClassType is defined as a type which refers to the parent class type an instance of this class inherited from.
      -# A Stub class declaration responsible for registering itself with the ManagerSerializableWOMap. This
         is used by the serialization system to create an instance of a class by reading from an input source
         such as a file.

   */
   WOMacroDeclaration( WO, WO );

   /**
      Default constructor. Creates a WO with no associated VRML graphical model. This is typically called
      when the user will new the member variable 'model' as a MGL (Open GL Model) derivative.
   */
   static WO* New();

   /**
      Creates a WO with an associated VRML graphical model.
      \param modelFileName The path to the VRML model to load and associate with this WO.
   */
   static WO* New( const std::string& modelFileName, Vector scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );

   WO( const WO& toCopy ) = delete;
   WO( WO&& toMove ) = delete;
   WO& operator=( const WO& toCopyAssign ) = delete;
   WO& operator=( WO&& toCopyMove ) = delete;

   /**
      Destroys a WO, this explicitly deletes all associated joints, and the implicit destructor call
      to the WO removes all children and everything else.
   */
   virtual ~WO();

   /**
      Serializes this WO instance and its specific member properties to the output stream.
      This method serializes enough state such that when this WO's corresponding fromFile(...)
      is invoked, all attributes and state are preserved.
   */
   virtual void toFile( std::ostream& sout );

   /**
      Deserializes a WO from the input stream and returns an instance of that
      specific WO type whos member properties are restored to the same state when the WO
      was serialized.
   */
   static WO* fromFile( std::istream& sin );

   /** 
      \brief Returns the parent of this WO.
      
      WorldObjects are hierarchical in that a WO can have one or more children and those
      children can have one or more of their own children.

      \return A pointer to the parent WO.
   */
   WO* getParentWorldObject();
   
   /**
      Sets the parent of this WO. A WO can have at most ONE parent.
      This should only be used once on creation or problems will occur
      \param wo The WO* that is this child's parent.
   */
   void setParentWorldObject( WO* wo );

   /**
      Sets this WO's corresponding std::string label to inLabel. This is a user convience;
      no part of the engine relies on an object's label.
   */
   virtual void setLabel( const std::string& inLabel );

   /**
      Returns an std::string that represents a user-specified identifier.
      The engine itself does not user this; however, it can be useful for a user to label his
      WorldObjects.
      \returns A NULL Terminated C-String that is the label of this WO.
   */
   std::string getLabel();

   /**
      Returns a globally unique identifier for this WO. This value
      is generated automatically by Aftr and cannot be set by the user.
      This is helpful for OpenGL Selection and creating display lists corresponding to a
      WO.
      \return The globally unique identifier of this WO.
   */
   unsigned int getID() const { return this->id; }

   /// Returns a string containing information about this WO instance. 
   /// Including woID, label, class type, etc...
   virtual std::string toString( unsigned int hierarchyDepth = 0 );

   /// Invokes WO::toString() on this instance an recursively on all children.
   virtual std::string toStringRec( unsigned int hierarchyDepth = 0 );

   /**
      Returns this WO's globally unique identifier as a globally
      unique 24-bit color. Used by OpenGL Selection. 
      
      The user passes in 24 bits as three 8-bit colors Red, Green, and Blue,
      respectively. The lowest 24-bits of the globally unique identifier are placed
      into red, green, and blue 8-bit bytes. The highest 8-bits of the globally unique
      identifier are NOT used as there is not enough space.

      |----------- 32-bit ID --------|
      xxxxxxxxRRRRRRRRGGGGGGGGBBBBBBBB
              |-red--||-Green||-Blue-|
      \param red The Bits 23 through 16 of the globally unique Identifier.
      \param green The Bits 15 through 8 of the globally unique Identifier.
      \param blue The Bits 7 through 0 of the globally unique Identifier.
   */
   void convertIDtoUniqueColor( GLubyte& red, GLubyte& green, GLubyte& blue );

   /**
      Returns a reference to the std::vector containing all of this WO's
      children.
      \return A Reference to a vector of children WO*.
   */
   WorldObjectChildContainer& getChildren() { return this->children; }

   /**
      Returns the count of all decendents of this node not including this node itself.
   */
   size_t getCountOfAllDecendants();

   /**
      Returns the number of ancestors this WO has. For example:
      WO* a = WO::New(); WO* b = WO::New(); WO* c = WO::New(); WO* d = WO::New();
      c.getChildren().push_back( d ); //d is child of c
      b.getChildren().push_back( c ); //c is child of b
      a.getChildren().push_back( b ); //b is child of a
      worldLst->push_back( a ); //a is a root node
      
      if WO* A has a child B who has a child C who has a child D, then D's depth is 3, C's 
      depth is 2, B's depth is 1, and A's depth is 0.
   */
   size_t getDepthFromRootWO();

   /**
      Returns the internal model of the Model class
      \return A Pointer to the actual corresponding Model of this WO.
   */
   virtual Model* getModel();
   virtual const Model* getModel() const;

   /**
      Same as getModel(), but is templated so the user does not need to perform
      a static_cast<T> on the return type. This is simply a convenience method.
   */
   template< typename T, typename R = std::remove_pointer_t<T> > R* getModelT()
   {
      assert( this->model != nullptr );
      if constexpr( std::is_pointer_v<T> )
         return static_cast<R*>( this->model );//Lets wo->getModelT<MGLQuad*>() work as expected.
      return static_cast<R*>( this->model );   //Lets wo->getModelT<MGLQuad>() work as expected.
   }

   /**
      Sets this WO's model pointer to the in passed model. This WO is now the parent
      of the model. A model can only be owned by exactly one WO at any time.
   */
   virtual void setModel( Model* model, bool deleteExistingModel = true );

   /**
      Takes as input, an array of 16 floats and copies the current display matrix of the
      model into that array.
   */
   virtual void getDisplayMatrix( float* outParamDispMat4x4 ) const;

   virtual Mat4 getDisplayMatrix() const;

   /**
      Returns a Vector representing the X,Y,Z location of this WO in global coordinates.
      \return A Vector representing the X,Y,Z location of this WO in global coordinates.
   */
   virtual Vector getPosition() const;

   /**
      Sets the X,Y,Z location of this WO in global coordinates.

      The user typically calls this method inside of GLViewXYZ::LoadMap() to position the WO 
      initially.

      \param newXYZ A Vector representing the new X,Y,Z location of this WO in global coordinates.
   */
   virtual void setPosition( const Vector& newXYZ );
   virtual void setPosition( float x, float y, float z );

   /** 
      Sets the X,Y,Z global coordinate of this WO. The children are intentionally left UNCHANGED. This method
      is invoked by the network subsystem to sync each newly received NetWO's position (from the server) to
      the local graphical representation of the WO stored locally on this client.
      \param newXYZ The new X,Y,Z global coordinate of only this WO. All The WO's children are UNCHANGED.
   */
   virtual void setPositionIgnoringAllChildren( const Vector& newXYZ );

   /**
      Similar to WO::setPosition. However, instead of setting this WO's position, this
      WO is moved from its current location by dXdYdZ. That is, if this WO is at (10,20,30)
      and moveRelative( Vector( 4,5,6 ) ) is made, this WO's global position shall be set to (14,25,36).

      \param dXdYdZ A Vector with the corresponding X,Y, and Z values represent the delta X, delta Y, and delta Z
                      movement, respectively.
   */
   virtual void moveRelative( const Vector& dXdYdZ );

   virtual void moveRelativeIgnoringAllChildren( const Vector& dXdYdZ );

   /**
      Returns a normalized vector pointing in the direction the WO is "facing". According to convention,
      the WO's "front" (think nose of airplane) points along the +X-axis, the plane's tail points towards
      the +Z-axis, and the wings lie along the Y axis. The left wing points along the +Y-axis and the right wing
      points towards the -Y-axis.

      \return Normalize vector pointing in the direction this WO is currently facing.
   */
   virtual Vector getLookDirection() const;
   
   /**
      Returns a normalized vector pointing perpendicular to the direction the WO is "facing". According to convention,
      the WO's "front" (think nose of airplane) points along the +X-axis, the plane's tail points towards
      the +Z-axis, and the wings lie along the Y axis. The left wing points along the +Y-axis and the right wing
      points towards the -Y-axis. This method would return a vector pointing along the +Z-axis.

      \return Normalize vector pointing in the direction perpendicular to where this WO is currently facing. The
              current roll of the object is accounted for.
   */
   virtual Vector getNormalDirection() const;

   virtual void rotateToIdentity(); ///< Convenience method that invokes this corresponding method on this WO's model
   virtual void rotateAboutRelX( float deltaRadianAngle ); ///< Convenience method that invokes this corresponding method on this WO's model
   virtual void rotateAboutRelY( float deltaRadianAngle ); ///< Convenience method that invokes this corresponding method on this WO's model
   virtual void rotateAboutRelZ( float deltaRadianAngle ); ///< Convenience method that invokes this corresponding method on this WO's model
   virtual void rotateAboutGlobalX( float deltaRadianAngle ); ///< Convenience method that invokes this corresponding method on this WO's model
   virtual void rotateAboutGlobalY( float deltaRadianAngle ); ///< Convenience method that invokes this corresponding method on this WO's model
   virtual void rotateAboutGlobalZ( float deltaRadianAngle ); ///< Convenience method that invokes this corresponding method on this WO's model
   
   //User Keyboard Input Specific
   //-----------------------------------
   /**
      Fired when this WO is the current actor AND a key is pressed. Note that
      if the GLView defines a keypress for key x, that will be handled BEFORE
      this method gets passed key x. This also means that if the GLView returns
      execution in its onKeyDown method prior to calling this method, this method
      may never be invoked. For example, the 'q' to quit will never be passed
      to this method as GLView handles the event first, and then terminates
      the program.

      \param key SDL_KeyboardEvent generated by the key press
   */
   virtual void onKeyDown( const SDL_KeyboardEvent& key );

   /**
      Fired when this WO is the current actor AND a key is released. Note that
      if the GLView defines a key release for key x, that will be handled BEFORE
      this method gets passed key x. This also means that if the GLView returns
      execution in its onKeyUp method prior to calling this method, this method
      may never be invoked. For example, the 'q' to quit will never be passed
      to this method as GLView handles the event first, and then terminates
      the program.

      \param key SDL_KeyboardEvent generated by the key press
   */
   virtual void onKeyUp( const SDL_KeyboardEvent& key );
   //-----------------------------------

   //User Mouse Input Specific (for selection only right now
   //Overloadable, mouse functions for WorldObjects.

   /**Invoked when this WO is the current actor and the user presses a mouse button*/
   virtual void onMouseDown( const SDL_MouseButtonEvent& mouse );
   /**Invoked when this WO is the current actor and the user releases a mouse button*/
   virtual void onMouseUp( const SDL_MouseButtonEvent& mouse );
   /**Invoked when this WO is the current actor and the user scrolls the mouse wheel*/
   virtual void onMouseWheelScroll( const SDL_MouseWheelEvent& e );
   /**Invoked when this WO is the current actor and the user moves a mouse*/
   virtual void onMouseMove( const SDL_MouseMotionEvent& mouse );
   /**
      Invoked when the user clicks on this WO via the mouse cursor while selection is enabled.
      For example, if the Left CTRL key is held down while a user clicks on this WO, this method
      is invoked.
   */
   virtual void onMouseDownSelection( const SDL_MouseButtonEvent& mouse );

   /**
      When a WO is selected via onMouseDownSelection(...), if that WO has a non NULL parent,
      the default behavior is to notify the parent that the child was selected. This may propagate
      up to the "top" WO that may choose to use this information.

      This is intended to used when a hierarchy of objects (for example, a robotic arm) are composed of
      a non-specialized type of child such as a WO*. Instead of forcing the programmer to create a special
      child subclass for each type of child, the programmer only needs to create an intelligent root WO*
      (the topmost parent). Using this callback, the topmost parent will be notified with a child is selected.
      All the logic to do some intelligent behavior can then be placed in the parent. This avoids having
      to create subclasses only to add code in each child class.
   */
   virtual void onMouseDownChildWasSelected( const SDL_MouseButtonEvent& mouse, WO* selectedChild );
   //-----------------------------------
   
   /**
      Renders this WO's Graphical Model (this->model). If any children WorldObjects exist, each child's
      render() method is also invoked. Thus, the parent and all it's children are drawn to the screen.

      This method is typically invoked inside of the GLView's render() method; which automatically draws renders all
      WO* that were added to the std::vect< WO* >worldLst inside of GLViewXYZ::LoadMap().

      The user should never need to directly call this method.
   */
   virtual void render( const Camera& cam );

   /**
      This method is invoked by the \see GLView::onMouseDownSelection method when the user is in "WO Selection Mode" and
      clicks somewhere within the SDL Window. Every WO (and its children) are drawn in a slightly different
      color. Then, the color clicked on by the user identifies which WO* the user clicked on.

      GLView's \see GLView::lastSelectedWorldObject* shall point to the selected WO* after the 
      GLView::onMouseDownSelection returns. 
      
      The user should never need to directly call this method.
   */
   virtual void renderSelection( const Camera& cam );

   /**
      Resets the joint transform to identity matrix, and resets all the children's joints to
      the identity matrix as well. This will effectively reset the WO model to its original
      orientation before any joint manipulations occurred.
   */
   virtual void resetJoints();

   /** 
      After setting a parent of this WO, this locks the distance 
      and orientation between the parent and child. After this, whenever the parent
      moves and/or rotates, the child shall remain oriented appropriately.
   */
   virtual void lockWRTparent( WOGJoint* joint = NULL);

   /**
      Free's this child from being locked w.r.t the parent. This object is STILL a child of the parent.
      Additionally, the enableChangeableOrientationWRTparent gets reset to false. This object can call
      'lockWRTparent()' again at any time to fix this object's new position and orientation w.r.t the
      parent (or even a different parent, if this object's parent is changed).
   */
   virtual void unLockWRTparent();

   /**
      Returns true if this WO is locked with respect to its parent; false, otherwise.
      \return true if this is locked with respect to its parent; false, otherwise.
   */
   virtual bool isLockedWRTparent() { return this->IsLockedWRTparent; }

   /**
      Changes this object's relative horizontal offset by delaTheta.
      Mathematically, this method rotates this object's joint transform matrix
      deltaTheta radians about the relative positive z-axis.
      This is equivalent to the pitch.

      \param deltaTheta Radian angle by which this object shall be rotated about
      its relative +z-axis. This is equivalent to the pitch.
   */
   virtual void changeOrientationWRTparentDeltaTheta( float deltaTheta );

   /**
      Changes this object's relative vertical offset by deltaPhi.
      Mathematically, this method rotates this object's joint transform matrix
      deltaPhi radians about the relative positive y-axis.
      This is equivalent to the yaw.

      \param deltaPhi Radian angle by which this object shall be rotated about
      its relative +y-axis. This is equivalent to the yaw.
   */
   virtual void changeOrientationWRTparentDeltaPhi( float deltaPhi );

   /**
      Changes this object's relative roll offset by deltaRoll.
      Mathematically, this method rotates this object's joint transform matrix
      deltaRoll radians about the relative positive x-axis.

      \param deltaRoll Radian angle by which this object shall be rotated about
      its relative +x-axis.
   */
   virtual void changeOrientationWRTparentDeltaRoll( float deltaRoll );

   /**
      Returns a pointer to the WOGJoint that attaches this WO to its parent WO
      \return The WOGJoint that attaches this WO to its parent WO; NULL, if no joint currently exists.
   */
   virtual WOGJoint* getJoint();

   #ifdef AFTR_CONFIG_USE_TNL
      //Network Subsystem Specific ----------------------------------------------
      void destroyNetWOAndChildNetWOs();
      void setNetWO( NetWO* newNetWO );
      NetWO* getNetWO();
      virtual void onRegisteredWithServer();
      virtual void packNetState( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      virtual void unPackNetState( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );

      void setNetClusterWOCloneManager( NetClusterWOCloneManager* nccm );
      NetClusterWOCloneManager* getNetClusterWOCloneManager();

      //int vec and float vec (signals/integers w/ floats)
      void send_C2S_GuranteedOrderedData( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      virtual void received_C2S_GuranteedOrderedData( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      void send_S2C_GuranteedOrderedData( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      virtual void received_S2C_GuranteedOrderedData( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      void send_C2S_EZ(TNL::S32 message);//send a single guranteed ordered int, client to server
      void send_S2C_EZ(TNL::S32 message);//send a single guranteed ordered int, server to client

      //Int vec and string vec (signals/integers w/ strings)
      void send_C2S_GuranteedOrderedData( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< std::string >& stringVec );
      virtual void received_C2S_GuranteedOrderedData( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< std::string >& stringVec );
      void send_S2C_GuranteedOrderedData( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< std::string >& stringVec);
      virtual void received_S2C_GuranteedOrderedData( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< std::string >& stringVec );

      //Network methods that are NOT ghosted to a WO on all instances. These methods are useful when
      //a WO which manages state on a specific machine for a given module changes its internal state.
      //For example, the WOMessenger in Space Race is resonsible for managing state of the client's progress
      //through the race course. If the client clicks the 'I Give Up' button, then the server needs to know that
      //that specific client gave up. When the server replies to this, the server must NOT send that message to
      //the WOMessenger instances on ALL clients. The server must send that message only to the WOMessenger on
      //the client that gave up.
      void send_C2S_NonGhostedGuranteedOrderedData( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      virtual void received_C2S_NonGhostedGuranteedOrderedData( ConnClientGhost* toClient, TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      void send_S2C_NonGhostedGuranteedOrderedData( ConnClientGhost* toClient, TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      virtual void received_S2C_NonGhostedGuranteedOrderedData( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      //-------------------------------------------------------------------------
   #endif

   /**
      Populates output with the nearest point on the ray between tail and head intersects the WO or one of its children, defined by
      Aftr conventions, i.e. uses composite index and vertex lists.

      Internally, this method transforms the in passed ray through the inverse of the display matrix
      and subtracts this WO's position; therefore, the actual ray intersection tests can be done
      without transforming any of the original face positions (faster).
      
      This method will call the WO's Model's Model::getNearestPointWhereLineIntersectsMe(...),
      which assumes the above transformations have already taken place. The user would typically 
      call this method to intersect a ray at an arbitrary location with a WO at 
      an arbitrary location and orientation.

      If Vector* statistics is not NULL; then 
            statistics->x returns the number of OctnodesTested during this call
            statistics->y returns the number of face linePlaneIntersections tested during this call
            statistics->z returns the number of isInsideTrangle( pt) tested during this call

      returns AftrGeometricTerm::geoSUCCESS if a point is found
      returns AftrGeometricTerm::geoERROR if no point is found
   */
   virtual AftrGeometricTerm getNearestPointWhereLineIntersectsMe(const Vector& rayTail, 
      const Vector& rayHead, Vector& output, bool lineSegment = true, 
      bool useOctreeSearchIfAvailable = true, Vector* statistics = NULL,
      AftrGeometryRayVsFace* hitFace = NULL );

   /**
      Returns true if this WO Model's BoundingBox is inside of the viewing frustum; false, otherwise.
      \param viewportFrustum The camera's AftrGeometryFrustum that is used against this WO Model's
             BoundingBox.
   */
   virtual bool isInViewingFrustum( const AftrGeometryFrustum& viewportFrustum );

   bool useFrustumCulling; ///< If true, frustum culling is performed on this WO Model's boundingbox to accelerate rendering
   bool isVisible; ///< If true, the WO's model shall be rendered; otherwise the WO shall not be rendered.
   void makeMeAndAllMyChildrenInvisible(); ///< Makes this WO and all it's children invisible
   void makeMeAndAllMyChildrenVisible(); ///< Makes this WO and all it's children visible

   /**
      Determines how this object is drawn by OpenGL.  Should this WO's model be rendered as opaque, transparent, or is the object a light? \see RENDER_ORDER_TYPE
   */
   RENDER_ORDER_TYPE renderOrderType;

   /**
      Called on every WO in the world list during GLView::updateWorld() either: exactly once, or exactly one time
      per Physics Engine Step.

         Purpose: This method may be used by the user as a mechanism of internal time keeping and other non-ODE related
         internal house-keeping actions that need to be performed every physics 'tick'. If no physics engine exists, this method is
         invoked ONCE per GLView::updateWorld() call. If a physics engine exists, this method is invoked once before EVERY
         physics step is taken. Thus, if the ratio of 'number of physics steps to number of renders' is 15, then this method 
         shall be invoked on every object in the world list 15 times.

         Example code block to use this method to keep track of the time since an action dealing with this object occurred:
         virtual void onPhysicsEngineTick()
         {
            this->myPrivateTimeCumulator += ManagerSDLTime::getTimeSinceLastPhysicsIteration();
            while( this->myPrivateTimeCumulator >= MY_TIME_THRESHOLD )
            {
               foo();
               this->myPrivateTimeCumulator -= MY_TIME_THRESHOLD;
            }
         }

         DESCPTION:
         If and only if the Physics Engine is NULL (is not used by the module), this method shall be invoked
         once per GLView::updateWorld() invocation.

         If and only if the Physics Engine is NOT NULL ( IS USED by the module), this method shall be invoked
         once prior to EACH iteration the Physics Engine takes. Thus, if the ratio of 'number of physics steps to
         number of renders' is 15, then this method shall be invoked on every object in the world list 15 times.
         Each invocation occurs just before the GLView calls on the Physics Engine to take a step.
   */
   virtual void onPhysicsEngineTick();

   /**
      This method is invoked within GLView::init() after LoadMap has completed,
      the physics engine has been created, and the Network Subsystem is fully
      initialized; that is, the Simulation is fully initialized and ready to
      begin. No simulation ticks have yet been taken.
      The simulation is completely ready to begin. 
      
      Users can overload this method to perform any 'last minute' initialization
      that may need to be based on any previous init information that may not have
      been available within the World Object's constructor.

      This is invoked regardless of NetSimulation type client, server, or standalone.
   */
   virtual void onSimulationCompletelyInitialized();

   /**
      Identical to onSimulationCompletelyInitialized; however, this is only
      invoked if this instance is a server. This is not invoked if this
      instance is NET_SIM_TYPE::nstSTANDALONE or NET_SIM_TYPE::nstCLIENT.

      The user should place only server-specific initialization instructions
      in here.

      Any general, non-server specific instructions, should be placed
      inside of onSimulationCompletelyInitialized.
   */
   virtual void onSimulationCompletelyInitializedOnServerSide();

   /**
      Identical to onSimulationCompletelyInitialized; however, this is only
      invoked if this instance is a NET_SIM_TYPE::nstCLIENT (client). This is not invoked if this
      instance is NET_SIM_TYPE::nstSTANDALONE or NET_SIM_TYPE::NET_SIM_TYPE::nstSERVER.

      The user should place only client-specific initialization instructions
      in here.

      Any general, non-client specific instructions, should be placed
      inside of onSimulationCompletelyInitialized.
   */
   virtual void onSimulationCompletelyInitializedOnClientSide();

   /**
      This method is invoked on any server instance once per render.
      This is not invoked if this instance is NET_SIM_TYPE::nstSTANDALONE or NET_SIM_TYPE::nstCLIENT.
      
      This method is invoked from GLView::onServerSideUpdateWorld() immediately
      after the new positions and orientations have been updated by the physics
      engine, but before this new data has been transmitted to any clients (or
      synchronized with each WOODE's underlying NetWO).
   */
   virtual void onServerSideUpdateWO();

   /**
      This method is invoked on any client instance once per render.
      This is not invoked if this instance is NET_SIM_TYPE::nstSTANDALONE or NET_SIM_TYPE::NET_SIM_TYPE::nstSERVER.

      This method is invoked from GLView::onServerSideUpdateWorld() immediately
      after the new positions and orientations have been updated by the physics
      engine, but before this new data has been transmitted to any clients.
   */
   virtual void onClientSideUpdateWO();

   /**
      Called once per main engine iteration by GLView::updateWorld on
      each WO. This method should be used to update any state that may
      be based on time or another variable that is not necessarily
      directly controlled by that WO.
      
      This method is invoked on all 3 NetSimulation types (NET_SIM_TYPE::NET_SIM_TYPE::nstSERVER,
      NET_SIM_TYPE::nstSTANDALONE, or NET_SIM_TYPE::nstCLIENT).
   */
   virtual void onUpdateWO();

   /**
      Sets the current animation to the Animation which is passed in
   */
   void setCurrentAnimation( Animation* newAnimation ) { this->currentAnimation = newAnimation; }

   /**
      Gets the current animation that is set for this worldObject
   */
   Animation* getCurrentAnimation() { return currentAnimation; }

   /**
      \returns the total faces of this object and all it's children
   */
   size_t getFaceCountIncludingChildren();

   /**
      Invoked after GLView::loadMap() on all WOs. This method ensures that each WOODE
      has a valid model. If a user does not want a Model for a specific WOODE, then he
      can instantiate that WOODE's model to be an MGLNullModel.
   */
   virtual void inspectForNullModel();

protected:
   WO();
   virtual void onCreate();
   virtual void onCreate( const std::string& modelFileName, Vector scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );
   void initInstanceData(); ///< Called by the numerous constructors to ensure all protected member variables are always initialized in one place.

   virtual void toFileConstructorParams( std::ostream& sout );
   virtual void toFileWOState( std::ostream& sout );
   static ThisClassType* fromFileConstructorParams( std::istream& sin );
   virtual bool fromFileWOState( std::istream& sin );
   bool fromFileWOStateHelper( std::istream& sin, std::string& lhs, std::string& rhs );

   /// Recursive helper function for WO::getCountOfAllDecendants()
   size_t getCountOfAllDecendantsRec( WO* wo );

   bool IsLockedWRTparent = false;
   WOGJoint* joint = nullptr; ///< Joint connect to this WO's parentWO; this joint is used to 'lock' this WO WRT its parent; NULL iff not attached.

   unsigned int id = 0;  ///< globally unique ID for this WO, mainly used by the renderSelection for user selection purposes.
   std::string label = "";///< Provided as a user convience; he can set this to any std::string desired; ie, "Chuck's Red ball", "Ted's Car", or "Boat 12".
   Model* model = nullptr;     ///< Graphical Model associated with this WO. Currently this can be loaded from a file (3ds, wrl) or procedurally generated
   WO* parentWorldObject = nullptr; ///< A pointer to this WO's parent; if there is no parent, it is NULL.
   WorldObjectChildContainer children; ///< A container which stores pointers to all of this WO's child WorldObjects.

   static const int VECPREC = 5; ///< number of digits after the decimal point to serialize

   #ifdef AFTR_CONFIG_USE_TNL
      /**
         A pointer to this WO's corresponding NetWO. This is used by \see send_C2S_GuranteedOrderedData and
         \see send_S2C_GuranteedOrderedData to make immediate RPC calls outside of the typical network ghosting
         mechanism. Two examples of the typical unordered, non-guranteed ghosting include the
         \see packNetState and \see unPackNetState.
         If this simulation instance is a SERVER, netWO gets set at the end of GLView::init() AFTER the call to LoadMap().
         Therefore, the user CANNOT and MUST NOT ever directly set netWO. The user can, however, use netWO after GLView::init() has completed. If the user
         chooses to use the netWO for a specific task, the user should understand the networking subsystem before doing so as to
         avoid corrupting the Network System's state.
         If the simulation instance is a CLIENT, netWO is set up and properly registered ONLY after \see WO::onRegisteredWithServer() invokation begins.
         This invokation will occur within a few seconds of initially connecting to the server; the delay is a function of the number of WOs that
         must be sync'd between the server and this client.
         netWO is created, destroyed, and managed (owned) by NetSimulation.
      */
      NetWO* netWO;

      /**
         This pointer is automatically managed by the NetSimulation. The user never needs to touch
         this object. This is a pointer to per WO instance specific information regarding clustering 
         information. For example, if this object is a skybox, the Cluster server (in NetSimulation)
         will use this object to mark that this WO shall never be transferred between servers.

         If server clustering is never used, or this instance is a client, this object will remain
         NULL for the duration of the simulation's time span.
      */
      NetClusterWOCloneManager* netClusterWOCloneManager;
   #endif

   /**
      The current selected animation for this world object.
      Each ghost world object has the opportunity to have an animation associated with it, but mainly the base 
      objects will have this set to anything but NULL.
   */
   Animation* currentAnimation = nullptr;

   /**
      This is a timer interal to this WO that gets incremented every engine
      'tick'. This gets updated inside of the WO::onPhysicsEngineTick()
      method.
      This timer is useful to have this WO* perform a task(s) on a periodic basis.
      For example, if this was a human, which had eye lids that needed to blink every
      2 seconds, the user could check if this timer >= 2000 then perform a blink and 
      reset the timer = 0. Otherwise, if the timer < 2000, the user knows 2 seconds
      has not yet elapsed so more engine ticks must first occur.
   */
   unsigned int cumTimeElapsed = 0;

};

} //namespace Aftr

