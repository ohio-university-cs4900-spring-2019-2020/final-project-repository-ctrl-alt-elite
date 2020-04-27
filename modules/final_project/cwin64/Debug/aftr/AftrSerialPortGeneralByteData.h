#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST
#include "AftrSerialPort.h"
#include <queue>
#include <string>

namespace Aftr
{

   class AftrSerialPortGeneralByteData : public AftrSerialPort
   {
   public:
      static AftrSerialPortGeneralByteData* New();
      virtual ~AftrSerialPortGeneralByteData();

      bool hasUnreadData();
      virtual std::vector< char >* getNewlyReceivedData();///< Calling function owns data

   protected:
      AftrSerialPortGeneralByteData();
      virtual void onCreate();
      virtual void start();
      virtual void onRecvData( const boost::system::error_code& error, size_t bytesReceived );

      bool HasUnreadData = false;
      boost::mutex recvMutex; ///< Mutex which protects the recv buffer vector
      std::vector< char >* recvBufVec; ///< Messages that have been received, but not read by application yet
   };

} //namespace Aftr

#endif
