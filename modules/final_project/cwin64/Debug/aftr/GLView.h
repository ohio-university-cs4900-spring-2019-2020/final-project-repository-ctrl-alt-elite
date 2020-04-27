//-----------------------------------------------------------------------------
// Description: An OpenGL form control capable of drawing a World onto itself
// Author: Scott Nykl
//-----------------------------------------------------------------------------
#pragma once

#include "AftrConfig.h"
#include "AftrOpenGLIncludes.h"
#include "AftrGlobals.h"
#include "HandlerMouseState.h"
#include "SelectionQueryResult.h"
#include "Vector.h"
#include "PhysicsEngine.h"
#include <vector>

#ifdef AFTR_CONFIG_USE_TNL
   #include "tnlVector.h"
   namespace TNL { class EventConnection; }
#endif

namespace Aftr
{
   class Camera;
   class WorldContainer;
   class PhysicsEngine;
   class WO;
   class GUI;
   class UI;
   class NetMessengerServer;
   class ManagerTexture;
   class NetSimulation;
   class ConnClientGhost;
   class AftrFrameBufferObject;
   class IndexedGeometryQuad;
   class AftrGLRendererBase;
   class ModelMesh;
   class SelectionQueryResult;

   enum CAM_CHASE_TYPE;


/**
   \class GLView
   \author Scott Nykl 
   \brief The abstract GLView. This class is the top-most manager of the module. This should be inherited from and the child
   shall be named GLViewModuleName. For example, the TideIsland module GLView is called GLViewTideIsland.

   Important: Since this is an abstract class with no constructor, all child classes are REQUIRED to invoke the
   GLView::init() method.

   For example:

   GLViewNewModule* GLViewNewModule::New( const std::vector< std::string >& args )
   {
      GLViewNewModule* glv = new GLViewNewModule( args );
      glv->init( Aftr::GRAVITY, Vector( 0, 0, -1.0f ), "Aftr.conf", 2 );
      glv->onCreate();
      return glv;
   }

   GLViewMyModule::GLViewMyModule( const std::vector< std::string >& args )
   {
      //Initialize member variables here...
   }

   This class contains ALL aspects of a module. Several relevant aspects include:
      -# worldLst - The std::vector of WO*. All WO in your module shall be new'd in loadMap() and pushed into worldLst inside of loadMap().
      -# actorLst - All WO* that desire camera tracking and keyboard callbacks shall be pushed into actorLst.
      -# actor - The WO* pointing to the current actor; only one WO can be the actor at any given time.
      -# cam - The camera used within this module.
      -# lastSelectedWorldObject - When a user crtl-clicks a WO in your module, this WO* points to that WO.
      -# pe - This module's physics engine. It is used within GLView::updateWorld each main loop iteration.

    \{
*/

class GLView 
{

public:
   
   //Constructor is protected and only invoked by descendants of the GLView class

   /**
      Deletes the:
         -# GUI
         -# Camera
         -# Physics Engine
         -# All WO* in the worldLst
         -# worldLst
         -# actorLst
         -# Shuts down all static Managers

      This destroys ALL aspects that define a module. If main.cpp deletes the GLView, all memory
      ever used within GLView is released. This is actually what the 'RESET' button actually does
      it deletes the GLView and new's it again (along with reinitializing SDL).
   */
   virtual ~GLView();

   /**
      Returns a pointer to the GLView's UI instance. nullptr if not instantiated.
   */
   UI* getUI();

   /**
      By default, when an engine instance starts, port 12683 opens (TCP and 
      UDP) to listen for NetMessages. This is a method for interprocess 
      communications or cross-network information exchange. The NetMessage
      server is an asynchronous listener that can serve many simultaneous
      clients. For example, a Java GUI can send information to the engine to
      visualize something.
   */   
   NetMessengerServer* getNetMessengerServer();

   /**
      This method is called within the main loop inside GLView::startWorldSimulationLoop(). After each frame,
      time is accounted for, updating the framerate over the last second.
   */
   virtual void setCurrentFrameRate( int frameRateOverLastOneSecond ) { this->currFrameRate = frameRateOverLastOneSecond; }

   /**
      Returns the number of times this module's world was rendered to the screen during the last ONE second.
      \return the number of times this module's world was rendered to the screen during the last ONE second.
   */
   int getCurrentFrameRate() { return this->currFrameRate; }

   /**
      Returns The Width of the GLView in pixels
      \return The Width of the GLView in pixels
   */
   int getWindowWidth();

   /**
      Returns The Height of the GLView in pixels
      \return The Height of the GLView in pixels
   */
   int getWindowHeight();

   /**
      Sets the actor the camera will watch. Also determines which WO* any SDL_Event callbacks, such as keypresses,
      will be sent to. For example, if the human is the current actor, then the UP ARROW will be processed
      by the human. This will probably make him do something like walk forward.

      \param inActor The WO* that shall become the current actor
   */
   virtual void setActor( WO* inActor );

   /**
      Iterates to the next actor in actorLst.
   */
   virtual void trackNextActor();

   /**
      Returns A pointer to the current actor.
      \return a pointer to the current actor.
   */
   WO* getActor();

   /**
      \returns a pointer to the GLView's actorLst. Note, the actorLst is not populated until after
      GLView::loadMap() returns.
   */
   WorldContainer* getActorLst() { return this->actorLst; }

   /**
      \returns a pointer to the GLView's netLst. Note, the netLst is not populated until after
      GLView::loadMap() returns.
   */
   WorldContainer* getNetLst() { return this->netLst; }

   /**
      Returns a pointer to the GLView's worldLst.
      \return A pointer to the GLView's worldLst.
   */
   WorldContainer* getWorldContainer();

   /**
      Sets the number of ODE Physics Steps taken between each time the worldLst is rendered to the screen.
      \see numPhysicsStepsPerRender
      \param numPhysSteps the number of ODE Physics Steps taken between each time the worldLst is rendered to the screen.
   */
   void setNumPhysicsStepsPerRender( int numPhySteps ) { this->numPhysicsStepsPerRender = numPhySteps; }
   
   /**
      Returns the number of ODE Physics Steps taken between each time the worldLst is rendered to the screen.
      \return The number of ODE Physics Steps taken between each time the worldLst is rendered to the screen.
   */
   int getNumPhysicsStepsPerRender() { return this->numPhysicsStepsPerRender; }

   CAM_CHASE_TYPE getActorChaseType() { return this->ActorChaseType; }
   void setActorChaseType( CAM_CHASE_TYPE chaseType );

   /**
      Returns a pointer to this GLView's physics engine.
      \return pe A pointer to this GLView's physics engine.
   */
   PhysicsEngine* getPhysicsEngine();

   /**
      Returns a pointer to the camera used within this module.
      \return A pointer to the camera used within this module.
   */
   Camera* getCamera();

   /**
      Returns a pointer to a Camera pointer. This may be helpful for objects
      that do not necessiarly want to store a GLView* but need a pointer to
      the current Camera stored in the GLView. Each time a camera is recreated,
      GLView->getCamera() may point to a new memory location; hence storing a
      local pointer equal to GLView->getCamera() is unsafe.

      For example, many MGLs only need access to data within the Camera. Since
      the camera is deleted and new'd each time a new view style changes, storing
      the GLView's original Camera* will not work after recreating a camera.

      If the MGL stores a "Camera** myCam" and sets that equal to "GLView->getCameraPtrPtr()",
      then invoking (*myCam)->getPosition() will return the camera's current position.
      This method safely stores a pointer to the GLView's current Camera.

      Another safe method is to store a "GLView* glView" and simply invoke
      glView->getCamera() to get a pointer to the GLView's current camera.

      If you are unsure about the above, simply store a GLView* in your own object and
      call GLView->getCamera() to get a pointer to the current camera.

      Do not store the pointer returned by GLView->getCamera() since it will be invalid
      once the camera is deleted and new'd due to camera type change.
   */
   Camera** getCameraPtrPtr();

   /**
      This method is where the user constructs his entire virtual world.
      The user performs the following here:
         -# new the worldLst 
         -# new the actorLst
         -# new the netLst
         -# new a WO
         -# set the WO's attributes such as position, mass, surface properties, parent WO
         -# push WO into worldLst
         -# if the WO is an actor, push into actorLst
         -# Repeat above 4 steps for ALL WO the user will ever use during runtime of this module.
   */
   virtual void loadMap() = 0;

   virtual void loadMapFromFile( const std::string& fileName = "../save/default.world" );
   virtual void processFromFileStatement( std::istream& sin, const std::string& lhs, const std::string& rhs );
   virtual void loadMapToFile( const std::string& fileName = "../save/default.world" );

   /**
      Begins the simulation corresponding to this module's GLView child.
      \return The return value has 2 different meanings:
       -# If  0 is returned, a request to exit program has been issued (Exit).
       -# If -1 is returned, a request to delete and re-instantiate the module has been issued (Reset).
   */
   virtual int startWorldSimulationLoop();

   /**
      This method is invoked by main.cpp once every main loop iteration. This method
      takes zero or more ODE physics steps, renders the world, and also invokes the
      onPhysicsEngineTick callback on all WO* in the worldLst.

      The number of ODE physics steps taken is equal to the current ratio. That is, if the ratio
      is 15, then 15 ODE physics steps are taken. Note that this means every WO's
      ODEupdateForcesAndJoints() and ODEupdateToNewPositionOrientation() are invoked 15 times as well.

      The WO::onPhysicsEngineTick shall be invoked ratio times iff ratio > 0; else if 
      ratio == 0, WO::onPhysicsEngineTick shall be invoked exactly once. This invocation rule exists
      to ensure that cumElapsedTime is still updated even if the physics engine is paused.

      The scene shall be rendered once, after all the ODE physics steps/onPhysicsEngineTick are taken.
   */ 
   virtual void updateWorld();

   /**
      Fires when the screen is reshaped used to scale the world to fit the screen
      height and width parameters are the screen size. This also invokes WOGUI widget
      onResizeWindow() callbacks.
   */
   virtual void onResizeWindow( GLsizei width, GLsizei height );

   virtual void resetMouseState();

   #ifdef AFTR_CONFIG_USE_TNL //TNL Specific functions
      /**
         Called on client-side when a connection is established with a new server.
         This is a NON-clustered method.
      */
      virtual void onClientConnectOnClientSide( ConnClientGhost* client );
      
      /**
         Called on server-side when a connection is established with a new client.
         This is a NON-clustered method.
      */
      virtual void onClientConnectOnServerSide( WO* newActor, ConnClientGhost* client = nullptr );

      /**
         Called on client-side when a connection is closed between this client and a server.
         This is a NON-clustered method.
      */
      virtual void onClientDisconnectOnClientSide( ConnClientGhost* client );

      /**
         When a client leaves the simulation, this method is invoked server-side. If a client exits
         gracefully, ie, quits properly instead of abruptly crashing w/o signal server of exit, this method
         is invoked almost instantly after the client quits.
         If the client exits abruptly then this method won't get called for that client until the timeout
         has occurred (around a minute or so)
         
         \param reclaimedActors contains WO*s pointing at the WOs that were controlled by that client or
         were available for reclamation when that client exited. Typically, this will contain a single WO
         corresponding to the WO in the NetSimulation::occupiedNetLst controlled by the client.

         \param client A pointer to the now defunct connection. The server can use this to print the IP address
         of the exiting client or query \see ConnClientGhost specific information. HOWEVER, immediately after
         leaving this method, the ConnClientGhost* client will be automatically deleted. Do not store the
         client internally or try to reference it after execution leaves this method.
      */
      virtual void onClientDisconnectOnServerSide( std::vector< WO* >& reclaimedActors, ConnClientGhost* client );

      /**
         Invoked when a Guranteed Ordered Data (GOD) RPC Message arrives
      */
      virtual void onReceivedRPCGOD( TNL::EventConnection* conn, TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      
      /** Returns a pointer to this GLView's NetSimulation */
      NetSimulation* getNetSim() { return this->netSim; }
   #endif

   bool isServer();///<returns true if this is instance a TNL server, false otherwise
   bool isClient();///<returns true if this instance is a TNL client, false otherwise
   bool isStandAlone();///<returns true if this instance is a stand alone (true if TNL is not used)
                       ///< (also true if TNL is used, but set to stand alone), false otherwise

   /** Fired when a mouse button is pressed */
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   /** Fired when a mouse button is released */
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   /** Fired when a mouse scroll wheel is scrolled (either vertically or horizontally */
   virtual void onMouseWheelScroll( const SDL_MouseWheelEvent& e );
   /** Fired when a mouse button is moved */
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   /** Fired when a key is pressed */
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   /** Fired when a key is released */
   virtual void onKeyUp( const SDL_KeyboardEvent& key );
   /** Fired when motion of a Joystick Axis is encountered */
   virtual void onJoyAxisMotion( const SDL_JoyAxisEvent& joy );
   virtual void onJoyBallMotion( const SDL_JoyBallEvent& joy );
   virtual void onJoyHatMotion( const SDL_JoyHatEvent& joy );
   virtual void onJoyButtonDown( const SDL_JoyButtonEvent& joy );
   virtual void onJoyButtonUp( const SDL_JoyButtonEvent& joy );
   virtual void onJoyDeviceAdded( const SDL_JoyDeviceEvent& joy );
   virtual void onJoyDeviceRemoved( const SDL_JoyDeviceEvent& joy );

   /**
      Fired when selection is enabled and a mouse button is pressed
   */
   virtual void onMouseDownSelection( unsigned int xPixelCoord, unsigned int yPixelCoord, Camera& cam );
   
   /** Turns OpenGL selection on */
   void enableOpenGLSelection() { openGLSelectionEnabled = true; }
   /** Turns OpenGL selection off */
   void disableOpenGLSelection() { openGLSelectionEnabled = false; }
   /** Returns true if OpenGL selection is enabled; false, otherwise. */
   bool getOpenGLSelectionEnabled() { return openGLSelectionEnabled; }
   
   /**
      Returns a pointer to the WO* selected via OpenGL selection; if nullptr, the last
      call to selection did not select a WO.
      \return WO* The last selected WO*. If nullptr, the last selection attempt did not find a WO*
   */
   WO* getLastSelectedWO();

   ///**
   //   Sets the lastSelectedWorldObject to the in passed WO*. This should only be called by a user
   //   that knows exactly why he wants to change this value. An example of when this is useful is to
   //   set the lastSlectedWorldObject to nullptr before performing some operation.
   //   \param WO* The WO* that the lastSelectedWorldObject shall be set equal to.
   //*/
   //void setLastSelectedWorldObject( WO* x );

   /**
      Returns a pointer to the global coordinate representing where the last successful
      selection occured; nullptr is returned if that last selection attempt failed.
   */
   Vector* getLastSelectedCoordinate();

   /**
      Returns a pointer to the ModelMesh selected on the previous selection call.
      If no ModelMesh was selected during that call, this will be set to nullptr
   */
   ModelMesh* getLastSelectedModelMesh();

   std::unique_ptr< SelectionQueryResult > selectionQuery = nullptr;

   HandlerMouseState* getHandlerMouseState() { return &this->mouseHandler; }

   /**
      This function triggers the engine to be fully shutdown after the current 
      iteration of GLView::startWorldSimulationLoop() completes.
      This method properly destroys all objects, shutdown all managers, 
      frees all corresponding memory, and exits normally.
   */
   virtual void shutdownEngine();
   
   /**
      This function triggers the engine to be fully reset after the current 
      iteration of GLView::startWorldSimulationLoop() completes.
      This method properly destroys all objects, shutdown all managers, 
      frees all corresponding memory, and then restarts the engine 
      reinitializing all components to their original state.
   */
   virtual void resetEngine();

   virtual AftrGLRendererBase* getGLRenderer();

protected:

   /**
      Constructor. Initializes all core parts of the engine. This is invoked by all
      modules when the child GLView decedent is instantiated.
   */
   GLView( const std::vector< std::string >& args );

   /**
      Contains all WO* that will ever be used during this module's runtime. This list shall get newed and populated
      inside of the child GLView::loadMap() method. Once loadMap() returns, the engine assumes this list is complete
      and that this list will not change for the rest of the module's runtime.
      
      If a WO* is new'ed but not pushed into this list, that WO* will
      be non-functional and may make your module unstable, if other WO* are associated with that WO*.

      The worldLst is owned and deleted by GLView. Therefore the user shall never need to call delete worldLst.
   */
   WorldContainer* worldLst = nullptr;

   /**
      Contains all WO* that can/will ever be tracked by the camera. There is only one actor at any given time. The 
      WO* actor points at the current actor. When an SDL_Event occurs, such as a user key-press, GLView will forward
      that SDL_Event to the actor's corresponding callback method. In this case when the event occurred, 
      actor->onKeyDown( SDL_Event& key ) would automatically be invoked.

      The actorLst is owned and deleted by GLView. Therefore the user shall never need to call delete actorLst.

      These are pointer into the worldLst.
   */
   WorldContainer* actorLst = nullptr; //pointers into worldLst

   /**
      Valid only when TNL is being used.
      Points to all WO* that shall be used as client controlled avatars throughout the simulation. This list shall get
      newed and populated inside of the child GLView::loadMap() method. Once loadMap() returns, the engine assumes this
      list is complete and that this list will not change for the rest of the module's runtime.

      These are pointer into the worldLst.
   */
   WorldContainer* netLst = nullptr;

   /**
      The camera used within the module. \see Camera
   */
   Camera* cam = nullptr;

   /**
      Defines how the camera follows the current actor.
      How the camera follows the current actor.
      \see CAM_CHASE_TYPE
   */
   CAM_CHASE_TYPE ActorChaseType = STANDARDLOOK;


   /**
      This points to the current actor in the running module. If this is nullptr, there is no actor. When an SDL_Event, such as
      a key press occurs, the actor->onKeyDown( SDL_Event...) shall be invoked. For example, if the Human is the current actor
      and the user presses the 'Up Arrow' button, then the WOHuman::onKeyDown( SDL_Event& key) shall be invoked, and key shall
      reference the 'SDL_UP'. Then, the human can start walking forward.

      This point is not the owner; this is a pointer into worldLst. It can be
      manipulated via setActor
   */
   WO* actor = nullptr;

   UI* ui = nullptr; ///< The Aftr Indexed-geometry based GUI, replacing the deprecated GUIChan

   /**
      Aftr IPC Mechanism to send / receive messages with other programs / processes
      over sockets.
   */
   NetMessengerServer* netMessengerServer = nullptr;

   //#if defined AFTR_CONFIG_USE_ODE || defined AFTR_CONFIG_USE_NV_PHYSX
      /**
         The ODE / NVIDIA PhysX physics engine used by this module. This gets populated 
         from all the WO* inside of the worldLst after loadMap()
         finishes execution. GLView::updateWorld makes use of the physics engine. The user should not have 
         to interact with the physics engine unless he explicitly has specific reason to do so.

         The PhysicsEngineODE is owned by this class.
      */
      PhysicsEngine* pe = nullptr;
   //#endif

   std::vector< std::string > args; ///< The command line arguments passed into this program.

   int currFrameRate = 0; ///< The number of times this module's world was rendered over the last one second.

   /**
      The number of ODE physics steps taken between each call to render the module's world.
      The default value is 15 physics steps per world render.
      ~1 physics step per render results in a very smooth "slow motion" behavior.
      ~15 physics step per render results in a "average world" behavior.
      ~50 physics step per render results in a very fast "jerky" behavior (on a Core 2 Duo w/ nVidia GeForce 8800)
      
      As physics steps grows beyond 15+ (based on hardware), too much CPU time is spent calculating physics steps
      and the frame rate drops. This results in the module becoming CPU BOUND.

      On the other hand, if the graphical capabilities are the bottleneck, a ratio of 1 will cause the module to become
      GRAPHICALLY BOUND.

      Hence, the GUI has the slider which allows the user to change the ratio during runtime.
   */
   int numPhysicsStepsPerRender = 0;

   /**
      This handler keeps track of the current state of the mouse associated
      with this handler. Multiple handlers can be associated with multiple mice
      by feeding the SDL Mouse events to a particular HandlerMouseState.
   */
   HandlerMouseState mouseHandler;

   #ifdef AFTR_CONFIG_USE_TNL
      NetSimulation* netSim; ///< NetSimulation owned by this GLView... This is the networking subsystem.
   #endif

   /**
      Called by GLView::init().
      This method sets the camera's look mode to 'FREELOOK' and ensure selection is initially turned off.
      This can be overloaded by the user to define other user input states; for example, if selection should be
      on by default, it can be done here.

      If the user would like to maintain existing functionality of this method while adding additional functionality,
      he can simply over load this method and invoke 'GLView::initUserControls();' as the first line. Subsequent lines
      can then add functionality.
   */
   virtual void initUserControls();

   /**
      Called by GLView::init()
      This method new's the Camera at the X,Y,Z and sets its phi and theta corresponding to in passed params.
   */
   virtual void initCamera( float xLoc = 15, float yLoc = 15, float zLoc = 10, float phi = 0, float theta = 0 );

   /**
    Called by GLView::init()
    This method initializes frame buffers and parameters for Stereoscopic vision. This method will use
    values specified in the module's conf file for specific parameters.
   */
   //virtual void initStereoVision();

   /**
      After all of the WO's are created (upon loadMap() returning) and all other managers / physics engines
      have been initialzed. This invokes all of the init callbacks inside each WO. This way WOs that reference
      other WO's that have not yet been created can successfully reference them inside of these callbacks.
      
      This is also useful for networked server / client modules. If this is a server, all the server-side init 
      callbacks are invoked. If this is a client-side instance, all client-side init callbacks are invoked.
   */
   virtual void invokeWOinitCallbacks();

   virtual void onServerSideUpdateWorld();
   virtual void onClientSideUpdateWorld();

   /**
      The main initialization method for GLView. This method is designed to be invoked immediately after new-ing
      the GLView subclass instance. See the GLView class documentation at the top for an exact example of how to do this.

      By requiring the user to invoke GLView::init() as the first line of his child GLView's init() method, the user
      can avoid the complexities of knowing how to call the listed methods below.

      Initializes the GLView class
         -# calls initUserControls
         -# calls initCamera
         -# calls initialization functions on all static Managers
         -# calls LoadMap
         -# calls initManagerTexture
         -# new's the Physics Engine based on type. 0 is NO Physics Engine. 1 is ODE. 2 is NVIDIA PhysX.
   */
   virtual void init( float gravityScalar = Aftr::GRAVITY, 
                      Vector gravityNormalizedVector = Vector(0,0,-1),
                      std::string confFileName = "Aftr.conf", 
                      const PHYSICS_ENGINE_TYPE& physicsEngineType = PHYSICS_ENGINE_TYPE::petODE );

   /**
      When an SDL_Event such as a mouse click occurs, main.cpp first gives the GUI
      a chance to claim this event as intended for the GUI. This is because the GUI
      is drawn on TOP of everything else; therefore, if a mouse click occurs on a point
      where a GUI Button lies, we assume the click was intended for the button, and not
      for a WO* behind that button. If the GUI does not deal with this event, main.cpp
      will then pass the event to the GLView's callback methods (ie, onMouseDown(...) ).

      If the GUI deals with the event, true is returned; false, otherwise.

      \return true if the GUI dealt with this event; false, otherwise.
   */
   virtual bool handleGUIEvent( SDL_Event new_event );

   /**
      This method processes all non-GUI input events that have occurred since the last main
      loop iteration. This method checks the type of input (mouse,keyboard,joystick,etc), 
      and invokes the properly GLView callback (such as GLView::onKeyDown(...)).

      If the event is a Window event (such as a resize), this method passes the window
      event to 'int handleWindowEvent( SDL_WindowEvent& sdlWindowEvent )' for specific
      window handling.

      This method has the following return messages:

       1 - continue normally (processed properly)
       0 - exit module (received exit request)
      -1 - reset module (received reset request)
   */
   virtual int handleEvent( SDL_Event& sdlEvent );

   virtual int handleWindowEvent( SDL_WindowEvent& sdlWindowEvent );

   virtual int handleSystemSpecificEventOSDependent( SDL_SysWMEvent& sysEvent );

   bool openGLSelectionEnabled = false; ///<true if selection is enabled; false, otherwise
   bool receivedShutdownSignal = false; ///<Polled once per iteration inside of GLView::startWorldSimulationLoop(); if true, engine will terminate
   bool receivedResetSignal = false; ///<Polled once per iteration inside of GLView::startWorldSimulationLoop(); if true, engine will reset

   /// OpenGL Renderer used to drawn the OpenGL scene and swap the buffer to screen.
   AftrGLRendererBase* glRenderer = nullptr;
};

/** \} */

} //namespace Aftr
