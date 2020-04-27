#ifdef AFTR_CONFIG_USE_BOOST

#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include "NetMsg.h"
#include "NetMessengerStreamBuffer.h"

using namespace Aftr;

template< typename T >
NetMessengerServerUDPConnT<T>::NetMessengerServerUDPConnT( boost::asio::io_context& io_context, 
                     std::shared_ptr< NetMessengerMessageQueueT<T> > servListenerRecvQueue, 
                     unsigned short port,
                     std::function< std::optional<std::vector<T>>( uint8_t*, size_t) > createTFunc ) :
                     udpSock( io_context, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), port ) ),
                     //recvQueue( servListenerRecvQueue ),
                     createTFunc( createTFunc)
{
   this->signalShutdownAsyncReceive = 0;
   this->recvQueue = servListenerRecvQueue;
   this->IsStarted = false; // false until this->start() is invoked
   this->recvBuf = std::make_unique<uint8_t[]>( MAX_RECV_BUF_LEN );
   this->sendBuf = std::make_unique<uint8_t[]>( MAX_SEND_BUF_LEN );

   if( !this->udpSock.is_open() )
      std::cout << "UDP Socket failed to open...\n";
}

template< typename T >
NetMessengerServerUDPConnT<T>::~NetMessengerServerUDPConnT()
{
   this->signalShutdownAsyncReceive = 1;
   boost::system::error_code ec;
   this->udpSock.shutdown( boost::asio::basic_datagram_socket<boost::asio::ip::udp>::shutdown_type::shutdown_both, ec );
   if( ec )
   {
      std::cout << "ERROR: NetMessengerServerUDPConnT<T>::onRecvDatagram(...):\n"
                << "   " << ec.category().name() << ": " << ec.value() << std::endl;
   }
   this->udpSock.close();
   std::cout << "Waiting for asynReceiveDatagrame thread to terminate:";
   while( this->signalShutdownAsyncReceive != 2 )
      std::cout << ".";
   std::cout << "\n";
}

template< typename T >
void NetMessengerServerUDPConnT<T>::start()
{
   this->IsStarted = true;
   this->asyncReceiveDatagram();
}

template< typename T >
void NetMessengerServerUDPConnT<T>::asyncReceiveDatagram()
{
   this->udpSock.async_receive_from( boost::asio::buffer( this->recvBuf.get(), MAX_RECV_BUF_LEN ),
                                     this->ep,
                                     [this]( const boost::system::error_code& ec, std::size_t bytesReceived )
   {
      if( this->signalShutdownAsyncReceive == 1 )
      {
         std::cout << "Terminating thread asyncReceiverDatagram from within Lambda... " << AFTR_FILE_LINE_STR << "...\n";
         this->signalShutdownAsyncReceive = 2;
         return;
      }

      if( !ec && bytesReceived > 0 )
      {
         std::optional< std::vector<T> > datums = this->createTFunc( this->recvBuf.get(), bytesReceived );
         if( !datums )
            this->asyncReceiveDatagram(); // immediately receive more bytes if the creation function returned std::nullopt (avoids mutex locking)

         //std::cout << "type of datum is " << use meyer's book to output here
         auto recvQ = this->recvQueue.lock(); //convert weak_ptr to shared_ptr
         if( recvQ ) //ensure this pointer is still valid
         {
            recvQ->lock(); //critical section start
            for( size_t i = 0; i < datums->size(); ++i )
               recvQ->getQueue().push( std::move( (*datums)[i] ) );
            recvQ->unlock(); //critical section end
                             //std::cout << "Sleepin this thread..." << std::endl;
                             //boost::this_thread::sleep( boost::posix_time::seconds(10) );
                             //std::cout << "Woke up!..." << std::endl;
            this->asyncReceiveDatagram();
         }
         else
         {
            std::cout << "ERROR: NetMessengerServerUDPConnT was destroyed before the async recv thread was\n"
               << "shutdown! This should be impossible if this->signShutdownAsyncReceve is working properly\n"
               << "notify Scott Nykl that this has happened and show him this message:" << AFTR_FILE_LINE_STR << "...\n";
            this->signalShutdownAsyncReceive = 2;
            return;
         }
      }
      else if( ec && ec == boost::asio::error::message_size )
      {
         std::cout << "Message_size error " << AFTR_FILE_LINE_STR << "\n";
      }
      else
      {
         std::cout << "ERROR: NetMessengerServerUDPConnT<T>::onRecvDatagram(...):\n"
            << "   " << ec.category().name() << ": " << ec.value() << std::endl;
      }
   } );
}

//template< typename T >
//void NetMessengerServerUDPConnT<T>::onRecvDatagram( const boost::system::error_code& error, size_t bytesReceived )
//{
//   //std::cout << "Got header of length " << bytesReceived << "\n";
//   if( !error && bytesReceived > 0 )
//   {
//      //This socket just got a header, now this socket needs to receive the body of the message
//
//      NetMessengerStreamBuffer is( &this->recvBuf[0], (unsigned int) bytesReceived );
//
//      is >> this->currHeaderCode;
//      is >> this->currMsgLenBytes;
//
//
//      //Extract the payload from the datagram
//      NetMsg* msg = ManagerSerializableNetMsgMap::createInstance( this->currHeaderCode, is );
//      //delete[] this->recvBuf; this->recvBuf = nullptr; //no need to delete since this is the only UDP socket; destroy it on destruction
//      if( msg == nullptr )
//      {
//         std::cout << "NetMessengerServerUDPConnT<T>::onRecvBody()... Received bad header info... Server state may be corrupt...\n" 
//            << "received byte data is: " << is.toString() << std::endl;
//
//         //continue trying to read future messages even though an invalid message was received.
//         this->udpSock.async_receive_from( boost::asio::buffer( this->recvBuf, MAX_RECV_BUF_LEN ),
//            this->ep, 
//            boost::bind( &NetMessengerServerUDPConnT<T>::onRecvDatagram, this,
//            boost::asio::placeholders::error,
//            boost::asio::placeholders::bytes_transferred ) );
//
//         return;
//      }
//
//      msg->setAssociatedServerSession( nullptr );
//      //msg->setAssociatedServerUDPConn( this ); //return UDP packet will goto temporary ep where datagram originated not listener socket
//      //msg->setAssociatedEndPoint( this->ep ); //MAKE THIS WORK EVENTUALLY
//
//      //insert message into arrival queue and transfer ownership of the message to
//      //that queue. this arrival queue should be owned by the owning server listener.
//      //this way many listeners can exist at once and all messages remained sync'd with
//      //their corresponding originator
//      this->recvQueue->lock(); //critical section start
//      this->recvQueue->getQueue().push( msg );
//      this->recvQueue->unlock(); //critical section end
//      msg = nullptr; //recvQueue (owned by NetMessengerServerListener) now owns this message
//
//      this->udpSock.async_receive_from( boost::asio::buffer( this->recvBuf, MAX_RECV_BUF_LEN ),
//         this->ep, 
//         boost::bind( &NetMessengerServerUDPConnT<T>::onRecvDatagram, this,
//         boost::asio::placeholders::error,
//         boost::asio::placeholders::bytes_transferred ) ); 
//
//   }
//   else if( error && error != boost::asio::error::message_size )
//   {
//      //std::cout << "ERROR: NetMessengerServerUDPConnT<T>::onRecvDatagram(...):\n" 
//      //          << "   " << error.category().name() << ": " << error.value() << std::endl;
//      //delete this;
//      this->udpSock.async_receive_from( boost::asio::buffer( this->recvBuf, MAX_RECV_BUF_LEN ),
//         this->ep, 
//         boost::bind( &NetMessengerServerUDPConnT<T>::onRecvDatagram, this,
//         boost::asio::placeholders::error,
//         boost::asio::placeholders::bytes_transferred ) ); 
//   }
//   else
//   {
//      std::cout << "ERROR: NetMessengerServerUDPConnT<T>::onRecvDatagram(...):\n" 
//         << "   " << error.category().name() << ": " << error.value() << std::endl;
//
//      this->udpSock.async_receive_from( boost::asio::buffer( this->recvBuf, MAX_RECV_BUF_LEN ),
//         this->ep, 
//         boost::bind( &NetMessengerServerUDPConnT<T>::onRecvDatagram, this,
//         boost::asio::placeholders::error,
//         boost::asio::placeholders::bytes_transferred ) ); 
//   }
//}

//return UDP packet will goto temporary ep where datagram originated not listener socket
//bool NetMessengerServerUDPConnT<T>::sendNetMsgSynchronousUDP( const NetMsg& msg )
//{
//   NetMessengerStreamBuffer os( true );
//   msg.toStreamIncludingHeader( os );
//
//   boost::system::error_code error;
//   this->udpSock.send_to( boost::asio::buffer( (void*)os.getBuffer(), (size_t)os.getBufferLen() ), this->ep, 0, error );
//   if( error )
//   {
//      std::cout << "ERROR: boost::asio::write error at " << AFTR_FILE_LINE_STR << ". Error message is:\n" << error.message() << "\n";
//      return false;
//   }
//   return true;
//}

#endif
