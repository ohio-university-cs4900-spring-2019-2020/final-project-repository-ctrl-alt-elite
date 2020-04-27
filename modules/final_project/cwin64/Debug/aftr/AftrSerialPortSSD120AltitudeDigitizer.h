#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST
#include "AftrSerialPort.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <queue>
#include <string>

namespace Aftr
{

class AftrSerialPortSSD120AltitudeDigitizer : public AftrSerialPort
{
public:
   static AftrSerialPortSSD120AltitudeDigitizer* New();
   virtual ~AftrSerialPortSSD120AltitudeDigitizer();

   bool hasUnreadData();
   std::string getLatestMessagePurgingOldData();

protected:
   AftrSerialPortSSD120AltitudeDigitizer();
   virtual void onCreate();
   virtual void start();
   virtual void onRecvData( const boost::system::error_code& error, size_t bytesReceived );

   bool HasUnreadData;
   boost::mutex qMutex; ///< Mutex which protects the queue
   std::queue< std::string > recvQueue; ///< Messages that have been received, but not read by application yet
};

} //namespace Aftr

#endif
