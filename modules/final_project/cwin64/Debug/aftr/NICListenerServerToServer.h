#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include "NICAftrBase.h"
#include <set>

namespace Aftr
{
   class NetSimulation;

/**
   \class NICListenerServerToServer
   \author Scott Nykl

   All connections between server clusters are called ConnServerClusters. Each
   ConnServerCluster has exactly 2 end points. One of these end points is
   contained as a connection within a NICListenerServerToServer. The other end point
   is contained as a connection within a NICProberServerToServer. That is, each
   NICListenerServerToServer is associated with one or more NICProberServerToServer
   NICs, and each NICProberServerToServer is associated with exactly one
   NICListenerServerToServer.
   
   The NICListenerServerToServer represents the single virtual interface
   that each cluster server uses to listen for and connect with remote
   cluster servers. A cluster server has exactly one of these interfaces.
   This interface passively listens for probes from a NICProberServerToServer
   interface. Once this interface "hears" a probe from a NICProberServerToServer,
   this instance checks to see if:
    -# A connection to the remote server already exists
    -# A connection to the remote server is currently being established

    If any of the above are true, this server cluster is already associated
    with the remote server cluster and will ignore the probe.

    If all of the above are false, this NICListerServerToServer will send a
    unicast ping response to the source of the NICProberServerToServer and thus
    begin establishing a connection.

    Once an entire server cluster is fully "up" (initialized, running, and connected
    w/ all neighboring server clusters), this NICListerServerToServer should have
    N endpoints from N different NICProberServerToServer NICs on neighboring server
    clusters.

    For example, if a cluster farm has 4 server clusters which all are adjacent to
    each other, this instance shall contain 3 endpoints. That is, this NIC will have
    3 simulataneous connection coming into it; one from each neighboring server 
    cluster's NICProberServerToServer.

    Read the NetSimulation documentation associated with member variables 
    -# NetSimulation::nicSL
    -# NetSimulation::nicCL
    -# NetSimulation::nicCSC
    -# NetSimulation::nicSSC
    -# NetSimulation::neighbors

    Also read the docs on NICProberServerToServer.

    These will aid in painting a full picture of how server clusters operate.

    \{
*/
class NICListenerServerToServer : public NICAftrBase
{
public: 

   /**
      Instantiates a virtual interface used exclusively by a server cluster to listen
      for/communicate with neighboring server clusters. Read this class' documentation
      about all the details related to this interface.
      
      Each server cluster should contain exactly one of these interfaces.
   */
   NICListenerServerToServer( NetSimulation* theSim, const TNL::Address& bindAddress );
   virtual ~NICListenerServerToServer();

   virtual void tick();

   /**
      Invoked within NetInterface::processPacket(...) when a packet is received that
      does not fall into the category of connection handshake or game data. For now,
      this includes packets related to searching for a simulation server to join.
      If this instance is a client, it pings for servers until one is found to connect to.
      If this instance is a server, it responds to ping packets from clients.
      More complicated games could maintain server lists, request game information
      and more.
   */
   virtual void handleInfoPacket( const TNL::Address& address, TNL::U8 packetType, TNL::BitStream* stream );

protected:

   virtual std::string getInterfaceTypeString();

   /**
      How long a 'SearchingForServerClusterRequest' probe from a specific
      server will be ignored before reprocessing.
   */
   static const unsigned int RECENT_CONNECTION_REQUEST_TIMEOUT_MS = 2000;

   bool serverClusterRequestWasSentFromLocalHost( const TNL::Address& address );

   /**
      This method returns true if this cluster server's NICListenerServerToServer has already 
      established a connection with a NICProberServerToServer of cluster server at address. 
      
      This method will also return true if this NICListenerServerToServer has recently sent
      back a connection response to another NICProberServerToServer belonging to the SAME
      cluster server at address. This can happen when a remote server has more than
      one NICProberServerToServer interfaces, and each of those interfaces sends a broadcast
      that is receieved by this listener interface. When this happens, we only want
      the listener interface to respond to exactly ONE of the probes belonging to THAT
      remote server. Additionally, a timeout is associated with a prober. This means
      that if a probe is heard at t=0, when t=timeout, then another probe from that
      server will be processed; however, if a connection has been established from the
      first probe, then a connection will already be established, so a second connection
      will not form. If another probe is processed and no connection exists, then a
      response will be sent back.

      If the above two conditions are false, false is returned.
   */
   bool proberAlreadyContactedClusterServer( const TNL::Address& address );

   void updateRecentConnectionRequestList();
   /**
      First part of vector is Address that recently sent a 'SearchingForServerClusterRequest'.
      Second part of vector is the timestamp of when that address was initially received; that is,
      the number of ticks since SDL was initialized via SDL_GetTicks(), in milliseconds.
      
      After a time period of RECENT_CONNECTION_REQUEST_TIMEOUT_MS, we remove this address from the list.
   */
   std::vector< std::pair< TNL::Address, unsigned int > > recentConnectionRequests;



};

} //namespace Aftr

/** \} */

#endif //AFTR_CONFIG_USE_TNL
