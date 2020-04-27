#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include "tnlNetInterface.h"
#include "ConnClientGhost.h"
#include "ConnClientClusterGhost.h"
#include <vector>

namespace Aftr
{
   class NetSimulation;

/**
   \class NICAftrBase
   \author Scott Nykl 
   
   The NICAftrBase represents a virtual interface that contains all the connections
   of a specific IP:PORT for this instance. For example, if this is a server, this interface 
   will contain one connection to each client that is currently connected. If this is a 
   client, then the client will most likely have a single connection to the server.

   This class is also responsible for broadcasting/searching for local servers

    \{
*/
class NICAftrBase : public TNL::NetInterface
{
   typedef TNL::NetInterface Parent;

public: 

   /// Constructor for this network interface, called from the constructor for NetSimulation.
   /// The constructor initializes and binds the network interface, as well as sets
   /// parameters for the associated simulation and whether or not this is a server's interface.
   NICAftrBase( NetSimulation* theSim, const TNL::Address& bindAddress );
   virtual ~NICAftrBase();

   virtual std::string toString();

   /**
      Sends all pending data and then processes all packets that have arrived.
   */
   virtual void tick();

   /**
      Sends all pending data but does not touch/process any packets that have recently
      arrived. Useful when the user only wants to send all pending data relevant to
      all connections associated with this interface.
   */
   virtual void sendAllPendingData();

   /**
      Invoked within NetInterface::processPacket(...) when a packet is received that
      does not fall into the category of connection handshake or game data. For now,
      this includes packets related to searching for a simulation server to join.
      If this instance is a client, it pings for servers until one is found to connect to.
      If this instance is a server, it responds to ping packets from clients.
      More complicated games could maintain server lists, request game information
      and more.
    */
   virtual void handleInfoPacket( const TNL::Address& address, TNL::U8 packetType, TNL::BitStream* stream ) = 0;

   void logBytesRecvToFile();

   NetSimulation* getSimulation() { return this->sim; }

protected:

   /**
      Returns a string containing the exact class name this instance is of; not a parent class
      name. This method is used by the logBytesRecvToFile method so the log file is able
      to distinguish between the types of interfaces.
   */
   virtual std::string getInterfaceTypeString() = 0;

   virtual void logBytesRecv( TNL::U32 bytesRecv );
   unsigned int logIntervalStartTime;
   const static unsigned int logIntervalLengthInMS = 1000;
   std::vector< unsigned int > logOfBytesRecv;

   unsigned int pingDelayTime; ///< Milliseconds to wait between sending SearchingForServerRequest packets.

   /// Constants used within NICAftrBase
   enum Constants 
   {
      PingDelayTimeDefault = 2000, ///< Default number of milliseconds to wait between sending out pings to search for servers.
      SearchingForServerRequest = FirstValidInfoPacketId, ///< Signals a client searching for a server on the same LAN.
      SearchingForServerResponse,                         ///< Signals a server responding to a clients request for a local server.
      SearchingForServerClusterRequest,                   ///< Signals a cluster server/client searching for a server-cluster on the same LAN.
      SearchingForServerClusterResponse,                  ///< Signals a server in a server-cluster responding to a server/client cluster's request for a local server-cluster.
   };

   NetSimulation* sim;   ///< The game object associated with this network interface.

};

} //namespace Aftr

/** \} */

#endif //AFTR_CONFIG_USE_TNL
