/*
Includes some helpful include files. Don't include this in a header file because it will bloat each file that includes it.
Instead, only include this in .cpp files that need to know about these things.

TODO: Remove this file from the engine... No need to let user potentially bloat code by misuse of this...
*/

#pragma once

#include "SteamieConfig.h"
#include "SteamieSDLIncludes.h"

/**
   This file includes the proper OpenGL include files based on the current platform
   specific setting found in SteamieConfig.h. This file is helpful when an engine
   file needs to know what any GL type or function is (ie GLuint, etc), but does
   not want to include everything that is specified within Predefined.h.
   SteamieConfig.h must have the corresponding preprocessor
   directive defined for this file to include the aforementioned data.
*/
#include "SteamieOpenGLIncludes.h"

/**
   This file includes all ODE functions and STEAMiE related classes and functions
   that make use of ODE. SteamieConfig.h must have the corresponding preprocessor
   directive defined for this file to include the aforementioned data.
*/
#include "SteamieODEIncludes.h"

#include "SteamieGlobals.h"
#include "SteamieManagers.h"
#include "SteamieUtilities.h"

