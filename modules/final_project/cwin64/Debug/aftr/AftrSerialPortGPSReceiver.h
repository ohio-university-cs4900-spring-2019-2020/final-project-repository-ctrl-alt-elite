#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST
#include "AftrSerialPortGeneralByteData.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <queue>
#include <string>

namespace Aftr
{

class GPSLLAMsg
{
public:
   GPSLLAMsg();
   virtual ~GPSLLAMsg();
   std::string toString() const;
   //std::string toStringNoChecksum() const;
   //unsigned int computeChecksum() const;

   double lat; ///< WGS 84 latitude (decimal value)
   double lng; ///< WGS 84 longitude (decimal value)
   float elevation; ///< Elevation, in meters, above WGS 84 ellipsoid
protected:
};

class AftrSerialPortGPSReceiver : public AftrSerialPortGeneralByteData
{
public:
   static AftrSerialPortGPSReceiver* New();
   virtual ~AftrSerialPortGPSReceiver();
   
   /**
      Returns true iff outMsg is updated to the latest valid unread packet. If no unread valid packet 
      exists, false is returned and the parameter is not modified.
   */
   bool getLatestUnreadPacket( GPSLLAMsg& outMsg );

   //virtual void sendADSBMsgAsync( const GPSLLAMsg& msg );

   static void AftrSerialPortGPSReceiverTEST(  const std::string& s );


protected:
   AftrSerialPortGPSReceiver();
   virtual void onCreate();
   virtual void start();
   virtual void onRecvData( const boost::system::error_code& error, size_t bytesReceived );

   virtual bool parseGGAString( const std::string& s, GPSLLAMsg& out );
   virtual bool validateMsgChecksum( const std::string& s );

   /// hasUnreadPacket has validated the input to be in the correct format; this method
   /// verifies that the data is actually correct according to a summation checksum over
   /// the packet data.
   /// Returns true if a valid packet has been received. If true, newMsg is updated to hold
   /// the new data. If false, newMsg is NOT modified and false is returned.

   bool HasUnreadPacket;
   //AftrADSBComMsg lastCompleteMsg; ///< Stores that last fully received and checksummed received packet
   static const unsigned int MAX_GPS_MSG_LEN = 150; ///< Max number of characters a message may be
   std::string latestIncompletePkt;
};

} //namespace Aftr

#endif
