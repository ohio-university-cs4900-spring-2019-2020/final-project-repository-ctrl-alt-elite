#pragma once


#include <string>

//#include "AftrOpenGLIncludes.h"
//#include "OculusSDK/LibOVR/Src/OVR_CAPI_GL.h"
//#include "Mat4Fwd.h"

namespace Aftr
{

/**
   This manager initializes the Oculus Rift's orientation and position tracking sensors.
*/
class ManagerOVR
{
public:
   static void init();
   static void shutdown();
   static std::string toString();
   //static std::string toStringSensorState();
   //static ovrHmd getHMD();

   static bool isReady() { return ManagerOVR::IsReady; }

protected:
   static bool IsReady;
   static bool hasBeenInitialized;
};

} //namespace Aftr
