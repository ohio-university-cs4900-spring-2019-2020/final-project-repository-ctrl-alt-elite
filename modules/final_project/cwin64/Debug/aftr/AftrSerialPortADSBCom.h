#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST
#include "AftrSerialPortGeneralByteData.h"
//#include <boost/asio.hpp>
//#include <boost/thread.hpp>
#include <queue>
#include <string>
#include "AftrADSBComMsg.h"

namespace boost
{
   namespace system
   {
      class error_code;
   }
}

namespace Aftr
{

class AftrSerialPortADSBCom : public AftrSerialPortGeneralByteData
{
public:
   static AftrSerialPortADSBCom* New();
   virtual ~AftrSerialPortADSBCom();
   
   /**
      Returns true iff outMsg is updated to the latest valid unread packet. If no unread valid packet 
      exists, false is returned and the parameter is not modified.
   */
   bool getLatestUnreadPacket( AftrADSBComMsg& outMsg );

   virtual void sendADSBMsgAsync( const AftrADSBComMsg& msg );

   static void AftrSerialPortADSBComTEST(  const std::string& s );


protected:
   AftrSerialPortADSBCom();
   virtual void onCreate();
   virtual void start();
   virtual void onRecvData( const boost::system::error_code& error, size_t bytesReceived );

   /// hasUnreadPacket has validated the input to be in the correct format; this method
   /// verifies that the data is actually correct according to a summation checksum over
   /// the packet data.
   /// Returns true if a valid packet has been received. If true, newMsg is updated to hold
   /// the new data. If false, newMsg is NOT modified and false is returned.
   bool validateChecksum( const std::string& s, AftrADSBComMsg& newMsg );

   bool HasUnreadPacket;
   //AftrADSBComMsg lastCompleteMsg; ///< Stores that last fully received and checksummed received packet
   static const unsigned int MAX_ADSB_MSG_LEN = 40; ///< Max number of characters a message may be
   std::string latestIncompletePkt;
};

} //namespace Aftr

#endif
