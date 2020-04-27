#pragma once

/**
   This file controls all subsystems that are built into
   aftr.lib when compiling the engine. As a result, this
   determines all the functionality that modules created using
   the engine can provide.

   AftrBurner currently links against several different libraries.
   The majority of these libraries are optional; that is, they
   provide additional functionality such as sound (SDL_MIXER),
   broad image format support (SDL_IMAGE),
   networking (TNL), Cal3D Animated models (CAL3D), physics (ODE),
   and many others.

   The core library that the engine most heavily relies on is SDL.
   SDL provides AftrBurner with cross platform windowing, device input,
   and event handling. Removing the dependence on the core SDL libraries -
   SDL.lib and SDLmain.lib (libSDL.a and libSDLmain.a) would be difficult.
   As a result, this config file does not allow the core SDL lib to be
   removed.

   Below are preprocessor definitions which determine which libraries (and their corresponding
   code base within the engine source) are built at compile time.

   Naturally, linking against these libs means that you will need to include the
   corresponding header files in the include path.

   The required libs via SDL are:
      ".../lib/SDL.lib"
      ".../lib/SDLmain.lib"
      "opengl32.lib"
   The required dlls via SDL are:
      "../bin/sdl.dll"

   \author Scott Nykl
*/

#include "TempDefines.h" //this file contains preprocessor definitions for optional portions of the code

/**
If enabled via TempDefines.h, OpenGL will be polled for any errors
during each render. This method prints those errors and the corresponding
error number.
*/
#define AFTR_STRINGIZE_DETAIL(x) #x
#define AFTR_STRINGIZE(x) AFTR_STRINGIZE_DETAIL(x)
#define AFTR_FILE_LINE_STR (__FILE__ ":" AFTR_STRINGIZE(__LINE__))
//python refactor.py r "printOpenGLErrors\(( .*,.*)\);" "printOpenGLErrors(\1, AFTR_FILE_LINE_STR );

#ifdef WIN32
   #define AFTR_C_CALL __stdcall
#else
   #define AFTR_C_CALL 
#endif
//#define AFTR_C_CALL __stdcall


#define AFTR_CONFIG_USE_SDL2 //Used by every OS except the iPhone OS

/**
   When defined, this indicates the engine is being built for the iPhone.
   Some conditional code is compiled in this case. For example, the WOFlyer5Thruster,
   expects the 3 Joystick axes to be that of the iPhone accelerometer and compiles
   code which controls flyer movement via the accelerometers.
*/
//#define AFTR_CONFIG_USE_IPHONE

/**
   These two defines are mutually exclusive. One must be defined at all times. GLEW is the
   Open GL Extension Wrangler and is recommended for desktops and other non-embeded/mobile
   platforms. This also enables use of any program shaders, vertex shaders, fragment 
   shaders, etc...

   GLES is the Open GL Embedded Systems version for mobile platforms like the iPhone or Android.
   GLES does NOT support any program shaders, vertex shaders, fragment shaders, etc...
*/
#define AFTR_CONFIG_USE_OGL_GLEW
//#define AFTR_CONFIG_USE_OGL_GLES


/**
   When defined, this indicates the system has the CUDA SDK installed and will
   attempt to compile all .cu files.
*/
/* #undef AFTR_CONFIG_USE_CUDA */

/**
   When defined, this indicates the availability of the BOOST Library. This 
   library is used inside some numerical classes (for example, the Matrix class)
   to accelerate CPU-based computations (like CPU-based Matrix multiplies). This
   also indicates the entire boost library is available and being used by the 
   engine.
*/
#define AFTR_CONFIG_USE_BOOST

/**
   Enables usage of the Torque Network Library (TNL). This provides real time server-client 
   simulations and real time server cluster simulations.
   Most notably the NetSimulation and NetWO classes (as well as
   all the corresponding TNL virtual interfaces) use this library.
   
   The preprocessor definition, when defined, causes engine (and any module) to:
   Link against the following libs:
      ".../lib/tnl.lib"
      ".../lib/libtomcrypt.lib"
   Runtime Dynamically load (DLL):
      None
*/
/* #undef AFTR_CONFIG_USE_TNL */


/**
   Enables usage of the Open Dynamics Engine (ODE). This is a high fidelity rigid body
   Newtonian physics simulatior. All WOs implementing the IFaceWOODE interface have
   a corresponding ODE physics body that sets the graphical body accordingly.

   The preprocessor definition, when defined, causes engine (and any module) to
   Link against the following libs:
      ".../lib/ode.lib"
   Runtime Dynamically load (DLL):
      ".../bin/ode.dll"
*/
/* #undef AFTR_CONFIG_USE_ODE */


/**
   Enables usage of NVIDIA's PhysX physics engine.
*/
/* #undef AFTR_CONFIG_USE_NV_PHYSX */


/**
   Enables usage of SDL_LoadImage(...) supporting a many file formats such as .jpg,
   .png, .tiff, .gif, .bmp, etc. This is used internally by ManagerTexture::loadTexture().

   The preprocessor definition, when defined, causes engine (and any module) to
   Link against the following libs:
      ".../lib/SDL_image.lib"
   Runtime Dynamically load (DLL):
      ".../bin/SDL_image.dll"
      ".../bin/zlib1.dll"
      ".../bin/smpeg.dll"
      ".../bin/libtiff.dll"
      ".../bin/libpng.dll"
      ".../bin/jpeg.dll"
*/
#define AFTR_CONFIG_USE_SDL_IMAGE


/**
   Enables audio capabilities using SDL_mixer, including usage of SDL_MixChunk(...).

   The preprocessor definition, when defined, causes engine (and any module) to
   Link against the following libs:
      ".../lib/SDL2_mixer.lib"
   Runtime Dynamically load (DLL):
      ".../bin/SDL_mixer.dll"
      ".../bin/smpeg.dll"
*/
/* #undef AFTR_CONFIG_USE_SDL_MIXER */


/**
   Enables usage of AftrTCPSocket. This is used by the database IO,
   high scores IO, and question set from remote database stuff. Namely
   without this, DatabaseIOHighScores and DatabaseIOQuestionSet will
   not work.

   The preprocessor definition, when defined, causes engine (and any module) to
   Link against the following libs:
      ".../lib/Sockets.lib"
      "wsock32.lib" (Windows only)
   Runtime Dynamically load (DLL):
      None
*/
//#define AFTR_CONFIG_USE_SOCKETS


/**
   Enables usage of the Character Animation Library (CAL3D). This library
   provides very lifelike animated bipeds. Without this library, the
   ManagerCAL3DModelMultiplicity, WOCal3D, and MGLCal3D will not exist.

   The preprocessor definition, when defined, causes engine (and any module) to
   Link against the following libs:
      ".../lib/cal3d.lib"
   Runtime Dynamically load (DLL):
      None
*/
/* #undef AFTR_CONFIG_USE_CAL3D */


/**
   Enbles the usage of the Assimp model import library. This library provides
   the ability to load almost any type of model file under the sun.
*/
#define AFTR_CONFIG_USE_ASSIMP

/**
   Enables users to create WO's Model from a .3DS file.
   Without this library, the WO3DS and MGL3DS.

   The preprocessor definition, when defined, causes engine (and any module) to
   Link against the following libs:
      ".../lib/lib3ds-2_0.lib"
   Runtime Dynamically load (DLL):
      ".../lib3ds-2_0.dll"
*/
#define AFTR_CONFIG_USE_3DS

/**
   Enables use of the Geospatial Data Abstraction Library (GDAL).
   This is a unifying C/C++ API for accessing raster geospatial data,
   and currently includes formats like GeoTIFF, Erdas Imagine, Arc/Info
   Binary, CEOS, DTED, GXF, and SDTS. It is intended to provide efficient 
   access, suitable for use in viewer applications, and also attempts to 
   preserve coordinate systems and metadata. Python, C, and C++ interfaces
   are available. 
*/
#define AFTR_CONFIG_USE_GDAL

/**
   If AFTR_CONFIG_COLOR_FLOAT is enabled:
      AFTR_COLOR_TYPE is set to GLfloat
      AFTR_MAX_COLOR is set to 1

   If AFTR_CONFIG_COLOR_UNSIGNED_BYTE is enabled:
      AFTR_COLOR_TYPE is set to GLubyte
      AFTR_MAX_COLOR is set to 255
*/

//#define AFTR_CONFIG_COLOR_FLOAT
#define AFTR_CONFIG_COLOR_UNSIGNED_BYTE


/**
  Fonts and related objects are disabled if AFTR_CONFIG_USE_FONTS is not defined.
  Uses Free Type fonts in ./src/freetype-2.3.12. These fonts are being depricated
  in favor of the AFTR_CONFIG_USE_FREE_TYPE_GL_FONTS.
*/
/* #undef AFTR_CONFIG_USE_FONTS */

/**
  The new font system which renders text at a higher performing and a higher 
  quality. Each text object is placed in a VAO and is also rendered via a Signed
  Distance Map shader that offer better quality than traditional bitmaps, 
  especially when zoomed in. This is based on FreeType and freetype-gl data
  structures. This system is enabled if the below preprocessor directive is enabled, 
  otherwise it is disabled and not compiled.
  Uses Free Type fonts in ./src/freetype-2.5.5.
*/
#define AFTR_CONFIG_USE_FREE_TYPE_GL_FONTS

/**
   If AFTR_CONFIG_USE_OCULUS_RIFT_OVR is enabled, the Oculus Rift Virtual Reality
   Goggles will be compiled into the engine and can be used by modules. This 
   definition primarily provides a definition within the ManagerOVR,
   AftrGLRendererOVR, and WOOculusOVR classes.
   Modules will need to link against the OVR libs and both the engine and the
   modules will need to include the respective headers.
*/
/* #undef AFTR_CONFIG_USE_OCULUS_RIFT_OVR */

/**
   If AFTR_CONFIG_USE_OCULUS_RIFT_DK2 is enabled, the Oculus Rift Virtual Reality
   Goggles will be compiled into the engine and can be used by modules. This 
   definition primarily provides a definition within the ManagerOVR_DK2 and 
   AftrGLRendererOVR_DK2 classes.
   Modules will need to link against the OVR libs and both the engine and the
   modules will need to include the respective headers.
*/
/* #undef AFTR_CONFIG_USE_OCULUS_RIFT_DK2 */

/**
   If AFTR_CONFIG_USE_KEYLOK_DONGLE is enabled, an authorized KeyLok anti-piracy
   USB dongle must be inserted while AftrBurnerEngine is running. If the dongle is 
   removed, execution will pause until the USB dongle is reinserted.
   This must be enabled when shipping modules to external users.
*/
/* #undef AFTR_CONFIG_USE_KEYLOK_DONGLE */
