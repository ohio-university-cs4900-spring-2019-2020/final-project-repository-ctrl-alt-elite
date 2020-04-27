#pragma once

#include "AftrLogData.h"
#include "Vector.h"
#include "AftrLogDataMacroMethods.h"

namespace Aftr
{

class AftrLogDataMTiGSensor : public AftrLogData
{
public:
   AftrLogDataMacroDeclaration( AftrLogDataMTiGSensor );
   
   AftrLogDataMTiGSensor();
   AftrLogDataMTiGSensor( const VectorD& lla, float dispMat4x4[16], 
                             float altFt = 0, float temperature = 0,
                             double headLat = 0, double headLng = 0, float headAltFt = 0, 
                             unsigned int SDLTimeStamp = 0,
                             unsigned int XsensGPSSecSinceEpoch = 0, unsigned int XsensGPSusec = 0,
                             unsigned int sysGPSSecSinceEpoch = 0, unsigned int sysGPSusec = 0,
                             unsigned int udpSequenceNumber = 0 );

   virtual ~AftrLogDataMTiGSensor();

   void getDCMMatrix( float outDispMatrix4x4[16] );
   VectorD getLLA() { return lla; }
   void getLLA( double outLLA[3] );
   void getAltAndTemperature( float outAltAndTemperature[2] );
   unsigned int getUDPSequenceNumber() { return this->udpSequenceNumber; }
   
   float orient[16];
   VectorD lla;
   float altimeterAlt; ///< altitude in feet
   float altimeterTemperature;

   double headLat; ///< Latitude in decimal degrees of the head aircraft (ADSB Transmitter)
   double headLng; ///< Longitude in decimal degrees of the head aircraft (ADSB Transmitter)
   float headAltFt; ///< Altitude in feet of the head aircraft (ADSB Transmitter)

   unsigned int SDLTimeStamp; ///< SDLGet_Ticks() at time of data point creation

   unsigned int XsensGPSSecSinceEpoch; ///< XSens's reported value for number of seconds since Jan 6 00:00:00 1980 (GPS Time)
   unsigned int XsensGPSusec; ///< XSens's reported value for number of microsecond count beyond seconds since epoch (Xsens report)
   unsigned int sysGPSSecSinceEpoch; ///< System's reported value for number of seconds since Jan 6 00:00:00 1980 (GPS Time)
   unsigned int sysGPSusec; ///< Systems's reported value for number of microsecond count beyond seconds since epoch (System report)

   unsigned int udpSequenceNumber; ///< When transmitting a UDP stream, this logs the an application level sequence number enabling
                                /// a sender and receiver to compare exactly which messages were lost or received

protected:

};


} //namespace Aftr

