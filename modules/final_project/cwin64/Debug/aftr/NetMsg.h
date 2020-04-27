#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include "NetMessengerStreamBuffer.h"
#include "NetMsgMacroMethods.h"
#include <string>
#include <memory>

namespace Aftr
{

class NetMessengerServerSession;
class NetMessengerServerUDPConn;

/**
   Header info contains 8 bytes. The first 4 bytes compose an unsigned integer 
   indicating the message identifier. The second 4 bytes compose an unsigned 
   integer indicating the length of the body.
*/
class NetMsg
{
public:

   NetMsgMacroDeclaration( NetMsg );

   NetMsg();
   virtual ~NetMsg();
   /// Writes the entire message (header and body) to the output stream.
   /// The binary array in the stream is ready to be placed on the wire as an independent message.
   virtual bool toStreamIncludingHeader( NetMessengerStreamBuffer& os ) const;
   /// Writes the message body to the output stream.
   virtual bool toStream( NetMessengerStreamBuffer& os ) const;
   virtual bool fromStream( NetMessengerStreamBuffer& is );
   /// Invoked when this message has fully arrived at the remote end.
   /// This method must be invoked in the main thread which owns the OpenGL context.
   virtual void onMessageArrived() {};

   virtual std::string toString() const;

   /**
      When a message arrives and that NetMsg's corresponding NetMsg::onMessageArrived() is invoked,
      this method may be used to quickly enqueue a reply message to be executed on the sender side.
      An example of using this method is:

      void NetMsgCreateWO::onMessageArrived()
      {
         WO* wo = WO::New( "/models/cube.wrl" );
         wo->setPosition( Vector( xPos, yPos, zPos ) ); //<--- These values were sent from the sender to this instance
         wo->setLabel( "Created by IPC Net Msg" );
         ManagerGLView::getGLView()->getWorldContainer()->push_back( wo );

         NetMsgCreateWOReply* msg = new NetMsgCreateWOReply(); //<--- Craft a reply message in response to the sender's
         msg->woID = wo->getID();                              // original message.
         this->sendReply( msg );
      }

      By default, the reply message is transmitted using the same protocol that the original message used (TCP or UDP).
      A TCP reply relies on setAssociatedServerSession(...) being previously called with a valid NetMessengerServerSession.
      A UDP reply relies on setAssociatedUDPConn(...) being previously called with a valid NetMessengerServerUDPConn.

      This method takes ownership of the replyMsg and is responsible for freeing the memory. The user loses ownership
      upon calling this method. Do not assume the pointer is valid after invoking this method.
   */
   virtual bool sendReply( std::shared_ptr<NetMsg> replyMsg );

   /**
      Sets the server-side TCP session associated with this message.

      This method is only relevant when this message physically reside on the server and
      TCP is being used to transmit the messages.
      A server may have many concurrent sessions, each with a set of message exchanges.
      When a server receives a message, it associates the corresponding session with that
      message, so the message is able to easily reply back to the client which originally
      sent that message.

      If a client has many sessions to one or more servers, the client must ensure it
      properly maintains which messages originated from which sessions to reply back to
      the proper endpoints. The recommended way is for the client to create a 'client' class
      which wraps a socket (endpoint) and the socket's receive/send message operations. When
      the client receives a message in that 'client' class, the message gets associated with
      that 'client' (socket) via a setter.
   */
   void setAssociatedServerSession( NetMessengerServerSession* session );

   /////**
   ////   Sets the server-side TCP session associated with this message.

   ////   This method is only relevant when this message physically reside on the server and
   ////   TCP is being used to transmit the messages.
   ////   A server may have many concurrent sessions, each with a set of message exchanges.
   ////   When a server receives a message, it associates the corresponding session with that
   ////   message, so the message is able to easily reply back to the client which originally
   ////   sent that message.

   ////   If a client has many sessions to one or more servers, the client must ensure it
   ////   properly maintains which messages originated from which sessions to reply back to
   ////   the proper endpoints. The recommended way is for the client to create a 'client' class
   ////   which wraps a socket (endpoint) and the socket's receive/send message operations. When
   ////   the client receives a message in that 'client' class, the message gets associated with
   ////   that 'client' (socket) via a setter.
   ////*/
   //return UDP packet will goto temporary ep where datagram originated not listener socket
   ////void setAssociatedServerUDPConn( NetMessengerServerUDPConn* udpConn );

   /**
      Returns the session associated with this message. NULL if:
      1) no session is set
      2) this is NOT a TCP connection (ie, this NetMsg was sent via UDP)
      3) this is called on the client side

      This method is only relevant when this message physically reside on the server.
      A server may have many concurrent sessions, each with a set of message exchanges.
      When a server receives a message, it associates the corresponding session with that
      message, so the message is able to easily reply back to the client which originally
      sent that message.

      If a client has many sessions to one or more servers, the client must ensure it
      properly maintains which messages originated from which sessions to reply back to
      the proper endpoints. The recommended way is for the client to create a 'client' class
      which wraps a socket (endpoint) and the socket's receive/send message operations. When
      the client receives a message in that 'client' class, the message gets associated with
      that 'client' (socket) via a setter.
   */
   NetMessengerServerSession* getAssociatedServerSession();

   /////**
   ////   Returns the UDP connection on which this NetMsg Arrived. NULL if:
   ////   1) no udpConn was set during NetMsg Creation
   ////   2) this is NOT a UDP datagram (ie, this was sent via TCP stream)

   ////   This may be used within a NetMsg to send a quick reply
   ////*/
   //return UDP packet will goto temporary ep where datagram originated not listener socket
   ////NetMessengerServerUDPConn* getAssociatedServerUDPConn();

protected:
   NetMessengerServerSession* associatedServerSession = nullptr; ///< Used for TCP connections
   
   //return UDP packet will goto temporary ep where datagram originated not listener socket
   //NetMessengerServerUDPConn* associatedServerUDPConn = nullptr; ///< Used for UDP datagrams
};

} //namespace Aftr


#endif
