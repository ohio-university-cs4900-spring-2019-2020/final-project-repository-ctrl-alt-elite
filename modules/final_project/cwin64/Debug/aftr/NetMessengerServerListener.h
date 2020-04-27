#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST
#include <boost/asio.hpp>
#include "NetMessengerSessionContainer.h"
#include "NetMessengerMessageQueue.h"

namespace Aftr
{

class NetMessengerServerSession;
class NetMessengerServerUDPConn;

class NetMessengerServerListener
{
public:
   NetMessengerServerListener( boost::asio::io_context& io_context, unsigned short port );
   virtual ~NetMessengerServerListener();

   void handle_accept( NetMessengerServerSession* new_session, const boost::system::error_code& error );

   virtual NetMessengerSessionContainer& getSessions();
   virtual NetMessengerMessageQueue& getNewlyArrivedMsgs();

   unsigned short getUDPListenerPort() const;
   unsigned short getTCPListenerPort() const;

protected:
   boost::asio::io_context& ioService;
   boost::asio::ip::tcp::acceptor acceptor;

   //rename this member variable to something like currentNonStartedTCPConn;
   NetMessengerServerSession* currentNonStartedSession; ///< At any time there is always exactly 1 unstarted session 
                                                        ///< waiting to be started when a new connection is formed.
                                                        ///< On destruction, this must be deleted to avoid leaks.

   NetMessengerServerUDPConn* currentNonStartedUDPConn; ///< At any time there is always exactly 1 unstarted connection 
                                                        ///< waiting to be started when a new connection is formed.
                                                        ///< On destruction, this must be deleted to avoid leaks.



   //Collection of all active sessions, must be thread safe
   NetMessengerSessionContainer sessions;
   NetMessengerMessageQueue newlyArrivedMsgs;
};

} //namespace Aftr

#endif //boost
