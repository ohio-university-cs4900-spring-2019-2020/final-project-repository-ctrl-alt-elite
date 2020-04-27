/**
   \class ManagerOpenGLState
   \author Chad Mourning
   \brief A static manager object for the Aftr engine that mainstains and modifies OpenGLState variables for you.

   This manager ties into the state preservation mechanism that returns the state to the predetermined
   one between every top level object.  This manager, like all managers, is accessable from everywhere.
*/

#pragma once

#include "AftrOpenGLIncludes.h"
#include "AftrGlobals.h"
#include <stack>

namespace Aftr
{

enum class AFTR_GL_CONTEXT_PROFILE : unsigned char { COMPATIBILITY, CORE, ES, UNINITIALIZED };
std::ostream& operator<<( std::ostream& out, const AFTR_GL_CONTEXT_PROFILE& rhm );

enum class RENDER_HW_MODE : unsigned char;

void AFTR_GL_DebugMessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, 
                                  GLsizei length, const GLchar* message, void* userParam );

class ManagerOpenGLState
{
public:

   /**
      This function reverts the OpenGL state to the predetermined state (see state variables below).
      It is called between every top level object in the default GLView::render( const Camera& cam ).
      It is NOT called between every child of objects in WO or any engine WO subclass.
   */
   static void preserveState();

   static bool supportsFBO();
   static void setUnsupportedFunctionsToStubs();

   ///If true glEnable(GL_BLEND) in preserve state, otherwise glDisable(GL_BLEND)
   static bool blend;
   ///If true glEnable(GL_DEPTH_TEST) in preserve state, otherwise glDisable(GL_DEPTH_TEST)
   static bool depth_test;
   ///If true glEnable(GL_TEXTURE_2D) in preserve state, otherwise glDisable(GL_TEXTURE_2D)
   static bool texture_2d;
   ///If true glEnable(GL_FOG) in preserve state, otherwise glDisable(GL_FOG)
   static bool fog;
   ///If true sets the global ambient lighting to ManagerOpenGLState::globalAmbientValues, otherwise sets them to the default values
   static bool globalAmbient;
   ///If fog is true use this fog mode, otherwise ignored
   static GLenum fog_mode;
   ///If fog is true use this fog color, otherwise ignored
   static GLfloat fog_color[4];
   ///If fog is true use this fog density, otherwise ignored
   static GLfloat fog_density;
   ///If fog is true use this fog hint, otherwise ignored
   static GLenum fog_hint;
   ///If fog is true use this fog start, otherwise ignored
   static GLfloat fog_start;
   ///If fog is true use this fog end, otherwise ignored
   static GLfloat fog_end;
   ///If globalAmbient is true then use these values for global ambient lighting, otherwise ignored
   static GLfloat globalAmbientValues[4];
   ///If true, frustum culling will be enabled and checked for each WO that has WO::useFrustumCulling set to true
   static bool enableFrustumCulling;
   ///If true, specularity color will be reset to front_material_specularity_color between every top level object
   static bool enableSpecularityColorPreservation; 
   ///If enableSpecularityColorPreservation is true, the specularity color is set to this.
   static GLfloat front_material_specularity_color[4];
   ///If true, specularity coefficient (shininess) will be set to front_material_specularity_coefficient
   static bool enableSpecularityCoefficientPreservation;
   ///If enableSpecularityCoefficientPreservation is true, specularity coefficient will be set to this
   static GLfloat front_material_specularity_coefficient;
   ///If true, and lighting is enabled GL_COLOR_MATERIAL is also enabled.  Otherwise GL_COLOR_MATERIAL is disabled.
   static bool color_material;
   

   /**
      Returns the machine-specific hardware supported render mode.
      This will be V
   */
   static RENDER_HW_MODE getRenderMode();

   //BEGIN_SCOTT
   static float vertFOV; ///< Vertical Field of view of the OpenGL Viewport

   /**This is the height and width around where the mouse clicks that will be recognized for selection*/
   static int PICK_AREA_REGION;
   /**the buffer that will hold the names of the selection hits*/
   static int NAME_BUFFER_SIZE;

   /**
     This then invokes reInitOpenGLState.
   */
   static void init();
   /// Resets Projection Matrix, Viewport aspect ratio, resets GL_BLEND and glColorMaterial to default
   static void reInitOpenGLState();
   //does the initialization for core compatibility for 3.1 forward compatible contexts -- based off 4.4 spec, may need fallbacks for profiles between 3.1 and 4.4
   static void reInitCore();
   //does the initialization the "old way" for legacy hardware
   static void reInitCompatibility();

   ///If lighting mode enabled no textures are drawn on Models (to better observe lighting), and red spheres are at light locations
   static bool lightingModeEnabled;
   ///if renderAsSelectionEnabled, then all calls to WO::render( const Camera& cam ) call model->renderSelection instead
   static bool renderAsSelectionEnabled;
   ///Mutator for the global ambient lighting values, default values are for default lighting
   static void setGlobalAmbientLighting( GLfloat red = 0.4f, GLfloat green = 0.4f, GLfloat blue = 0.4f, GLfloat alpha = 1.0f );

   /**The GL Clipping Plane valid is diameter of clipping plane*/
   static float GL_CLIPPING_PLANE;
   static float GL_NEAR_PLANE;

   //stack for controlling if dpeth testing is on
   static std::stack< bool > depthTestStack;
   static void pushDepthTestStack( bool enable );
   static void popDepthTestStack();

   //"stack" for z-biasing
   static int zBiasCounter;
   static void increaseZBias();
   static void decreaseZBias();

   static std::string toStringCurrentGLContextInfo();
   static std::string toString();

   static void setEnableGLDebugCallback( bool enableCallback );

   static void setGLContextInfo( AFTR_GL_CONTEXT_PROFILE contextProfile, int majorGLVersion, int minorGLVersion );
   static AFTR_GL_CONTEXT_PROFILE getGLContexProfile(); /// Returns enum class representing the current context's profile type (either core, compatibility, es, or uninitiailized)
   static bool isGLContextProfileVersion32orGreater(); ///< True if the current context is OpenGL 3.2 or later
   static bool isGLContextProfileVersion40orGreater(); ///< True if the current context is OpenGL 4.0 or later
   static bool isGLContextProfileCore(); ///< The current context must be 3.2 or greater for "core" profile to be defined
   static bool isGLContextProfileES(); ///< On a desktop, the current context must be  3.2 or greater for a core profile. Version 4.3 is where core matches GL ES 3.0
   static bool isGLContextProfileCompatibility(); ///< Always true if context if below 3.2. Otherwise, the environment variable
   static int getGLContextMajorVersion(); ///< Returns the current context's major version (ie, OpenGL 4.x, 3.x, 2.x, ...)
   static int getGLContextMinorVersion(); ///< Returns the current context's minor version (ie, OpenGL x.0, x.1, x.2, x.3, ...)
   static bool getHaltOnGLDebugMessageCallbackEvent(); ///< True iff conf file sets "gldebugmessagecallbackisenabledhaltoneachmessage" to true, causes a cin.get() 

protected:
   ///The default global ambient lighting values
   static GLfloat defaultGlobalAmbientValues[4];

   static GLint majorGLVersion;
   static GLint minorGLVersion;
   static AFTR_GL_CONTEXT_PROFILE glProfile;
   static bool haltOnGLDebugMessageCallbackEvent;
};

}

