#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include "NICAftrBase.h"

namespace Aftr
{
   class NetSimulation;

/**
   \class NICListenerServerToClient
   \author Scott Nykl 
   
   The NICListenerServerToClient 

    \{
*/
class NICListenerServerToClient : public NICAftrBase
{
public: 

   /// Constructor for this network interface, called from the constructor for NetSimulation.
   /// The constructor initializes and binds the network interface, as well as sets
   /// parameters for the associated simulation and whether or not this is a server's interface.
   NICListenerServerToClient( NetSimulation* theSim, const TNL::Address& bindAddress );
   virtual ~NICListenerServerToClient();

   virtual void tick();

   /// Invoked within NetInterface::processPacket(...) when a packet is received that
   /// does not fall into the category of connection handshake or game data. For now,
   /// this includes packets related to searching for a simulation server to join.
   /// If this instance is a client, it pings for servers until one is found to connect to.
   /// If this instance is a server, it responds to ping packets from clients.
   /// More complicated games could maintain server lists, request game information
   /// and more.
   virtual void handleInfoPacket( const TNL::Address& address, TNL::U8 packetType, TNL::BitStream* stream );

protected:

   virtual std::string getInterfaceTypeString();

   /**
      How long a 'SearchingForServerClusterRequest' probe from a specific
      server will be ignored before reprocessing.
   */
   static const unsigned int RECENT_CONNECTION_REQUEST_TIMEOUT_MS = 2000;

   /**
      This method returns true if this cluster server's NICListenerServerToClient has already 
      established a connection with a NICProberClientToServer of cluster client at address.
      
      This method will also return true if this NICServerListener has recently sent
      back a connection response to another NICProberClientToServer belonging to the SAME
      cluster client at address. This can happen when a remote client has more than
      one NICProberClientToServer interfaces, and each of those interfaces sends a broadcast
      that is receieved by this listener interface. When this happens, we only want
      the listener interface to respond to exactly ONE of the probes belonging to THAT
      remote client. Additionally, a timeout is associated with a prober. This means
      that if a probe is heard at t=0, when t=timeout, then another probe from that
      client will be processed; however, if a connection has been established from the
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
