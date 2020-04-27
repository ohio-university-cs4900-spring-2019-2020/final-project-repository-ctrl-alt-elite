#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include "tnlGhostConnection.h"
#include <queue>

namespace Aftr
{
   class NetWO;

/**
   \class ConnClientGhost
   \author Scott Nykl

   The ConnClientGhost represents a connection on an interface between a server and client.
   
   RPCs invoked from ConnClientGhost are sent to exactly one destination. That means,
   the RPC is not "ghosted" to an instance on ALL clients. If the rpc is Server to Client (S2C)
   The data is sent only to that single client; no other clients "hear" that transmission.

   This is useful when a client or server wants to send data to exactly one destination, and not
   utilize the "ghosting" mechanism inside in the \see NetWO objects.

   \{
*/
class ConnClientGhost : public TNL::GhostConnection
{
   typedef TNL::GhostConnection Parent;
public:

   /**
      TNL_DECLARE_NETCONNECTION is used to declare that ConnClientGhost is a valid connection class to the
      TNL network system.
   */
   TNL_DECLARE_NETCONNECTION( ConnClientGhost );


   /**
      Created in NICAftrBase::handleInfoPacket(...) when a client receives a ping
      response from a server. This will connect from a client to a server; hence, when a
      connection is created on a client, a corresponding connection is created on the server.      
   */
   ConnClientGhost();

   /**

   */
   virtual ~ConnClientGhost();

   /**
      onConnectTerminated is called when the connection request to the server
      is unable to complete due to server rejection, timeout or other error.
      When a ConnClientGhost connect request to a server is terminated, the client's network interface
      is notified so it can begin searching for another server to connect to.
   */
   virtual void onConnectTerminated( TNL::NetConnection::TerminationReason reason, const char* rejectionString );

   /**
      onConnectionTerminated is called when an established connection is terminated, whether
      from the local or remote hosts explicitly disconnecting, timing out or network error.
      When a ConnClientGhost to a server is disconnected, the client's network interface
      is notified so it can begin searching for another server to connect to.
   */
   virtual void onConnectionTerminated( TNL::NetConnection::TerminationReason reason, const char* string );

   /**
      onConnectionEstablished is called on both ends of a connection when the connection is established.  
      On the server this will create a player for this client, and set it as the client's
      scope object.  On both sides this will set the proper ghosting behavior for the connection
      (ie server to client).
   */
   virtual void onConnectionEstablished(); 

   /**
      isDataToTransmit is called each time the connection is ready to send a packet.  If
      the NetConnection subclass has data to send it should return true.  In the case of a simulation,
      this should always return true.
   */
   virtual bool isDataToTransmit();

   /**
      \return The WOID of the WO* this actor is currently controlling.
   */
   virtual TNL::U32 getClientActorWOID() { return this->clientActorWOID; }

   /**
      \return A pointer to the queue of current NetWOs awaiting a valid woID sent back from the server
      to this client so the NetWO can be fully registered and become functional.
   */
   virtual std::queue< NetWO* >* getWaitingForWOIDReceptionQueue() { return &this->waitingForWOIDReceptionQueue; }

   /**
      Sets/resets this clientActorWOID to zero; that is, it associates with connection with
      controlling a WO with an ID of ZERO, which means 
   */
   virtual void resetClientActorWOID() { this->clientActorWOID = (TNL::U32) 0; }

   /**
      Called by server at the end of ConnClientGhost::onConnectionEstablished().
      The server sends the client a woID. This woID corresponds to the woID of the WO*
      which the client shall control throughout the simulation. That is, after the client
      completes invokation of this RPC, the client's GLView->actor shall be set to the
      WO* with the corresponding woID.

      Invoked by client which performs the following:
      -# Syncs client's copy of actor's WOID with the server
      -# Invokes GLView->invokeGLViewClientOnClientConnect(...) on client which
         sets the client's GLView->actor to the WO* with the corresponding woID
   */
   TNL_DECLARE_RPC( rpcS2C_setClientActorWOID, (TNL::U32 woID) );


   /**
      This RPC is invoked on server side in response to NetWO::rpcC2S_requestCorrespondingWOID.
      This is used to send the corresponding woID to ONLY the netWO instance on ONE client; not
      the netWO instance on ALL clients. This is the reason the "second-half" of 
      rpcC2S_requestCorrespondingWOID (this RPC) is implemented in \see ClientGhostConnect instead of
      \see NetWO.

      Before the client initially calls \see rpcC2S_requestCorrespondingWOID, the client pushes its
      newly created NetWO into a queue (performed in NetWO::onGhostAdd). A request for a corresponding
      woID for that new NetWO is sent (\see rpcC2S_requestCorrespondingWOID). The NetWO then simply waits
      in the queue until the server invokes this RPC on the client-side.

      Because both the rpcC2S and rpcS2C RPCs of "_requestCorrespondingWOID" are guranteed-ordered,
      the first NetWO the client places into the queue will correspond to the first woID the server
      returns to the client (the woID param in the RPC). Hence, the client can queue
      all new NetWOs and the server will return woIDs in the proper order to always sync the correct
      woID with the correct NetWO on client-side.      
   */
   TNL_DECLARE_RPC( rpcS2C_requestCorrespondingWOID, (TNL::U32 woID ) );


   /**
      This RPC is invoked in response to rpcC2S_requestForceNetSyncDataForNetWO(...). The server
      takes the current orientation and position of the WO* corresponding to woID and packages
      it into a TNL::Vector< TNL::F32 >.
      \param woID is the woID corresponding to the NetWO/WO on the client that will apply this new
      position/orientation information.
   */
   TNL_DECLARE_RPC( rpcS2C_requestForceNetSyncDataForNetWO, ( TNL::U32 woID, TNL::Vector< TNL::F32 > data ) );

   /**
      This method should only be invoked very INfrequently; for example, once during client-side
      initializiation of each NetWO (currently, this is performed on each NetWO inside of
      NetSimulation::registerNewNetWOwithNetSimulation(...).

      This method requests that the server force send a guranteed update of the latest
      position/orientation data for this NetWO. This includes a fresh copy of the position,
      and orientation only. This will be sent out immediately after receieving and 
      interpreting this RPC.
   */
   TNL_DECLARE_RPC( rpcC2S_requestForceNetSyncDataForNetWO, ( TNL::U32 woID ) );

   /**
      This RPC sends data from the server to exactly one WO instance on exactly ONE client - no Ghosting occurs.
      This RPC will typically be invoked from within WO::send_S2C_NonGhostedGuranteedOrderedData(...) since this
      method has a ConnClientGhost* corresponding to the IP:Port of the client which originated the first
      C2S_NonGhostedGuranteedOrderedData() invokation.

      Corresponding C2S is NetWO::rpcC2S_sendNonGhostedGuranteedOrderedData(...).
   */
   TNL_DECLARE_RPC( rpcS2C_sendNonGhostedGuranteedOrderedData, ( TNL::U32 woID, TNL::Vector< TNL::S32 > intVec, TNL::Vector< TNL::F32 > floatVec ) );

protected:

   /**
      Used only client side. A NetWO requests a woID from NetWO::rpcC2S_requestCorrespondingWOID().
      Immedeitaly prior to this invocation (inside of NetWO::onGhostAdd()), the NetWO* is placed in this
      queue.
      That NetWO is temporarily stored in this queue until the guranteed-ordered RPC comes back
      from the server. At that point, the NetWO is removed from the queue inside of
      ConnClientGhost::rpcS2C_requestCorrespondingWOID( woID ). Then the NetWO is assigned its
      proper woID.
   */
   std::queue< NetWO* > waitingForWOIDReceptionQueue;

   TNL::SafePtr<NetWO> clientScopeObject; ///< The player object associated with this connection.

   TNL::U32 clientActorWOID; ///< The WOID corresponding to the WO this client will control from his terminal
   
};

} //namespace Aftr

/** \} */

#endif //AFTR_CONFIG_USE_TNL
