#pragma once

#ifdef AFTR_CONFIG_USE_TNL

#include "ConnClientGhost.h"

namespace Aftr
{
   class NetWO;

/**
   \class ConnClientClusterGhost
   \author Scott Nykl

   The ConnClientClusterGhost represents a connection on an interface between a server cluster
   and client joined into that server cluster.
   
   RPCs invoked from ConnClientClusterGhost are sent to exactly one destination. That means,
   the RPC is not "ghosted" to an instance on ALL clients. If the rpc is Server to Client (S2C)
   The data is sent only to that single client; no other clients "hear" that transmission.

   This is useful when a client or server wants to send data to exactly one destination, and not
   utilize the "ghosting" mechanism inside in the \see NetWO objects.

   \{
*/
class ConnClientClusterGhost : public ConnClientGhost
{
   typedef TNL::GhostConnection Parent;
public:

   /**
      TNL_DECLARE_NETCONNECTION is used to declare that ConnClientClusterGhost is a valid connection class to the
      TNL network system.
   */
   TNL_DECLARE_NETCONNECTION( ConnClientClusterGhost );


   /**
      Created in NICAftrBase::handleInfoPacket(...) when a client receives a ping
      response from a server. This will connect from a client to a server; hence, when a
      connection is created on a client, a corresponding connection is created on the server.      
   */
   ConnClientClusterGhost();

   /**

   */
   virtual ~ConnClientClusterGhost();

   /**
      onConnectTerminated is called when the connection request to the server
      is unable to complete due to server rejection, timeout or other error.
      When a ConnClientClusterGhost connect request to a server is terminated, the client's network interface
      is notified so it can begin searching for another server to connect to.
   */
   virtual void onConnectTerminated( TNL::NetConnection::TerminationReason reason, const char* rejectionString );

   /**
      onConnectionTerminated is called when an established connection is terminated, whether
      from the local or remote hosts explicitly disconnecting, timing out or network error.
      When a ConnClientClusterGhost to a server is disconnected, the client's network interface
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

protected:
   
};

} //namespace Aftr

/** \} */

#endif //AFTR_CONFIG_USE_TNL
