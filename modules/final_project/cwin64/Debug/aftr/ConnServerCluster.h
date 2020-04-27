#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include "tnlEventConnection.h"
#include "tnlRPC.h"
#include "tnlVector.h"

namespace Aftr
{

   class WO;

/**
   \class ConnServerCluster
   \author Scott Nykl

      In the server cluster, each server node has a DOUBLE mesh topology to all neighbors.
      That is, if there are N server nodes, each node has exactly 2*(N-1) connections.
      This is because each server has a connection that was initiated FROM a neighbor to itself
      AND each server has a connection that was initiated FROM itself to a neighbor.

      This is how a notion of a "PC" or Peer-Client and "PS" or Peer-Server is created.
      PC2PS implies that this server will send data originating FROM one of its "server-cluster probing"
      interfaces (as opposed to its single "server-cluster listening" interface) TO
      the single "server-cluster listening" interface of the neighboring server on the 
      other end of the connection.

      PS2PC implies that this server will send data originating FROM its single "server-cluster listening"
      interface (as opposed to its many "server-cluster probing" interfaces) TO 
      the corresponding "server-cluster probing" interface of the neighboring server on the
      other end of the connection.

      All connections between server clusters are called ConnServerClusters. Each
      ConnServerCluster has exactly 2 end points. One of these end points is
      contained as a connection within a NICListenerServerToServer. The other end point
      is contained as a connection within a NICProberServerToServer. That is, each
      NICListenerServerToServer is associated with one or more NICProberServerToServer
      NICs, and each NICProberServerToServer is associated with exactly one
      NICListenerServerToServer.

   \{
*/
class ConnServerCluster: public TNL::EventConnection
{
   typedef TNL::EventConnection Parent;
public:

   /**
      TNL_DECLARE_NETCONNECTION is used to declare that ConnServerCluster is a valid connection class to the
      TNL network system.
   */
   TNL_DECLARE_NETCONNECTION( ConnServerCluster );

   /**
      A ConnServerCluster creates a logical connection between two peer servers within the same
      server cluster. 
      
      \see ConnServerCluster
   */
   ConnServerCluster();

   virtual ~ConnServerCluster();

   /**
      onConnectTerminated is called when the connection request to the server
      is unable to complete due to server rejection, timeout or other error.
      When a ConnClientGhost connect request to a server is terminated, the client's network interface
      is notified so it can begin searching for another server to connect to.
   */
   void onConnectTerminated( TNL::NetConnection::TerminationReason reason, const char* rejectionString );

   /**
      onConnectionTerminated is called when an established connection is terminated, whether
      from the local or remote hosts explicitly disconnecting, timing out or network error.
      When a ConnClientGhost to a server is disconnected, the client's network interface
      is notified so it can begin searching for another server to connect to.
   */
   void onConnectionTerminated( TNL::NetConnection::TerminationReason reason, const char* string );

   /**
      onConnectionEstablished is called on both ends of a connection when the connection is established.  
      On the server this will create a player for this client, and set it as the client's
      scope object.  On both sides this will set the proper ghosting behavior for the connection
      (ie server to client).
   */
   void onConnectionEstablished(); 

   /**
      isDataToTransmit is called each time the connection is ready to send a packet.  If
      the NetConnection subclass has data to send it should return true.  In the case of a simulation,
      this should always return true.
   */
   bool isDataToTransmit();

   /**
      Serializes all WO state data (including ODE state) into a set of TNL::Vectors
      which are then sent across the wire when this method invokes:
      ConnServerCluster::rpcPC2PS_sendHandOffWOToNeighbor.

      Subsequently, the body of ConnServerCluster::rpcPC2PS_sendHandOffWOToNeighbor
      is invoked on the remote machine.
   */
   virtual void performHandOffToNeighbor( WO* wo );

   /**
      This method is invoked by ConnServerCluster::rpcPC2PS_sendHandOffWOToNeighbor when data
      regarding a newly received WO arrives.

      This method searches NetSimulation::interWorldLst for the corresponding WO that has just moved
      into this cluster server. If found, the WO is properly sync'd using the in passed state
      information. Typically, this involves creating a corresponding ODE body, syncing the position,
      orientation, angular velocity, and linear velocity of the WO and ALL of its children WOs.

      Upon completion of the aforementioned tasks, this method invokes NetSimulation::onReceivedNewWOFromHandOff(...)
      and passes a pointer to the new WO that has just been created on this cluster server instance.

   */
   void receivedHandOffFromNeighbor( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& gfxData, TNL::Vector< TNL::F32 >& odeData );

   /**
      This method is invoked when a WO residing in this local cluster volume enters a BORDER
      region. POS_IN_CLUSTER_VOLUME. This begins cloning the WO (including the WO's ODE body) to the
      neighboring cluster server(s) lying adjacent to the border region. NetSimulation::neighbors.
      \param WO* pointer to the WO that will be cloned to neighboring servers.
   */
   void startCloneSession( WO* wo );

   /**
      This method is invoked on the remote neighbor server cluster when that neighbor receives the RPC
      indicating that the neighbor should begin cloning a WO. This method is invoked in response to the 
      authoritative server cluster invoking startCloneSession.
   */
   void receivedStartCloneSession( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& gfxData, TNL::Vector< TNL::F32 >& odeData, TNL::Vector< TNL::U32 >& allKeysPressed );

   /**
      This method is invoked when a WO residing in this local cluster volume leaves the BORDER
      zone. This signals the clone residing on the corresponding neighbor to
      destroy itself.

      This is invoked when the WO enters the INTERIOR of its authoritative server cluster OR when the WO
      completely leaves the local volume cluster. In the case where the WO leaves the local volume cluster,
      the clone is completely terminated and removed prior to the official handoff taking place.

      \see POS_IN_CLUSTER_VOLUME
   */
   void terminateCloneSession( WO* wo );
   
   /**
      This method is invoked on the remote end of this connection in response to the other end
      calling terminateCloneSession.

      This method destroys the clone (including the ODE body) and relocates the WO from the GLView::worldLst
      to the NetSimulation::interWorldLst.
   */
   void receivedTerminateCloneSession( TNL::Vector< TNL::S32 >& intVec );

   /**
      This method is invoked each tick after a CloneSession has started and before that CloneSession is terminated.
      This method forwards any keyboard activity related to the WO to the neighboring server cluster that is currently
      cloning the WO.
   */
   void updateCloneSession( WO* wo );

   /**
      This method is invoked on the remote end of this connection in response to the other end
      calling receivedTerminateCloneSession. This actually calls the onKeyDown and onKeyUp methods
      corresponding to the keystrokes within the passed data.
   */
   void receivedUpdateCloneSession( TNL::U32 woID, TNL::Vector< TNL::U32 >& recentKeysPressed, TNL::Vector< TNL::U32 >& recentKeysReleased );

   /**
      This method is invoked periodically via the NetClusterWOCloneSession instance associated
      with a WO and a particular neighboring server. This resends position, orientation, linear
      velocity, and angular velocity to non-authoritative clones residing on a neighboring server.
      This is needed because different servers can operate at different speeds, meaning the keypresses
      on one server have less/more of an effect because the physics engine could be running at different
      ratios; hence, the authoritative server (this instance) needs to periodically force a resync to 
      correct any drift between the authoritative instance of the WO and the non-authoritative clone
      on the neighboring server.

      The woID is the associated non-authoritative clone to be updated, the graphical data contains the
      position and orientation, and the ode data contains linear and angular velocities.
   */
   void updateCloneSessionForceSync( WO* wo );

   /**
      This method is invoked on a non-authoritative neighboring server in response to the
      authoritative server invoking ConnServerCluster::updateCloneSessionForceSync().
   */
   void receivedUpdateCloneSessionForceSync( TNL::U32 woID, TNL::Vector< TNL::F32 >& gfxData, TNL::Vector< TNL::F32 >& odeData );

   /**
      Send Guranteed Ordered Data from this peer client to its corresponding peer server.
      In the server cluster, each server node has a DOUBLE mesh topology to all neighbors.
      That is, if there are N server nodes, each node has exactly 2*(N-1) connections.
      This is because each server has a connection that was initiated FROM a neighbor to itself
      AND each server has a connection that was initiated FROM itself to a neighbor.

      This is how a notion of a "PC" or Peer-Client and "PS" or Peer-Server is created.
      PC2PS implies that this server will send data originating FROM one of its "server-cluster probing"
      interfaces (as opposed to its single "server-cluster listening" interface) TO
      the single "server-cluster listening" interface of the neighboring server on the 
      other end of the connection.

      PS2PC implies that this server will send data originating FROM its single "server-cluster listening"
      interface (as opposed to its many "server-cluster probing" interfaces) TO 
      the corresponding "server-cluster probing" interface of the neighboring server on the
      other end of the connection.
   */
   TNL_DECLARE_RPC( rpcPC2PS_sendGuranteedOrderedData, ( TNL::Vector< TNL::S32 > intVec, TNL::Vector< TNL::F32 > floatVec ) );
   TNL_DECLARE_RPC( rpcPC2PS_sendRequestClusterServerInitInfo, () );
   TNL_DECLARE_RPC( rpcPC2PS_recvRequestClusterServerInitInfo, ( TNL::Vector< TNL::S32 > intVec, TNL::Vector< TNL::F32 > floatVec ) );
   TNL_DECLARE_RPC( rpcPC2PS_sendHandOffWOToNeighbor, ( TNL::Vector< TNL::S32 > intVec, TNL::Vector< TNL::F32 > gfxData, TNL::Vector< TNL::F32 > odeData ) );

   //Clone RPCs
   /**
      This RPC actually serializes and transmits the data generated within startCloneSession. This
      data is sent to the other end of this connection where it is deserialized. 
      
      On the remote machine, this RPC then invokes receivedStartCloneSession.
   */
   TNL_DECLARE_RPC( rpcPC2PS_sendStartCloneSession, ( TNL::Vector< TNL::S32 > intVec, TNL::Vector< TNL::F32 > gfxData, TNL::Vector< TNL::F32 > odeData, TNL::Vector< TNL::U32 > allKeysPressed ) );

   /**
      This RPC actually serializes and transmits the key press data generated within updateCloneSession. This
      data is sent to the other end of this connection where it is deserialized. 
      
      On the remote machine, this RPC then invokes receivedUpdateCloneSession.
   */
   TNL_DECLARE_RPC( rpcPC2PS_sendUpdateCloneSession, ( TNL::U32 woID, TNL::Vector< TNL::U32 > recentKeysPressed, TNL::Vector< TNL::U32 > recentKeysReleased ) );

   /**
      This RPC actually serializes and transmits the position, orientation, linear velocity, and
      angular velocity of the current authoritative WO to the non-authoritative cloned WO on a
      neighboring server. This is called periodically based on a timer within 
      NetClusterWOCloneSession::updateCloneSession. This
      data is sent to the other end of this connection where it is deserialized and overwrites
      that data on the non-authoritative clone. Thus the non-authoritative (remote) clone is forced
      to 'pop' back to exactly what the authoritative server has calculated it to be. This compensates
      for any drift between the authoriative server and the non-authoritative server.
      
      On the remote machine, this RPC then invokes receivedUpdateCloneSession.
   */
   TNL_DECLARE_RPC( rpcPC2PS_sendUpdateCloneSessionForceSync, ( TNL::U32 woID, TNL::Vector< TNL::F32 > gfxData, TNL::Vector< TNL::F32 > odeData ) );

   /**
      This RPC actually serializes and transmits the data generated within terminateCloneSession. This
      data is sent to the other end of this connection where it is deserialized. 
      
      On the remote machine, this RPC then invokes receivedTerminateCloneSession.
   */
   TNL_DECLARE_RPC( rpcPC2PS_sendTerminateCloneSession, ( TNL::Vector< TNL::S32 > intVec ) );

protected:
   static const unsigned int gfxData_VEC_SIZE = 12; ///< 9 floats of orientation and 3 floats of position
   static const unsigned int odeData_VEC_SIZE = 6; ///< ODE's linear and angular x,y,z velocities

   /**
      Recusively packs a WO's graphics and ODE data into two corresponding vectors. This traverses all
      children, grandchildren, great grandchildren, etc (all decendants) of that WO.

      These two vectors are then serialized and sent to the server at the other end of this connection.
      From there, the respective unPack methods are invoked to reconstruct identical copies of those WOs
      on the neighboring server.
   */
   void packWOStateToVec( WO* wo, TNL::Vector< TNL::F32 >& gfxData, TNL::Vector< TNL::F32 >& odeData );

   /**
      All graphical data must be unpacked prior to any ODE data because the orientation stored in the
      graphical model is used by ODE during WO::ODEinitInODE(). This unpacks the graphical data
      and populates the WO's model.
   */
   void unPackWOgfxStateFromVec( WO* wo, TNL::Vector< TNL::F32 >& gfxData );

   /**
      After the graphical data is unpacked, the ODE state data is unpacked and placed inside to WO.
      This method also invokes WO::ODEinitInODE() to instantiate the corresponding ODE bodies.
   */
   void unPackWOodeStateFromVec( WO* wo, TNL::Vector< TNL::F32 >& odeData );

   /**
      Searches the NetSimulation::interWorldLst for a WO with and id of woID. It returns a pointer
      to that WO. It will also set the interWorldLstIndex to the actual index within the list. This
      way, another search does not need to be performed when/if the WO needs to be moved between lists.
      For example if the WO is moved from the NetSimulation::interWorldLst to the GLView::worldLst, the
      index is already known so another search is avoided.
   */
   WO* searchNetSimulationInterWorldLstForWOID( unsigned int woID, size_t* interWorldLstIndex );

   /**
      Searches the GLView::worldLst for a WO with and id of woID. It returns a pointer
      to that WO. It will also set the worldLstIndex to the actual index within the list. This
      way, another search does not need to be performed when/if the WO needs to be moved between lists.
      For example if the WO is moved from the GLView::worldLst to the NetSimulation::interWorldLst, the
      index is already known so another search is avoided.
   */
   WO* searchGLViewWorldLstForWOID( unsigned int woID, size_t* worldLstIndex );
   

};

} //namespace Aftr

#endif //AFTR_CONFIG_USE_TNL
