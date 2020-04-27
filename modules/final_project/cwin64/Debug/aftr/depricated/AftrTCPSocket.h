#pragma once
#ifdef AFTR_CONFIG_USE_SOCKETS

#include <TcpSocket.h>
#include <ISocketHandler.h>
#include <string>

namespace Aftr
{

class AftrTCPSocket : public TcpSocket
{
public:
	AftrTCPSocket( ISocketHandler& h );
   virtual ~AftrTCPSocket();

	void OnRead();

   std::string getRecvData();

   long getTCPTimeOutInSec() { return this->TcpTimeOutThresholdInSeconds; }
   void setTCPTimeOutInSec( long TimeOutInSeconds ) { this->TcpTimeOutThresholdInSeconds = TimeOutInSeconds; }

protected:
   std::string recvData;

   /**
      Number of seconds a TCP connection to a remote database will wait
      for a connection, expected data, or any another anticipated event
      that should be received from the database.
      If this time elapses, the connection will be aborted and 
      DatabaseIOQuestions::receiveQuestions() will return false.
   */
   long TcpTimeOutThresholdInSeconds;
};

} //namespace Aftr
#endif //AFTR_CONFIG_USE_SOCKETS
