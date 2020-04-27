#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include "NetMessengerMessageQueue.h"
#include <cstdint>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "NetMessengerStreamBuffer.h"
#include "NetMsg.h"
#include <functional>
#include <atomic>
#include <optional>


namespace Aftr
{

template< typename T >
class NetMessengerServerUDPConnT
{
public:
   using value_type = T;

   NetMessengerServerUDPConnT(boost::asio::io_context& io_context,
                              std::shared_ptr< NetMessengerMessageQueueT<T> > servListenerRecvQueue, 
                              unsigned short port,
                              std::function< std::optional< std::vector<T>>( uint8_t*, size_t )> createTFunc );
   virtual ~NetMessengerServerUDPConnT();
   boost::asio::ip::udp::socket& getSocket() { return this->udpSock; }
   bool isStarted() { return this->IsStarted; }
   void start();
   //void onRecvDatagram( const boost::system::error_code& error, size_t bytesReceived );
   void asyncReceiveDatagram();

   std::function< std::optional< std::vector<T> >( uint8_t*, size_t )> createTFunc;

   ///bool sendNetMsgSynchronousUDP( const NetMsg& msg ); //return UDP packet will goto temporary ep where datagram originated not listener socket
   //bool enqueueMsgToSend( NetMsg* msg );

protected:
   boost::asio::ip::udp::socket udpSock;
   boost::asio::ip::udp::endpoint ep; //one new'd each time a datagram arrives; kept until message is destroyed

   //static const unsigned int HEADER_LEN_BYTES = 8; ///< Header length of a message in bytes (32-bits)
   static constexpr unsigned int MAX_RECV_BUF_LEN = 65536; ///< Max size of a UDP Datagram
   static constexpr unsigned int MAX_SEND_BUF_LEN = 65536; ///< Max size of a UDP Datagram
   std::unique_ptr<uint8_t[]> recvBuf = nullptr;///< Recv Buff of size MAX_RECV_BUF_LEN, placed on heap
   std::unique_ptr<uint8_t[]> sendBuf = nullptr;///< Recv Buff of size MAX_SEND_BUF_LEN, placed on heap

   bool IsStarted = false; ///< Initially set to false, gets set to True once this->start() has been invoked and async operations have begun

   unsigned int currHeaderCode = 0; ///< Set by onRecvHeader, read by onRecvBody, indicates NetMsg subclass to instantiate
   unsigned int currMsgLenBytes = 0; ///< Set by onRecvHeader, read by onRecvBody, indicates length of binary data for the current message

   //Thread safe queue of pending messages to send to endpoint associated with this session
   NetMessengerMessageQueueT<T> sendQueue;

   /**
      Pointer to corresponding NetMessengerServerListener's queue, which holds all newly
      received (and fully instantiated) messages until the engine processes their 
      callbacks (NetMsg::onMessageArrived()). The callback is invoked when then engine
      calls NetMessengerServer::onUpdate(), which is typically in the GLView::onUpdateWorld().
      This recvQueue is NOT owned by this instance, do not delete. This queue is actually
      owned by the corresponding NetMessengerServerListener which spawned this session's existence.
   */
   std::weak_ptr< NetMessengerMessageQueueT<T> > recvQueue;

   /// When set to 0: Continue executing asyncReceiveDatagram() on separate thread as usual.
   /// This will continue listening and receiving UDP data.
   /// When set to 1: The main thread, such as within this object's destructor, sets this value to 1.
   /// This signals the receiver thread to halt execution. The main thread must wait until execution
   /// has completed and the thread is shutting down. When the receiver thread has finished using all
   /// resources and is terminating with no other modifications, signalShutdownAsyncReceive is set to
   /// 2.
   /// When set to 2: The receiver thread is shutting down or terminated, but no resources will be touched
   /// by this thread again.
   std::atomic< uint8_t > signalShutdownAsyncReceive = 0;


};

} //namespace Aftr
#include "NetMessengerServerUDPConnT.cpptemplate.h"

#endif
