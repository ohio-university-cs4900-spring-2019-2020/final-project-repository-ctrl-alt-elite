#pragma once

#include "AftrConfig.h"
#include <string>
#include "SDL_video.h"

struct SDL_Surface;
struct SDL_Window;
struct SDL_SysWMinfo;


namespace Aftr
{

class Camera;

/**
   This manager initializes SDL and creates an SDL_Surface on which OpenGL can
   render to.
*/
class ManagerWindowing
{
public:
   static void init();
   static void shutdown();
   static void drawLoadingScreen();
   static bool windowExists() { return WindowExists; }
   static bool usingStereoscopicRendering() { return UsingStereoscopicRendering; }
   static bool usingStereoscopicRenderingSplitVertically() { return UsingStereoscopicRenderingSplitVertically; }
   static bool usingStereoscopicRenderingSplitHorizontally() { return UsingStereoscopicRenderingSplitHorizontally; }
   static int getScreenWidth(); ///< Returns the width, in pixels, of the currently bound buffer (FBO). If none is bound, the current width of the window is returned.
   static int getScreenHeight(); ///< Returns the height, in pixels, of the currently bound buffer (FBO). If none is bound, the current height of the window is returned.
   static int getWindowWidth(); ///< Returns width of window, in pixels. Use getScreenWidth() if potentially rendering into an FBO.
   static int getWindowHeight(); ///< Returns height of window, in pixels. Use getScreenHeight() if potentially rendering into an FBO.
   static int getMaxWindowWidth(); ///< Returns the maximum width this window can become (dependent on resolution at which program started)
   static int getMaxWindowHeight(); ///< Returns the maximum height this window can become (dependent on resolution at which program started)
   static SDL_Surface* getScreen();
   static bool resizeWindow( int newWidthInPixels, int newHeightInPixels );
   static void setCaption( const std::string& mainWindowCaption );
   static SDL_Window* getCurrentWindow();
   static std::string toString();
   static std::string toStringSDL_GL_Attributes();
   static std::string toStringSDL_Display_Attributes();
   /// Calls SDL_GetWMInfo specific to the current operating system and SDL Version to retrieve platform specific info
#ifdef WIN32
   static bool getSystemWindowManagerInfoViaSDL( SDL_SysWMinfo& outSysWM );
#endif

protected:

   static void setWindowIcon();

   static void drawLoadingScreenNonStereoCompatibility();
   static void drawLoadingScreenNonStereoGL32();

   static SDL_Window* sdlWindow;
   static SDL_GLContext sdlGLContext;

   static bool WindowExists;
   static bool UsingStereoscopicRendering;
   static bool UsingStereoscopicRenderingSplitVertically;
   static bool UsingStereoscopicRenderingSplitHorizontally;
   static unsigned int SDLVideoFlags; ///< Flags passed into SDL's SDL_SetVideoMode method (used during init and resize)
   static int windowWd;  ///< Viewport width in pixels
   static int windowHt;  ///< Viewport height in pixels
   static int maxWindowWd; ///< Maximum window width, this is width of the GL Buffer created for rendering
   static int maxWindowHt; ///< Maximum window height, this is the height of the GL Buffer created for rendering

};


} //namespace Aftr


