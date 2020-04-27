#pragma once

#include "WO.h"
#include "Mat4Fwd.h"
#include "OculusSDK/LibOVR/Src/OVR_CAPI_GL.h"

namespace Aftr
{

class WOOVR_DK2 : public WO
{
public:
   static WOOVR_DK2* New( const Vector& lengths, float lineWidthInPixels );
   virtual ~WOOVR_DK2();
   void setLineWidth( float lineWidthInPixels );   
   float getLineWidth();
   bool isOperational();
   Mat4 getOculusDisplayMatrix( bool includePosition = true ) const;
   Mat4 getOculusCameraPose() const;
   void getYawPitchRollinRadians( float& yawRad, float& pitchRad, float& rollRad );

   virtual void onUpdateWO();
   
protected:
   WOOVR_DK2();
   virtual void onCreate( const Vector& lengths, float lineWidthInPixels );
   WO* childBox = nullptr;

   ovrHmd hmd;
};


} //namespace Aftr