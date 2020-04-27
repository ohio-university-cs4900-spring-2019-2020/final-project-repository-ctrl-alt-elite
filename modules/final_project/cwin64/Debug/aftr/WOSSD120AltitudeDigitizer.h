#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include "WO.h"

namespace Aftr
{

class AftrSerialPortSSD120AltitudeDigitizer;


class WOSSD120AltitudeDigitizer : public WO
{
public:
   static WOSSD120AltitudeDigitizer* New( const std::string& comPort );
   virtual ~WOSSD120AltitudeDigitizer();

   virtual void onUpdateWO();
   bool isConnectedToAltimeter();

   float getCurrentAltitude() { return this->correctedAltitude; }
   float getCurrentTemperature() { return this->temperature; }
   void setBarometricPressure( float pressure ) { this->barometricPressure = pressure; }

protected:
   WOSSD120AltitudeDigitizer( const std::string& comPort );
   virtual void onCreate();
   AftrSerialPortSSD120AltitudeDigitizer* comPort;

   float correctedAltitude; ///< current altitude
   float temperature; ///< current temp

   static const float DEFAULT_GROUND_PRESSURE; ///< Default for USA avionics is 29.92
   float barometricPressure; ///< Ground pressure for the current area, Athens, OH is 30.13

};

} //namespace Aftr

#endif
