#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include "NICAftrBase.h"

namespace Aftr
{
   class NetSimulation;

/**
   \class NICProberClientToServer
   \author Scott Nykl 
   
   The NICProberClientToServer 

    \{
*/
class NICProberClientToServer : public NICAftrBase
{
public: 

   /// Constructor for this network interface, called from the constructor for NetSimulation.
   /// The constructor initializes and binds the network interface, as well as sets
   /// parameters for the associated simulation and whether or not this is a server's interface.
   NICProberClientToServer( NetSimulation* theSim, const TNL::Address& bindAddress, const TNL::Address& pingAddr );
   virtual ~NICProberClientToServer();

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

   /// \return true if this client process is currently searching the LAN for a server
   bool isPingingForServers() { return this->IsPingingForServers; }

   /// Enables or disables this client process to search for a server on the local LAN segment
   /// \param true to enable client broadcasting to search for a server; false, to disable searching for a server
   void isPingingForServers( bool isPinging ) { this->IsPingingForServers = isPinging; }

protected:

   virtual std::string getInterfaceTypeString();
   
   bool IsPingingForServers;  ///< True if this is a client that is pinging for active servers.
   TNL::U32 lastPingTime;     ///< The last platform time that a SearchingForServerRequest was sent from this network interface.
   TNL::Address pingAddress; ///< Network address to ping in searching for a server.  This can be a specific host address or it can be a LAN broadcast address.
};

} //namespace Aftr

/** \} */

#endif //AFTR_CONFIG_USE_TNL
