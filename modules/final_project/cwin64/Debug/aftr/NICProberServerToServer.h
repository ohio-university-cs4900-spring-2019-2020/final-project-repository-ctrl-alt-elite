#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include "NICAftrBase.h"

namespace Aftr
{
   class NetSimulation;

/**
   \class NICProberServerToServer
   \author Scott Nykl

   All connections between server clusters are called ConnServerClusters. Each
   ConnServerCluster has exactly 2 end points. One of these end points is
   contained as a connection within a NICListenerServerToServer. The other end point
   is contained as a connection within a NICProberServerToServer. That is, each
   NICListenerServerToServer is associated with one or more NICProberServerToServer
   NICs, and each NICProberServerToServer is associated with exactly one
   NICListenerServerToServer.
   
   The NICProberServerToServer is responsible for seeking out neighboring server
   clusters. If a cluster farm has N nodes, each cluster server should instantiate
   N-1 of these interfaces; that is, one instance to directly connect to this server
   cluster to each of the other server clusters within the cluster farm.

   Once the connection is established, the user will most likely only ever access
   the ConnServerCluster instances contained within this interfaces connection
   list. Because all NICProberServerToServer NICs have exactly one connection, the
   first element in the connection list will always contain the corresponding
   ConnServerCluster instance.

    \{
*/
class NICProberServerToServer : public NICAftrBase
{
public: 

   /**
      Instantiates a virtual interface used exclusively by a server cluster to actively
      search for/initiate communications with neighboring server clusters. 
      Read this class' documentation about all the details related to this interface.
      
      If an entire server cluster farm contains N nodes, each server cluster instance should
      instantiate N-1 of these objects. This way, this server has a direct connection to every
      other server cluster within the cluster farm.
   */
   NICProberServerToServer( NetSimulation* theSim, const TNL::Address& bindAddress, const TNL::Address& pingAddr );
   virtual ~NICProberServerToServer();

   virtual void sendPing();
   virtual void tick();

   /// Invoked within NetInterface::processPacket(...) when a packet is received that
   /// does not fall into the category of connection handshake or game data. For now,
   /// this includes packets related to searching for a simulation server to join.
   /// If this instance is a client, it pings for servers until one is found to connect to.
   /// If this instance is a server, it responds to ping packets from clients.
   /// More complicated games could maintain server lists, request game information
   /// and more.
   virtual void handleInfoPacket( const TNL::Address& address, TNL::U8 packetType, TNL::BitStream* stream );

   /// \return true if this client process is currently searching the LAN for server clusters
   bool isPingingForServers() { return this->IsPingingForServers; }

   /**
      Enables or disables this cluster server process to search for other server clusters on the local LAN segment
      \param true to enable this server cluster to begin broadcasting to search for other server clusters;
      false, to disable searching for a server.
   */
   void isPingingForServers( bool isPinging ) { this->IsPingingForServers = isPinging; }

   void setClusterServerID( unsigned int clusterServerID ) { this->clusterServerID = clusterServerID; }
   /**
      \return the cluster server ID of the server at the opposite end of the connection contained within this 
      NICProberServerToServer NIC.
   */
   unsigned int getClusterServerID() { return this->clusterServerID; }
   void setClusterVolumeBounds( Vector& max, Vector& min );
   Vector getVolumeMaxVert() { return this->volumeMaxVert; }
   Vector getVolumeMinVert() { return this->volumeMinVert; }

protected:

   virtual std::string getInterfaceTypeString();

   /**
      The cluster server ID of the server located at the opposite end of this 
      connection. Because all NICProberServerToServer NICs have exactly one 
      connection, we do not need to worry about any NICProberServerToServer
      having multiple clusterServerIDs.
   */
   unsigned int clusterServerID;
   Vector volumeMaxVert; ///< The Endpoint volume's maximum vertex (Quadrant 2)
   Vector volumeMinVert; ///< The Endpoint volume's minimum vertex (Quadrant 4)

   bool IsPingingForServers; ///< True if this is a client that is pinging for active servers.
   TNL::U32 lastPingTime;    ///< The last platform time that a SearchingForServerRequest was sent from this network interface.
   TNL::Address pingAddress; ///< Network address to ping in searching for a server.  This can be a specific host address or it can be a LAN broadcast address.
};

} //namespace Aftr

/** \} */

#endif //AFTR_CONFIG_USE_TNL
