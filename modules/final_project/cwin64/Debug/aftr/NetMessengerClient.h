#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include <string>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace Aftr
{

class NetMsg;

class NetMessengerClient
{
public:
   static NetMessengerClient* New( const std::string& host = "127.0.0.1", const std::string& port = "12683" );
   virtual ~NetMessengerClient();
   virtual void onUpdate();

   /// Sends a message from this client to the client's specified end point (host:port).
   /// Any replies generated will be received by the NetMessengerServerListener.
   virtual void sendNetMsgSynchronousTCP( const NetMsg& msg );
   virtual NetMsg* sendNetMsgBlockForReplyTCP( const NetMsg& msg );

   virtual void sendNetMsgSynchronousUDP( const NetMsg& msg );
   virtual NetMsg* sendNetMsgBlockForReplyUDP( const NetMsg& msg );

   bool isTCPSocketOpen() const;
   bool reconnect();

   std::string getLocalIpAddressesStrings() const;
   std::vector< boost::asio::ip::udp::endpoint > getLocalIpAddresses();

   boost::asio::ip::udp::socket* getUDPSocket() { return this->udpSock; }
   boost::asio::ip::udp::endpoint& getUDPEndPoint() { return this->udpEp; }

   boost::asio::ip::tcp::socket* getTCPSocket() { return this->sock; }
   boost::asio::ip::tcp::endpoint& getTCPEndPoint() { return this->tcpEp; }

protected:
   NetMessengerClient( const std::string& host, const std::string& port );
   virtual void onCreate();

   std::string host = "";
   std::string port = "";
   boost::asio::io_context* ioService = nullptr; ///< Boost's abstraction layer to the OS
   boost::asio::ip::tcp::socket* sock = nullptr;
   boost::asio::ip::tcp::endpoint tcpEp;
   bool tcpSockIsConnected = false;
   boost::asio::ip::udp::socket* udpSock = nullptr;
   boost::asio::ip::udp::endpoint udpEp;
   char* recvBuff = nullptr;
   unsigned int BUFF_SIZE = 16384;

   void doBigStressTest();
   void doUDPTestMsgTest();
   void doUDPTest();
   void doUDPTestBig();
};



} //namespace Aftr

#endif //AFTR_CONFIG_USE_BOOST
