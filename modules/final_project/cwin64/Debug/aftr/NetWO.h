#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include "tnlNetObject.h"
#include <iostream>
#include <map>

namespace Aftr
{

/**
   \class NetWO
   \author Scott Nykl 
   \brief NetWO's are used to efficiently send WO state data from a server to all
      clients that are interested in that particular NetWO. Only clients interested
      in obtaining updated information about that WO shall receive the corresponding
      NetWO.
      A 1-to-1 mapping exists between exactly one NetWO and one WO.
      Keep in mind that hierarchical objects such as the WOHuman is composed
      of many WOs, and therefore, has one NetWO for each WO within the WOHuman.

   \{
*/

class NetSimulation;
class WO;

class NetWO : public TNL::NetObject
{
   typedef TNL::NetObject Parent;

public:
   TNL_DECLARE_CLASS( NetWO );
   
   NetWO();
   virtual ~NetWO();

   /// Notifies the networking subsystem that this NetWO's corresponding WO's position has been
   /// changed. This is performed on the server-side from within NetWO::packUpdate().
   /// The typical scenario occurs within GLView::onServerSideUpdateWorld().
   /// -# The server's phsyics engine moves a WO (via pe->updateWorld() )
   /// -# The graphical location of the WOs are updated (via GLView::syncGFXfromPhyx())
   /// -# The Corresponding NetWO of this WO is updated (via netSim->syncNetWOfromGFX())
   /// -# If a change in position has occurred between the old NetWO position and the current
   ///    WO position, then this method is invoked.
   /// -# If invoked, this flag implies a new position must be transmitted from the server to all
   ///    clients that are currently interested in obtaining that WO's new position.
   void setMaskPositionChangedFlag();

   /// Notifies the networking subsystem that this NetWO's corresponding WO's orientation has been
   /// changed. This is performed on the server-side from within NetWO::packUpdate().
   /// The typical scenario occurs within GLView::onServerSideUpdateWorld().
   /// -# The server's phsyics engine moves a WO (via pe->updateWorld() )
   /// -# The graphical location of the WOs are updated (via GLView::syncGFXfromPhyx())
   /// -# The Corresponding NetWO of this WO is updated (via netSim->syncNetWOfromGFX())
   /// -# If a change in orientation has occurred between the old NetWO orientation and the current
   ///    WO orientation, then this method is invoked.
   /// -# If invoked, this flag implies a new orientation must be transmitted from the server to all
   ///    clients that are currently interested in obtaining that WO's new orientation.
   void setMaskOrientationChangedFlag();

   void setMaskNetStateUserDefinedDataChangedFlag();

   /// packUpdate writes the Player's ghost update from the server to the client.
   /// This function takes advantage of the fact that the InitialMask is only ever set
   /// for the first update of the object to send once-only state to the client.
   virtual TNL::U32 packUpdate( TNL::GhostConnection* connection, TNL::U32 updateMask, TNL::BitStream *stream );

   /// unpackUpdate reads the data the server wrote in packUpdate from the packet.
   virtual void unpackUpdate( TNL::GhostConnection *connection, TNL::BitStream *stream );

   /// serverSetPosition is called on the server when it receives notice from a client
   /// to change the position of the player it controls.  serverSetPosition will call
   /// setMaskBits(PositionMask) to notify the network system that this object has
   /// changed state.
   //void serverSetPosition( Position startPos, Position endPos, TNL::F32 t, TNL::F32 tDelta );  

   /// onGhostAvailable is called on the server when it knows that this Player has been
   /// constructed on the specified client as a result of being "in scope".  In TNLTest
   /// this method call is used to test the per-ghost targeted RPC functionality of
   /// NetObject subclasses by calling rpcPlayerIsInScope on the Player ghost on
   /// the specified connection.
   virtual void onGhostAvailable( TNL::GhostConnection* theConnection );

   /// onGhostAdd is called for every NetObject on the client after the ghost has
   /// been constructed and its initial unpackUpdate is called.  A return value of
   /// false from this function would indicate than an error had occured, notifying the
   /// network system that the connection should be terminated.
   virtual bool onGhostAdd( TNL::GhostConnection* theConnection );

   /// onGhostRemove is called on the client side before the destructor when ghost has gone out
   /// of scope and is about to be deleted from the client. 
   virtual void onGhostRemove();

   /// This method is invoked only server-side
   /// performScopeQuery is called to determine which objects are "in scope" (interesting)
   /// for the client that controls this NetWO instance.  Typically, all WOs within a certain
   /// proximity to this WO shall be "scoped" (interesting); therefore, the client will receive all data
   /// the server generates pertaining to exactly those WOs.
   virtual void performScopeQuery( TNL::GhostConnection* connection );


   /// rpcPlayerWillMove is used in TNLTest to demonstrate ghost->parent NetObject RPCs.
   //TNL_DECLARE_RPC( rpcPlayerWillMove, ( TNL::StringPtr testString ) );

   /// rpcPlayerDidMove is used in TNLTest to demostrate a broadcast RPC from the server
   /// to all of the ghosts on clients scoping this object.  It also demonstrates the
   /// usage of the Float<> template argument, in this case using 6 bits for each X and
   /// Y position.  Float arguments to RPCs are between 0 and 1.
   //TNL_DECLARE_RPC( rpcPlayerDidMove, ( TNL::Float<6> x, TNL::Float<6> y ) );

   /// rpcPlayerIsInScope is the RPC method called by onGhostAvailable to demonstrate
   /// targeted NetObject RPCs.  onGhostAvailable uses the TNL_RPC_CONSTRUCT_NETEVENT
   /// macro to construct a NetEvent from the RPC invocation and then posts it only
   /// to the client for which the object just came into scope.
   //TNL_DECLARE_RPC( rpcPlayerIsInScope, ( TNL::Float<6> x, TNL::Float<6> y ) );

   /**
      Manually set the 9 floats of the upper left corner of this NetWO's display
      matrix. This is called by ConnClientGhost::rpcS2C_requestForceNetSyncDataOnNetWO(...)
      to initially force sync this NetWO's orientation to that of the server and then update
      the graphical model on this client associated with this NetWO.

      \param float* An array of 9 floats that shall be copied into this NetWO's
      display matrix.
   */
   void setNetWOMatrix( float* orientationMatrix );

   /**
      Manually set the 9position of this NetWO.
      This is called by ConnClientGhost::rpcS2C_requestForceNetSyncDataOnNetWO(...)
      to initially force sync this NetWO's position to that of the server and then update
      the graphical model on this client associated with this NetWO.

      \param float x,y,z The position in 3-space to set this NetWO.
   */
   void setNetWOPosition( float x, float y, float z );

   TNL::U32 getID();
   void forceNetSync();
   bool forcedNetSyncPending();
   void forcedNetSyncComplete();
   void setWOID( unsigned int woID );
   void syncNetWOPositionFromWO();
   void syncNetWOPositionToWO();
   void syncNetWOMatrixFromWO();
   void syncNetWOMatrixToWO();
   void syncNetStateUserDefinedDataFromWO();

   NetSimulation* getSimulation() { return this->sim; }
   void setSimulation( NetSimulation* theSim ) { this->sim = theSim; }
   void setWOptr( WO* wo ) { this->woPtr = wo; }
   WO* getWOptr() { return this->woPtr; }

   //Two example RPCs that show syntax... Not used by NetWO
   TNL_DECLARE_RPC( rpcPlayerDidMove, (TNL::F32 x, TNL::F32 y, TNL::F32 z) );
   TNL_DECLARE_RPC( rpcS2CPlayerIsInScope, (TNL::U32 id) );

   void onKeyDown( const SDL_KeyboardEvent& key );
   TNL_DECLARE_RPC( rpcC2S_onKeyDown, (TNL::U8 type, 
                                       TNL::U8 state,
                                       TNL::U8 scancode,
                                       TNL::U16 sym,
                                       TNL::U8 mod,
                                       TNL::U16 unicode,
                                       TNL::U32 woID) );
   
   void onKeyUp( const SDL_KeyboardEvent& key );
   TNL_DECLARE_RPC( rpcC2S_onKeyUp, (TNL::U8 type, 
                                     TNL::U8 state,
                                     TNL::U8 scancode,
                                     TNL::U16 sym,
                                     TNL::U8 mod,
                                     TNL::U16 unicode,
                                     TNL::U32 woID) );

   //int/float rpc
   TNL_DECLARE_RPC( rpcC2S_sendGuranteedOrderedData, ( TNL::Vector< TNL::S32 > intVec, TNL::Vector< TNL::F32 > floatVec ) );
   TNL_DECLARE_RPC( rpcS2C_sendGuranteedOrderedData, ( TNL::Vector< TNL::S32 > intVec, TNL::Vector< TNL::F32 > floatVec ) );
   //int/string rpc
   TNL_DECLARE_RPC( rpcC2S_sendGuranteedOrderedDataString, ( TNL::Vector< TNL::S32 > intVec, TNL::Vector< TNL::StringPtr > stringVec ) );
   TNL_DECLARE_RPC( rpcS2C_sendGuranteedOrderedDataString, ( TNL::Vector< TNL::S32 > intVec, TNL::Vector< TNL::StringPtr > stringVec ) );

   
   /**
      When NetWO::onGhostAdd() is invoked, it means this client (client-side) has just
      received, constructed, and unpacked a new NetWO. However, the client does not know
      which WO should be associated w/ this NetWO. This RPC asks the server which WOID
      should be associated w/ this NetWO. The corresponding reply from the server occurs in
      ConnClientGhost::rpcS2C_requestCorrespondingWOID(...) because the server sends
      the woID to ONLY this client, and rpcs in ConnClientGhost are only to ONE endpoint (client).

      If the corresponding reply would have been implemented inside of NetWO, then that woID
      would be 'ghosted' to this NetWO on ALL clients - That would be BAD.
   */
   TNL_DECLARE_RPC( rpcC2S_requestCorrespondingWOID, ( ) );

   /**
      Sends nonghosted data from a client to a server. This actual method (sending from Client to Server) is the same
      as a typical rpc that transmits ghosted data; however, at the server end, the server realizes this is a nonghosted
      invokation and responds appropriately.

      The corresponding S2C is ConnClientGhost::rpcS2C_sendNonGhostedGuranteedOrderedData(...).
   */
   TNL_DECLARE_RPC( rpcC2S_sendNonGhostedGuranteedOrderedData, ( TNL::Vector< TNL::S32 > intVec, TNL::Vector< TNL::F32 > floatVec ) );

protected:

   enum States
   {
      maskOneTimeInitialization = BIT(0),
      maskPositionChanged = BIT(1),
      maskOrientationChanged = BIT(2),
      maskNetStateUserDefinedDataChanged = BIT(3),
   };

   NetSimulation* sim;
   WO* woPtr;
                        
   bool forceNetSyncRequested;

   /**
      WorldObject ID this NetWO 'ghosts' across the server.

      Used client-side to determine if the server has assigned a WOID
      to this NetWO yet. This is ZERO immediately after construction
      and remains ZERO until the rpc made inside of NetWO::onGhostAdd(...)
      returns a valid identifing WOID for this NetWO to be associated with.
   */
   TNL::U32 woID;

   TNL::F32 xpos;    ///Distance along global +X-axis in the world
   TNL::F32 ypos;    ///Distance along global +Y-axis in the world
   TNL::F32 zpos;    ///Distance along global +Z-axis in the world

   TNL::F32 matrix[9];  ///Orientation Matrix (Display Matrix)

   TNL::Vector< TNL::F32 > floatVec; ///Vector of floats used for syncing WO that require more data than simply a position and orientation
   TNL::Vector< TNL::S32 > intVec; ///Vector of ints used for syncing WO that require more data than simply a position and orientation


};

} //namespace Aftr

/** \} */

#endif //AFTR_CONFIG_USE_TNL
