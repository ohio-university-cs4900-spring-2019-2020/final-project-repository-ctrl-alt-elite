#pragma once

#include "AftrConfig.h"
#include "SDL.h"

namespace Aftr
{

class ManagerDeviceInput
{
public:
   static void init( int deviceIndex = 0);
   static void shutdown();

   static SDL_Joystick* getJoyStick();

   static void initJoystick( int deviceIndex ); ///< Finds and initializes any connection Joysticks (and iPhone Accelerometer)

protected:

   static SDL_Joystick* joyStick;

};

} //namespace Aftr

