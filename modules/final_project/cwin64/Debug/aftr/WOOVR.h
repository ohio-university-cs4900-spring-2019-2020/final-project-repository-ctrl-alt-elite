#pragma once

#include "WO.h"
#include "Mat4Fwd.h"
#include "OVR_CAPI_GL.h"

namespace Aftr
{

   class AftrGLRendererOVR;

   /**
    This class is used to visualize the head mount device's pose relative to the global 
    coordinate frame in the 3DVW.
   */
class WOOVR : public WO
{
public:
   static WOOVR* New( const Vector& lengths, float lineWidthInPixels, const AftrGLRendererOVR* renderer = nullptr );
   virtual ~WOOVR();
   void setLineWidth( float lineWidthInPixels );   
   float getLineWidth() const;
   bool isOperational() const;
   Mat4 getOculusDisplayMatrix( bool includePosition = true ) const;
   Mat4 getOculusCalibratedOriginPose() const;
   Vector getYawPitchRollinRadians( const ovrQuatf& q ) const;

   std::string toString() const;

   static Vector toAftrGlobalFrameFromOVR( const ovrVector3f& p );
   static Mat4 toAftrGlobalFrameFromOVR( const ovrQuatf& q );

   virtual void onUpdateWO();
   
protected:
   WOOVR( const AftrGLRendererOVR* renderer );
   virtual void onCreate( const Vector& lengths, float lineWidthInPixels );
   WO* childBox = nullptr;
   WO* sensorFrustum = nullptr;

   const AftrGLRendererOVR* renderer = nullptr;

   long long frameIdx = 0;



   
};


} //namespace Aftr