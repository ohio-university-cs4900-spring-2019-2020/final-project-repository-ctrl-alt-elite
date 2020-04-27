#pragma once

#include "AftrConfig.h"

#include "SDL.h" // This is the core library on which Aftr is highly dependent

/// If this preprocessor directive is defined in AftrConfig.h, this library is included
#ifdef AFTR_CONFIG_USE_SDL_IMAGE
   #include "SDL_image.h"
#endif

/// If this preprocessor directive is defined in AftrConfig.h, this library is included
#ifdef AFTR_CONFIG_USE_SDL_MIXER
   #include "SDL_mixer.h"
#endif

/// Aftr-defined SDL Events. In SDL's eyes, these are "USER-defined" events.
/// These events are used in the GLView::startWorldSimulationLoop() to 
enum USER_SDL_EVENT { USRRESET = 0, USREXIT, USER_SDL_EVENT_COUNT };
