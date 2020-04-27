#pragma once

#ifdef WIN32
#define OVR_OS_WIN32
#endif //WIN32

#include "AftrOpenGLIncludes.h"
#include "OculusSDK/LibOVR/Src/OVR_CAPI_GL.h"
#include "Mat4Fwd.h"

namespace Aftr
{

/**
   This manager initializes the Oculus Rift's orientation and position tracking sensors.
*/
class ManagerOVR_DK2
{
public:
   static void init();
   static void shutdown();
   static std::string toString();
   static std::string toStringSensorState();   
   static ovrHmd getHMD();
   static Mat4 convertOculusSDKPoseToAftrMat4Pose( const ovrPosef& pose, bool includePositionIn4thColumn = true );

   static bool isReady() { return ManagerOVR_DK2::IsReady; }

protected:
   static ovrHmd hmd;
   static bool IsReady;
   static bool hasBeenInitialized;
};

} //namespace Aftr
