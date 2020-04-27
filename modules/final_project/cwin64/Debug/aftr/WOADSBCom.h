#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include "WO.h"
#include "AftrSerialPortADSBCom.h"
#include "AftrSerialPortADSBComBinary.h"

namespace Aftr
{

//class AftrSerialPortGPSReceiver;

class WOADSBCom : public WO
{
public:
   static WOADSBCom* New( const std::string& radioRXCOMPort );
   virtual ~WOADSBCom();

   virtual void onUpdateWO();

   AftrADSBComMsg getLatestADSBMessage() const;

protected:
   WOADSBCom();
   virtual void onCreate( const std::string& radioRXCOMPort );
   virtual void onCreate( const std::string& gpsCOMPort, const std::string& altimeterCOMPort, const std::string& radioTXCOMPort );

   //AftrSerialPortADSBCom* ADSBComPort;
   AftrSerialPortADSBComBinary* ADSBComPort;
   //AftrSerialPortGPSReceiver* gpsComPort;

   AftrADSBComMsg ADSBMsg;

};


} //namespace Aftr

#endif
