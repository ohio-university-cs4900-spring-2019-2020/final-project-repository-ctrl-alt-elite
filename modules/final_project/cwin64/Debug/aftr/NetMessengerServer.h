#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST
#include <boost/log/detail/asio_fwd.hpp>
//forward declare boost classes
namespace boost
{
   class thread;
   namespace asio
   {
      class io_context;
   }
}

namespace Aftr
{

class NetMessengerServerListener;


class NetMessengerServer
{
public:
   static NetMessengerServer* New();
   ~NetMessengerServer();
   void onUpdate();
   NetMessengerServerListener& getServerListener();
   boost::asio::io_context* getIOContext();
private:
   NetMessengerServer();
   void onCreate();
   void onUpdateRecvData();
   void onUpdateSendData();

   boost::asio::io_context* ioContext = nullptr; ///< Boost's cross platform interface with OS networking
   NetMessengerServerListener* serv = nullptr; ///< Message Server which listens on IP:PORT (ipv4 or ipv6)
   boost::thread* ioContextThread = nullptr; ///< Thread which handles async io
};


} //namespace Aftr

#endif //AFTR_CONFIG_USE_BOOST
