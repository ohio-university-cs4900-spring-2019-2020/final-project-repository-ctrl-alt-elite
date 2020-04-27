#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include "NetMessengerMessageQueue.h"
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "NetMessengerStreamBuffer.h"
#include "NetMsg.h"


namespace Aftr
{

class NetMessengerServerUDPConn
{
public:
   NetMessengerServerUDPConn(boost::asio::io_context& io_context, NetMessengerMessageQueue* servListenerSendQueue, unsigned short port);
   virtual ~NetMessengerServerUDPConn();
   boost::asio::ip::udp::socket& getSocket() { return this->udpSock; }
   bool isStarted() { return this->IsStarted; }
   void start();
   void onRecvDatagram( const boost::system::error_code& error, size_t bytesReceived );

   ///bool sendNetMsgSynchronousUDP( const NetMsg& msg ); //return UDP packet will goto temporary ep where datagram originated not listener socket
   //bool enqueueMsgToSend( NetMsg* msg );

protected:
   boost::asio::ip::udp::socket udpSock;
   boost::asio::ip::udp::endpoint ep; //one new'd each time a datagram arrives; kept until message is destroyed

   //static const unsigned int HEADER_LEN_BYTES = 8; ///< Header length of a message in bytes (32-bits)
   static const unsigned int MAX_RECV_BUF_LEN = 65536; ///< Max size of a UDP Datagram
   static const unsigned int MAX_SEND_BUF_LEN = 65536; ///< Max size of a UDP Datagram
   char* recvBuf = nullptr;///< Recv Buff of size MAX_RECV_BUF_LEN, placed on heap
   char* sendBuf = nullptr;///< Recv Buff of size MAX_SEND_BUF_LEN, placed on heap

   bool IsStarted = false; ///< Initially set to false, gets set to True once this->start() has been invoked and async operations have begun

   unsigned int currHeaderCode; ///< Set by onRecvHeader, read by onRecvBody, indicates NetMsg subclass to instantiate
   unsigned int currMsgLenBytes; ///< Set by onRecvHeader, read by onRecvBody, indicates length of binary data for the current message

   //Thread safe queue of pending messages to send to endpoint associated with this session
   NetMessengerMessageQueue sendQueue;

   /**
      Pointer to corresponding NetMessengerServerListener's queue, which holds all newly
      received (and fully instantiated) messages until the engine processes their 
      callbacks (NetMsg::onMessageArrived()). The callback is invoked when then engine
      calls NetMessengerServer::onUpdate(), which is typically in the GLView::onUpdateWorld().
      This recvQueue is NOT owned by this instance, do not delete. This queue is actually
      owned by the corresponding NetMessengerServerListener which spawned this session's existence.
   */
   NetMessengerMessageQueue* recvQueue = nullptr;


};

} //namespace Aftr

#endif
