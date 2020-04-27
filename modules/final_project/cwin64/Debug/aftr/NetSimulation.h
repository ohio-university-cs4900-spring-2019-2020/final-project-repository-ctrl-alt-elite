#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include "NetWO.h"
#include "WorldList.h"
#include <vector>
#include <set>
#include <string>

namespace TNL
{
   class NetConnection;
   class AsymmetricKey;
}

namespace Aftr
{
   class GLView;
   class WorldContainer;
   class WorldObjectChildContainer;
   class WOClusterVolumeViewer;
   class ConnClientGhost;
   class NICAftrBase;
   class NICProberClientToServer;
   class NICProberServerToServer;
   class NICListenerServerToClient;
   class NICListenerServerToServer;

   enum class NET_SIM_TYPE : unsigned char { nstSTANDALONE = 0, nstSERVER_DEDICATED, nstSERVER, nstCLIENT, nstNUM_NET_SIM_TYPE };
   std::ostream& operator<<( std::ostream& out, const NET_SIM_TYPE& nst );

/**
   \class NetSimulation
   \author Scott Nykl

   Tell Scott to talk about servers, clients, stand alone, how servers serve, how clients
   connect, how RPCs work. RPCs in a NetWO versus RPCs in a ConnClientGhost.
   Talk about NICAftrBase and ClientGhost Connection...etc...

   As clients join the server, the server invokes
   RPCs on the client to instaniate NetWOs for all WOs on the client. After instantiated
   on the client, the client invokes NetWO::rpcC2S_requestCorrespondingWOID() to ask the
   server, "What woID should be associated with this new NetWO you just had me create?".
   The client then places the new NetWO* into a queue while waiting for a response.

   Because all these requests to the server are guranteed and ordered, it is assured that
   the first woID returned from the server to the client via 
   ConnClientGhost::rpcS2C_requestCorrespondingWOID( woID ) corresponds to the first
   NetWO* in the queue. Once the client recieves the response, the corresponding woID is
   assigned to the NetWO*, and that NetWO* is associated with its corresponding WO. It is
   at this point that the WO::onRegisteredWithServer() is invoked.

   \{
*/
class NetSimulation
{

public:

   /**
      Gives ConnServerCluster access to NetSimulation internals for efficient RPC purposes
   */
   friend class ConnServerCluster;

   /**
      If true, every instance of NICAftrBase or below will log all bytes receieved over time.
      This is used to collect experimental data about network bandwidth.
   */
   static const bool LOG_BYTES_RECEIVED_PER_TNL_INTERFACE = false;

   /**
      Default constructor. Sets the NetSimType and creates a NICAftrBase used to
      communicate with servers/clients (based on this instance's NetSimType). This does not
      create any NetWO objects at this point! The user is required to invoke NetSimulation::init()
      AFTER GLView::LoadMap() completes. This design allows the NetSimulation to be instantiated 
      prior to GLView::LoadMap() invokation. This is useful because it allows other subsystems
      to ask what the NetSimType for this instance is.
      
      It is REQUIRED that the user invoke NetSimulation::init() AFTER GLView::LoadMap()
      completes execution! This is because the init() method iterates through the 
      worldLst (populated inside of GLView::LoadMap() and creates a 1-to-1 mapping between
      each WO in the worldLst and creates a new NetWO object used for
      server/client synchronization (This only happens on the server side). Client NetWO's
      are created as the client's scope object comes within a certain proximity to a NetWO
      residing on the server.

      Failure to invoke NetSimulation::init() will cause clients to be unable to receive
      NetWO updates for each of the corresponding WOs.
   */
   NetSimulation( NET_SIM_TYPE simType, bool clusteringEnabled, 
                  unsigned int serverClusterID_or_numClusterServersExpectedByClient,
                  GLView* view, TNL::Address* serverAddress = NULL );

   virtual ~NetSimulation();

   /**
      This method is invoked by GLView::init(). This method automatically parses argc and argv
      to properly acquire the information needed to new the corresponding NetSimulation that will
      be use by this instance. This shall actually new the NetSimulation and return it. If there
      is an error, this method shall halt execution, print the error message, and terminate
      execution.

      The user must pass in the corresponding glView that shall own this NetSimulation instance.
      The user must also pass in the argc and argv command line arguments passed in at beginning
      of run time.
   */
   static NetSimulation* constructNetSimulation( GLView* glView, int argc, char* argv[] );

   /**
      This method MUST be called AFTER GLView::LoadMap() completes execution. This method iterates through the 
      worldLst (populated inside of GLView::LoadMap() and creates a 1-to-1 mapping between each WO in the worldLst and
      creates a new NetWO object used for server/client synchronization. (This only happens on the server side). 
      Client NetWO's are created as the client's scope object comes within a certain proximity to a NetWO
      residing on the server.
   */
   void init();

   /**
      Called server-side to gather the new position/orientation of
      each WO within the server's simulation.

      Syncs EVERY NetWO to the position/orientation of the corresponding WO.
      If a change has occurred between the original values of NetWO AND the
      current graphical position, then the NetWO's update mask will be
      set appropriately. The change in position and/or orientation must be larger than
      POS_DELTA_EPSILON and ORIENTATION_DELTA_EPSILON, respectively.
   */
   void syncNetWOfromGFX();

   /**
      Returns the type of net simulation this local process represents. For example, if this process is a client
      connected to a server, then NET_SIM_TYPE::nstCLIENT shall be returned. Likewise, if this is a server, then NET_SIM_TYPE::nstSERVER
      shall be returned.

      \return The Net Simulation Type of this simulation NET_SIM_TYPE
   */
   NET_SIM_TYPE getNetSimType() { return this->simType; }

   /**
      Returns true if clustering is enabled on this instance; false, otherwise.
      Typically, this means that the user started the application with a
      -clientC, -serverC, or -dedicatedC
   */
   bool clusteringEnabled() { return this->ClusteringEnabled; }

   ///////**
   //////   Sets the server cluster ID of this instance. This should only be called while
   //////   NetSimulation is initializing. 0 means this server has not yet fully joined a 
   //////   server cluster. 1 means this server is the authoritative server within the server cluster.
   //////   \param The server cluster ID to be assigned to this server instance within a server cluster.
   //////*/
   //////void setServerClusterID( unsigned int serverClusterID ) { this->serverClusterID = (TNL::U32) serverClusterID; }

   /**
      \return The ID of this server within the server cluster. 0 means this server has not yet 
      fully joined a server cluster. 1 means this server is the authoritative server within 
      the server cluster.      
   */
   unsigned int getServerClusterID() { return (unsigned int) this->serverClusterID; }

   /**
      Ensures all WOs that do not exist within this local cluster volume are removed from the GLView's
      worldLst, netLst, and actorLst. The WOs that are removed from the list are still instantiated, but
      are stored internally to the NetSimulation and do not return to their respective lists in the GLView
      until those WOs migrate into this server's local cluster volume.
   */
   void initLocalClusterVolume( WorldContainer* worldLst, WorldContainer* netLst, WorldContainer* actorLst );

   /**
      Uses max and min as OUT ONLY parameters. Max will contain the 'largest' (most positive) vertex in this server
      cluster's volume. Min will contain the 'smallest' (most negative) vertex in this cluster's volume.
   */
   void getLocalClusterVolume( Vector& max, Vector& min );

   /**
      Invoked by ConnServerCluster::rpcPC2PS_recvRequestClusterServerInitInfo() method.
      When a server prober initially connects with a server listener, the server prober invokes an RPC
      to request the newly discovered cluster volume's dimensions, id, and other necessary initialization information.
      When the server listener responds,
      ConnServerCluster::rpcPC2PS_recvRequestClusterServerInitInfo() is invoked which in turn invokes
      this method to notify the NetSimulation.
      \param The server prober nic that has received its initilization information from the corresponding server listener.
   */
   void onRemoteClusterServerNeighborConnEstablished( NICProberServerToServer* nic );

   /**
      Invoked when a server within the server cluster exits. This allows the NetSimulation
      to update its neighbor list and remove that exiting cluster server from the current
      NetSimulation's state.
      \param The server prober nic that is being destoryed because the corresponding server listener
      interface on the other end of the connection is exiting.
   */
   void onRemoteClusterServerConnectionTerminated( NICProberServerToServer* nic );

   /**
      Invoked when this server cluster instance receives a hand off from a neighboring
      server. This method moves the WO out of the interWorldLst, interNetLst, interActorLst to 
      the worldLst, netLst, actorLst, respectively.
   */
   void onReceivedNewWOFromHandOff( WO* newWO, size_t indexInInterWorldLst );

   /**
      Invoked when this server cluster instance receives notification that a WO located in another
      server's cluster volume is "near" this server's cluster volume. Therefore, this server should begin
      "cloning" the WO so that if the WO is handed off to this server (if the WO crosses into this server
      cluster's volume), the transition will be transparent as the approriate physics/graphics bodies
      for the WO will already be properly sync'd to this server.
   */
   void onReceivedNewWOFromStartCloneSession( WO* wo, size_t indexInInterWorldLst );

   void onReceivedTerminateCloneSession( WO* wo, size_t indexInGLViewWorldLst );

   /**
      \return a reference to the internal vector which stores all NetWO* instaniated on this instance. This
      is valid for a server and client; however, this is only valid on the client AFTER the client is fully
      sync'd with the server. That is, once the client's WO::onRegisteredWithServer() has been invoked for a
      particular WO, the corresponding NetWO will be in this list. Until the WO::onRegisteredWithServer() has
      been invoked; the user CANNOT assume the corresponding NetWO* is valid.
   */
   std::vector< NetWO* >& getNetWOLst() { return this->netWOLst; }

   /**
      Called within the server to find the NetWO* that corresponds to the scoped object used for ghosting.

      \return Pointer to the Scoped Object used for determining other object relevant to a client.
      EX: If a Human is .5 units away from the scoped object, this is probably close enough for the
      Human to be 'relevant' and therefore advertised to the client from the server.

   */
   NetWO* findScopedNetWO();

   /**
      Given a woID, return the corresponding NetWO*. If woID is not found, NULL
      shall be returned.
   */
   NetWO* getNetWO( unsigned int woID );

   /**
      Called by all NET_SIM_TYPEs to physically send/recieve data out/in of this application's process.
      Internally, this method only 'ticks' interfaces relevant to its simulation type. For example, if 
      this instance is a client, only client interfaces will be ticks; no server-related interfaces
      will be accessed. Vice-versa for server mode. In standalone, no interfaces are accessed, this
      method simply returns.

      'ticks' the actual network interface. 
      Causes the virtual network cards to:
      -# send all pending info to all clients
      -# process any packets that have arrived and not yet been processed.
   */
   void tick();

   /**
      Thie method checks each object within this cluster volume against this volume's borders. If an
      object is near to a border, a corresponding update is generated to that neighboring cluster server.
      This method is essential for one cluster server to properly notify a neighboring cluster server 
      that an object may soon have a transfer of authoritative cluster server.

      This method should be invoked when clustering is enabled and this instance is any type 
      of server cluster (normal server or dedicated server, but NOT STANDALONE). Additionally, this 
      must be invoked immediately before NetSimulation::tick(). Because this is invoked immediately
      before NetSimulation::tick(), this directly implies that the graphical objects of each WO have
      been recently sync'd from the physics engine; if this is not the case, then WO->getPosition() will
      return an old value and this method will incorrectly think a WO is located at an "older" position
      than that WO really is.
   */
   void updateLocalClusterInfo();

   /**
      This method is invoked on client-side upon receiving the WOID a new NetWO should be associated
      with.

      The client recieves messages from the server indicating that a new NetWO should be created
      because that NetWO has just come 'in scope' on the client. When this happens, a NetWO is
      constructed on the client side. However, before this NetWO is useful to the client, the client
      must know which WO the NetWO needs to be associated with; therefore, NetWO::onGhostAdd() invokes
      an RPC to the server asking, "Hey server, you just sent me a brand new NetWO, but what WOID should
      I bind this NetWO with?"

      The server responds by sending the WOID that the new NetWO should be associated. As soon as that
      data is recieved and assigned to the new NetWO, this method is invoked.

      \return true if NetWO is successfully registered with a WO; false, otherwise.
   */
   bool registerNewNetWOwithNetSimulation( NetWO* newNetWO, ConnClientGhost* conn );

   /**
      This server-side method is typically invoked by ConnClientGhost::onConnectionTerminated
      when a client gracefully exits the simulation. Alternatively, if a client exits the simulation
      without properly signaling the server this may not be invoked until the timeout period expires.
      In this event, it is also possible that the getNextAvailableClientActorWOID() will invoke this 
      method when a new client joins the simulation. This ensures that clients which have left the simulation
      no longer occupy a WO* in the occupiedNetActors.

      This method can also be called as a house keeping method to remove clients that 
      have exited the simulation at any point. The WO*s that were controlled by that terminated 
      client are removed from the NetSimulation::occupiedNetActors vector<WO*> and added back into the
      NetSimulation::availableNetActors vector<WO*>.

      \param (out only param) reclaimedWOs is a vector containing WO* to the WOs that were just reclaimed. 
      reclaimedWOs.size() will always equal the return value of this method (number of WO*s reclaimed).
      This vector is useful, for example, when a client disconnects from a server: all the WOs that were
      controlled by that client are pointed to in this list. The server can then manually reset the 
      internal state of these WOs (position, orientation, user-specific state, etc) 
      so when a new client joins in they are properly initialized.
      The user doesn't need to use this vector at all; however, it may be useful in some circumstances.

      \return The number of WO* that were reclaimed (removed from occupiedNetActors vector) and
      added back into the availableNetActors vector. If zero is returned, no WO*s were reclaimed; this
      implies no clients exited the simulation.
   */
   unsigned int reclaimAvailableClientActorWOIDs( std::vector< WO* >& reclaimedActors );

   void onKeyDown( const SDL_KeyboardEvent& key, WO* actor );
   void onKeyUp( const SDL_KeyboardEvent& key, WO* actor );

   /**
      \returns The woID corresponding to the next available actor that a client shall control via the network.
   */
   TNL::U32 getNextAvailableClientActorWOID();


   void invokeGLViewClientOnClientConnect( TNL::U32 serverAssignedClientActorWOID, ConnClientGhost* client );
   void invokeGLViewServerOnClientConnect( TNL::U32 serverAssignedClientActorWOID, ConnClientGhost* client = NULL );

   /**
      Returns a pointer to the current list of occupied net actors. These are WOs which are CURRENTLY controlled by
      players in the this simulation. When a player leaves, that player's WOs is moved from this list to the
      available net actors list.
   */
   std::vector< WO* >* getOccupiedNetActors() { return &occupiedNetActors; }

   /**
      Returns the GLView associated with this NetSimulation.
   */
   GLView* getGLView() { return this->glView; }

   /**
      Returns a pointer to this Cluster Server's ServerListener Virtual Interface.
      Only used by Cluster Servers
   */
   NICListenerServerToServer* getNICListenerServerToServer() { return this->nicSL; }

   /**
      Returns a pointer this Server's Client Listener Virtual Interface.
   */
   NICListenerServerToClient* getNICListenerServerToClient() { return this->nicCL; }

   /**
      Returns a reference to the vector of Client Probe Interfaces to each server.
      This will have exactly 1 interface (Non-clustered mode) in the list unless this client is attempting
      to connect to multiple Cluster Servers (Cluster mode).
   */
   std::vector< NICProberClientToServer* >& getNICsProberClientToServer() { return this->nicCSC; }

   /**
      Returns a reference to the vector of Server Probe Interfaces to each Cluster Server.
      Only used by Cluster Servers.
   */
   std::vector< NICProberServerToServer* >& getNICsProberServerToServer() { return this->nicSSC; }

   /**
      This method is valid only for cluster server instances. Returns the
      WOClusterVolumeViewer object instantiated by this NetSimulation during initialization.
   */
   WOClusterVolumeViewer* getClusterVolumeViewer() { return this->clusterVolumeViewer; }

   /**
      Returns the current state information of this NetSimulation instance. Includes all connections,
      object counts/locations, cluster info, etc.
   */
   std::string toString();

   void testRpcPC2PS_sendGuranteedOrderedData();

   /**
      Size or array containing pointers to All 26 neighbors (minus position 9, 18, 19).
      neighbors list in NetSimulation for positional locations corresponding to
      each of the values [0,8], [10,17], [20,28].
   */
   static const int NEIGHBOR_LST_SIZE = 29;

   /**
      Categorizies the position of a WO within its server clusters volume. The WO will either
      reside in the local volume's interior or border. If neither, then the WO is outside the
      local cluster volume and does not reside on this server cluster.

      Even if a WO does not officially reside on this server cluster, there may be a 'clone' of
      the WO near the OUTSIDE perimeter of this volume.
   */
   enum POS_IN_CLUSTER_VOLUME { INTERIOR = 0, BORDER, OUTSIDE };

protected:


   /**
      This is executed only on the SERVER to initially create 
      one 'net ghost' for each WO*. As clients join the server, the server invokes
      RPCs on the client to instaniate NetWOs for all WOs on the client. After instantiated
      on the client, the client invokes NetWO::rpcC2S_requestCorrespondingWOID() to ask the
      server, "What woID should be associated with this new NetWO you just had me create?".
      The client then places the new NetWO* into a queue while waiting for a response.

      Because all these requests to the server are guranteed and ordered, it is assured that
      the first woID returned from the server to the client via 
      ConnClientGhost::rpcS2C_requestCorrespondingWOID( woID ) corresponds to the first
      NetWO* in the queue. Once the client recieves the response, the corresponding woID is
      assigned to the NetWO*, and that NetWO* is associated with its corresponding WO. It is
      at this point that the WO::onRegisteredWithServer() is invoked.
   
      However, one 'net ghost' only updates ONE WO*. Thus,
      if a WO* is a hierarchical object, we must manually buzz through
      all of the children and create a 'net ghost' for each child as well.
   */
   void createNetWOs();

   /**
      Helper method used by NetSimulation::createNetWOs. Recursively traverses
      in passed list.
   */
   void createNetWOsRec( WO* wo );

   /**
      Helper method used by NetSimulation::createNetWOs. Creates a single NetWO
      corresponding to a WO, associates that NetWO to its WO and vice-versa, 
      initially sync's position/orientation data, and inserts the new NetWO in
      NetSimulation::netWOLst.
   */
   void createOneNetWO( WO* wo );

   /**
      This method is only valid for a cluster server.
      This method takes a WO* and removes all associated NetWOs (including all children
      of the parent WO*) from this cluster server. This is used when a WO is handed off
      from one cluster server to another; this server no longer ownes that WO (and its
      children) and therefore no longer ghosts that WO (and its children) to any 
      connected clients.
   */
   void removeNetWOsFromNetWOLst( WO* woToHaveNetWORemovedFromList );

   /**
      \returns the WO* containing the corresponding woID; NULL, if not found. A recursive search
      through the entire GLView::worldLst is performed; hence, this method is slower, but useful
      at initialization time when the NetSimulation::netLst is not yet fully populated and the
      associated NetWO not yet initialized.
   */
   WO* getAssociatedWOptr( TNL::U32 woID );

   /**
      Called within the server instance by the constructor. This method gets the net list of available
      net actors for the simulation and begins management of available/occupied net actors. When a new
      client joins, that client is assigned to control the next available net actor. NOTE: This method
      is invoked ONLY if the simulation type is NET_SIM_TYPE::nstSERVER or NET_SIM_TYPE::nstSERVER_DEDICATED \see NET_SIM_TYPE.
   */
   void initAvailableNetActors();

   /**
      New's each WO's NetClusterWOCloneManager pointer and initializes the data based on the type of
      WO. For example, if a WO is a skybox, then the NetClusterWOCloneManager will indicate that this
      WO shall not be handed off between servers as it is a special object.
   */
   void initNetClusterWOCloneManagerForEachWO( WorldContainer* worldLst );

   /**
      Recursively search through all WOs in the in passed list and return a 
      pointer to the WO with the corresponding WOID. If that woID is not found,
      NULL is returned.
   */
   WO* findWO( WorldContainer* list, unsigned int woID );

   /**
      Called by findWO to recurse through all children of a given WO. This is a helper
      method used by NetSimulation::findWO(...).
   */
   WO* recFindWO( WO* wo, unsigned int woID );

   /**
      Very simple parser that deserializes a cluster.conf file to gather the
      the position and extents of the internal and external zones of each server cluster
      listed in the conf file.

      This is a very simple parser that will fail if the conf file is not correct
      in almost any way.
   */
   bool parseClusterConfigFile( const std::string& fileName, Vector& centerPt, Vector& lxlylz, Vector& interiorLxLyLz );

   /**
      Scott will doc soon
      Initially populates interClusterWOLst list by moving WOs from worldLst into
      interClusterWOLst if those WOs do not currently reside in the cluster volume
      of this server.
   */
   void moveWOsNotExistingInThisClusterVolume( WorldContainer* srcLst, WorldContainer* conditionalDstLst );

   /**
      Scott will doc soon... this one should be obvious
   */
   void moveWOBetweenLists( WorldContainer* srcLst, size_t indexOfWOToBeMoved, WorldContainer* dstLst );


   /**
      Given a WO, this method locates the current zone this WO currently resides. The return
      value will be of type POS_IN_CLUSTER_VOLUME (which is either INTERIOR, BORDER, or
      OUTSIDE.

      If the WO resides in the interior, no neighbors need to be notified of this WO's current
      state.

      If the WO resides in the border, between 9 and 19 neighbors may need to be notified.
      In this case, the out value of zoneMasks will contain a bit mask. Each bit location containing
      a '1' indicates the neighbor which needs to recieve an update (if that neighbor exists).

      If the WO resides outside this local cluster volume, zoneMask will contain the integer value
      of the server this WO should be handed off to. 
      This value will be between [0,28] excluding 9,18,19, which do not exist as shown below.

      The neighbor value is indicated by the following diagrams:

      9 Neighbors BELOW this cluster volume (08 is directly below this cluster volume)
                                 01 00 07
                                 02 08 06
                                 03 04 05

      8 Neighbors BELOW this cluster volume (XX is this cluster volume)
                                 11 10 17
                                 12 XX 16
                                 13 14 15  NOTE: XX has numerical value of 18

      9 Neighbors ABOVE this cluster volume (28 is directly above this cluster volume)
                                 21 20 27
                                 22 28 26
                                 23 24 25
   */
   POS_IN_CLUSTER_VOLUME locateWOInLocalClusterVolume( WO* wo, std::set< unsigned int >& neighbors );

   /**
      Once NetSimulation::locateWOInLocalClusterVolume learns that the WO in question still
      resides within this local server cluster, the neighboring servers may need to be updated
      if this WO resides within the border region shared amongst one or more neighboring server
      clusters.

      This is a help method invoked from within NetSimulation::computeUpdateNeighborServers. It uses
      the current local region (local zone id) the WO resides to populate the in passed set with all corresponding
      neighboring servers that need to know about this WO.
      
   */
   void findNeighborsRequiringWOUpdateInfo( int localZoneID, std::set< unsigned int >& neighbors );

   /**
      This is a helper method invoked by NetSimulation::locateWOInLocalClusterVolume.
      This method is very similar to computeHandOffNeighborServer, except that instead of 
      checking if the WO in question resides outside of the local server cluster, it returns the
      local region ID where the WO lies within the border/interior cluster.

      This method should only be invoked after it has been determined that the WO in question does
      NOT reside outside of this local server cluster volume. That is, NetSimulation::computeUpdateNeighborServers
      should be invoked first, and if that method returns 18 (numerical value of local server cluster),
      then this method will provide the local subregion in which the WO resides. The numbering scheme
      for the local subsystem is identical to the scheme used by locateWOInLocalClusterVolume, however,
      XX (i.e., 18) represents the interior border and NOT the entire local server cluster. The surrounding
      values represent subregions of this server cluster's local cluster volume.

      The subregion id returned from this method can be passed into 
      NetSimulation::findNeighborsRequiringWOUpdateInfo. This will then populate the in passed std set
      with the server cluster IDs of all neighbors that need to "hear" about this particular WOs activity.
   */
   unsigned int computeUpdateNeighborServers( const Vector& WOPosition );

   /**
      This is a helper method invoked within NetSimulation::locateWOInLocalClusterVolume .
      When it is determined that the corresponding WO is located outside of this entire cluster
      volume, this method computes and returns the exact neighboring volume in which the WO now
      resides. This method may return a neighbor that doesn't actually exist in the current simulation.
      If this method returns a value of 18, it means the WO in question still resides within the
      local server cluster volume.

      If the neighbor does not exist (for example, there are only 2 cluster servers in this cluster),
      this method still behaves exactly the same; logic subsequent to this method invokation is responsible
      for handling this case.
   */
   unsigned int computeHandOffNeighborServer( const Vector& WOPosition );

   /**
      When a cluster server joins or leaves the cluster, this method is invoked and updates the internal
      neighbor list to ensure all available neighbors are accessable and no inaccessable servers are percieved
      to be reachable.
   */
   void updateNeighborList( NICProberServerToServer* nic );

   /**
      Max and min are 2 points in 3 space which define the Quadrant 2 and Quadrant 4 corners of the 
      rectangular prism of this server's cluster volume. The Quadrant 2 point (Vector& max) is simply 
      the server cluster center plus the cluster volume's length x/2, y/2, and z/2.
      The Quadrant 4 point (Vector& min is simply the server cluster center minus
      the cluster volume's length x/2, y/2, and z/2.
      
      \param max - OUT ONLY - the most positive x,y,z coordinates this server controls.
      \param min - OUT ONLY - the most negative x,y,z coordinates this server controls.
   */
   void computeMaxAndMinVertsOfLocalClusterVolume( Vector& max, Vector& min );

   /**
      The interior cluster volume of this server is the area in which any motion of objects does not need
      to be propogated to any neighboring servers because those objects are too far away to cross a server
      boundary in the "near" future. Once an object leaves the interior cluster volume of the server, the 
      object enter's this server cluster's "border". This means that the object's activities will be 
      advertised to neighboring servers because there is a possibility that this
      object may be handed off from this server to a neighboring server within a few 'ticks'.

      The server cluster's border zone can be defined as the area outside of the Union of this server's
      local cluster volume AND this server's interior cluster volume.

      Max and min are 2 points in 3 space which define the Quadrant 2 and Quadrant 4 corners of the 
      rectangular prism of this server's interior cluster volume. The Quadrant 2 point (Vector& max) is simply 
      the server cluster center plus the cluster volume's length x/2, y/2, and z/2.
      The Quadrant 4 point (Vector& min is simply the server cluster center minus
      the cluster volume's length x/2, y/2, and z/2.

      \param max - OUT ONLY - the most positive x,y,z coordinates of this server's interior cluster volume.
      \param min - OUT ONLY - the most negative x,y,z coordinates of this server's interior cluster volume.
   */
   void computeMaxAndMinVertsOfLocalInteriorClusterVolume( Vector& max, Vector& min );

   /**
      Returns true if the handoff RPC is generated and the WO is moved from the local worldLst
      to the interWorldLst. Remember that this method WILL modify worldLst; thus, if one is looping
      through the list and an element is removed, one must ensure to adjust the counter otherwise
      an element may be skipped.

   */
   bool handOffWOToNeighborClusterServer( WorldContainer* worldLst, size_t index, unsigned int neighbor );

   /**
      Reads through bit mask of a 32-bit unsigned integer and prints out 
      the bit locations with a value of 1.
      \param Bit locations containing a '1' indicate a state of set.
   */
   void displayZoneMask( unsigned int zoneMask );

   /**
      Calculates the manhattan distance between hte start vector and end vector. The
      input vector lxlylz is the unit used to calculate the distance between the two
      points.
   */
   Vector computeManhattanDistance( const Vector& start, const Vector& end, const Vector& lxlylz );


   GLView* glView; ///< GLView of this NetSimulation

   /**
      This interface is only valid for a server-cluster instance. This is the
      interface responsible for listening on the Server Listening (SL) IP:PORT.
      This IP:PORT "hears" neighboring servers and forms an connection to them.
      That is, it listens for neighboring servers; hence, ServerListener (nicSL).

      This Server Listener uses ConnServerCluster connections to
      exchange data between servers. Conversely, the Client Listener uses
      ConnClientGhost connections to exchange data between server and
      clients.

      Once a simulation is running, this interface stores a connection between
      this server and its corresponding peer servers.

      A listening interface does not broadcast itself as a server; in order for a
      neighboring server to form a connection to this interface, that neighbor must use a
      non-listening interface (NICProberServerToServer). Hence, all server-cluster instances also make use
      of a set of interfaces that actively seek out connections to neighboring servers.
      This set is called the nicSSC set and is also a member of NetSimulation.
      
      This implies that each server has 2 connections to each neighboring server. One of the
      connections is stored within this nicSL interface. The other connection is stored in this 
      server's nicSSC interface set and terminates within the neighboring server's nicSL interface.
      The second connection is formed when the neighboring server uses an interface in it
      nicSSC set to actively form a connection to this server's nicSL interface.

      This "double-connected-ness" provides a mechanism for neighboring servers to communicate
      with each other using RPCs that still discriminate between server and client. The gives
      additional control over which objects are being administered by which server. If an RPC
      originates from the nicSL interfaces and is destined to an interface in the nicSSC set,
      this is a PS2PC (Peer-Server to Peer-Client) server-cluster RPC. If an RPC originates
      from the nicSSC interface set and is destined to a neighboring server's nicSL interface,
      this is a PC2PS (Peer-Client to Peer-Server) server-cluster RPC.
   */
   NICListenerServerToServer* nicSL;

   /**
      This interface is only valid on any non-client instance. This is the
      interface responsible for listening on the Client Listening (CL) IP:PORT.
      This IP:PORT "hears" newly instantiated clients who are searching for servers.
      After hearing a client's request for a server, this nicCL will respond to
      the client if the client is requesting a server of this server's type.
      For example, if this instance is a server-cluster and this interface "hears"
      a client request for a server-cluster, this interface will respond; otherwise,
      this interface will not respond to that client.

      This Client Listener uses ConnClientGhost connections to exchange 
      data between server and clients. Conversely, this Server Listener 
      uses ConnServerCluster connections to exchange data between servers.

      Once a simulation is running, this interface stores all the connections between
      this server and its corresponding clients. The corresponding endpoint at the client
      side will always be an interface within the nicCSC set on the client (that client's
      corresponding Client-Server Connection interface within the nicCSC set).
   */
   NICListenerServerToClient* nicCL;

   /**
      This set of interfaces are valid only on client instances. Each interface
      within this set represents exactly 1 connection between this client and a server.
      In the case where only a single server exists, this set will contain exactly 1
      interface. In the case where this client is connected to N servers in a 
      server-cluster, then this set will contain exactly N interfaces (one to each server).

      That is, this vector stores the Client-Server Connections (CSC) interfaces.
      Internally, these interfaces utilize a ConnClientGhost to exchange
      data between servers and clients (can utilize ghosting).

      Once a simulation is running, each interface in this set manages the NetWOs
      from a particular server that are currently relevant to this client. The 
      corresponding endpoint at the server side will always be that server's nicCL
      interface (that server's Client Listener interface).
   */
   std::vector< NICProberClientToServer* > nicCSC;

   /**
      This set of interfaces are valid only on a server-cluster instance. Each interface
      within this set represents exactly 1 connection between this server and a neighboring
      server.

      The corresponding endpoint at the neighboring server's side will always be that
      neighboring server's nicSL interface. That is, each Server-Server Connection (nicSSC)
      interface within this set ends at a neighboring server's Server Listening (nicSL)
      interface.

      This implies that each server has 2 connections to each neighboring server. One of the
      connections is stored in this nicSSC set. The other connection is stored in this 
      server's nicSL interface and terminates within the neighboring server's nicSSC set.
      The second connection was formed when the neighboring server used an interface in its
      nicSSC set to actively form a connection to this server's nicSL interface.

      This "double-connected-ness" provides a mechanism for neighboring servers to communicate
      with each other using RPCs that still discriminate between server and client. The gives
      additional control over which objects are being administered by which server.
   */
   std::vector< NICProberServerToServer* > nicSSC;
   
   NET_SIM_TYPE simType;   ///< Type of Net Simulation NET_SIM_TYPE
   bool ClusteringEnabled; ///< If true, this instance assumes it is participating in a server-cluster
   TNL::AsymmetricKey* connectionKey; ///< Key used to encrypt all connection to/from this instance

   std::vector< NetWO* > netWOLst; ///< vector of all NetWOs currently within this simulation

   
   /** Valid only within a non-client instance */
   std::vector< WO* > availableNetActors;
   
   /** Valid only within a non-client instance */
   std::vector< WO* > occupiedNetActors;

   /** 
      Valid only within a non-client instance. Corresponds to the WOID controlled 
      by this server instance.
   */
   TNL::U32 serverActorWOID;

   /**
      Each server in a server cluster is assigned a unique ID from the authoritative
      cluster server. An ID of 0 means this instance has not yet connected to and recieved
      an ID from the authoritative server. An ID of 1 means this instance is the authoritative
      cluster server. An ID of anything above 1 implies this server-cluster instance has properly
      connected w/ the authoritative cluster server.
   */
   TNL::U32 serverClusterID;

   /**
      This value is only valid for a clustered client instance. This value represents the number
      of NICProberClientToServer instances to create. One instance shall be created for each 
      cluster server within the entire cluster farm. That is, if N server clusters exist, each client
      should have this value set to N. This way, every client has one direct connection to each 
      cluster server within the cluster farm.
   */
   unsigned int numClusterServersExpectedByClient;

   Vector serverClusterCenter; ///< Center point of this server cluster volume
   Vector serverClusterLxLyLz; ///< Length of X,Y,Z dimensions of rectangular prism of cluster volume
   Vector serverClusterInteriorLxLyLz; ///< Length of X,Y,Z dimension of interior rectangular prism. This does not include the border volume.

   Vector scMaxVert; ///< The maximum vertex of this server cluster's volume
   Vector scMinVert; ///< The minimum vertex of this server cluster's volume
   Vector scInteriorMaxVert; ///< The maximum vertex of this server cluster's interior volume
   Vector scInteriorMinVert; ///< The minimum vertex of this server cluster's interior volume

   WorldList interWorldLst; ///< Stores WOs that were loaded into GLView::worldLst within GLView::LoadMap(), but do not current reside in this cluster volume
   WorldList interNetLst;   ///< Stores WOs that were loaded into GLView::netLst within GLView::LoadMap(), but do not current reside in this cluster volume
   WorldList interActorLst; ///< Stores WOs that were loaded into GLView::actorLst within GLView::LoadMap(), but do not current reside in this cluster volume

   /**
      This is only valid on server cluster instances.
      Every Cluster Server MUST have EXACTLY ONE WOClusterVolumeViewer; this object is used
      as the scope object for clients that are not current a resident of this cluster server's
      volume. The user is required to instantiate exactly one of these objects within his
      module's GLView::LoadMap(). If the user does not create this object, an error will
      be given explaining what the user must do.
   */
   WOClusterVolumeViewer* clusterVolumeViewer;
   
   /**
      This array contains pointers to the nics representing directly connected
      neighbors. A cube surrounded by similar cubes in an axis aligned grid
      will have 26 direct neighbors. The mapping below shows the index used
      within this array. If that neighbor does not exist within the simulation,
      then that element in the neighbors list will be NULL.

      The neighbor value is indicated by the following diagrams:

      9 Neighbors BELOW this cluster volume (08 is directly below this cluster volume)
                                 01 00 07
                                 02 08 06
                                 03 04 05

      8 Neighbors BELOW this cluster volume (XX is this cluster volume)
                                 11 10 17
                                 12 XX 16 (NOTE: Numerical value of XX is 18)
                                 13 14 15

      9 Neighbors ABOVE this cluster volume (28 is directly above this cluster volume)
                                 21 20 27
                                 22 28 26
                                 23 24 25
   */
   NICProberServerToServer* neighbors[NEIGHBOR_LST_SIZE];

};

} //namespace Aftr

/** \} */

#endif //#ifdef AFTR_CONFIG_USE_TNL
