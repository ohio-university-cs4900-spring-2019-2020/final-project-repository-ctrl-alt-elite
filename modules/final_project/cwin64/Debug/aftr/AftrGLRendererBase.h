#pragma once

#include <string>
#include "GLSLUniformBlockDataStructs.h"
#include "GLSLUniformBlock.h"
#include "ManagerShader.h"
#include "VectorFwd.h"
#include <memory>

struct SDL_MouseMotionEvent;

namespace Aftr
{

class AftrFrameBufferObject;
class IndexedGeometryQuad;
class Camera;
class WorldContainer;
class WO;
class ModelMesh;
class SelectionQueryResult;

class AftrGLRendererBase
{
public:
   static AftrGLRendererBase* New();
   virtual ~AftrGLRendererBase();

   /**
      Invokes either renderSingular() (monoscopic camera using double buffering (one viewpoint)) or
      renderStereo() (stereoscopic camera using quad buffering (two viewpoints (right/left eyes))).
      After the above invocation completes, this method swaps the buffers displaying the
      newly generated frame to the screen.
      The camera's update methods may be invoked. These include methods like Camera::updateViewMatrix,
      Camera::updateProjectionMatrix, Camera::updateFrustumNormals, Camera::update, etc. However,
      after the camera is setup, it will be a const Camera& into the actual renderScene(...) method.
   */
   virtual void render( Camera& cam, WorldContainer& wList ) = 0;

   bool isUsingShadowMapping() const { return this->IsUsingShadowMapping; }
   void isUsingShadowMapping( bool enableShadowMapping );

   /**
      Allocates memory for shadow mapping, creates the FBO and Camera to perform shadow mapping.
      After this completes, generateShadowMap can fully execute and populate the UBOs in the 
      shaders pertaining to shadowSamplers and shadow mapping.
   */
   virtual void initShadowMapData();

   /**
      Creates a shadow map for one frame. The scene is rendered from light 0's perspective and
      stored in a texture accessed in the shader. This can be extended to multiple lights, but
      just generates shadows for light0 right now.

      Temporarily enables front face culling and glPolygonOffset with GL_POLYGON_OFFSET_FILL
   */
   virtual void generateShadowMap( const Camera& cam, WorldContainer& wList );

   /**
      Destroys this renderer's shadow map FBO, textures, and shadow map cameras. This info will get 
      recreated if ManagerLight::isUsingShadowMapping() is true AND generateShadowMap is invoked.

      A user may call this during run time after shadow mapping has been turned off to free the
      Texture memory on the graphics card and the CPU-side resources consumed by the shadow mapping
      algorithm.
   */
   virtual void freeShadowMapMemory();

   /**
      Returns the camera used during the generateShadowMap scene rendering. The user may change the
      near/far planes, FOV, or other parameters desired to manipulate the shadow map.
   */
   Camera& getShadowMapCamera() { return *this->shadowMapCam; }

   /**
      Called by render when rendering the world using stereoscopic mode (3D goggles).
      Computes asymmetric stereoscopic frustum.
      Invokes setUpStereoCamera() for right eye, calls renderScene() for right eye.
      Invokes setUpStereoCamera() for left eye, calls renderScene() for left eye.
   */
   virtual void renderStereo( Camera& cam, WorldContainer& wList ) = 0; ///< Invokes setUpStereoCamera then invokes renderScene twice, once for right eye, once for left

   /**
      Called by render when rendering the world in non-stereoscopic mode (no 3D goggles).
      Invokes setUpSingleCamera() and then invokes renderScene().
   */
   virtual void renderSingular( Camera& cam, WorldContainer& wList ) = 0;
   
   /**
      Draws all WO* within the worldLst; typically called from 
      renderSingular() or renderStereo() or an FBO render.

      Draws all objects contained in wList from the perspective of cam. All objects are drawn into which
      ever buffer is currently bound. This could be the GL_BACK_BUFFER, a GL Texture bound via an FBO,
      or any other valid buffer object.
   */
   virtual void renderScene( const Camera& cam, WorldContainer& wList, bool clearColorDepthStencilBuffersPriorToRender = true ) = 0;
   
   /**
      Updates the camera's position and frustum culling information.
      Sets up OpenGL Projection / Modelview matrices based on camera pose.
      This is for non-stereoscopic rendering (ie, no 3D goggles)
   */
   virtual void setUpSingleCamera( Camera& cam );

   //virtual void renderSelection( Camera& cam, WorldContainer& wList ) = 0;
   virtual void renderSelection( Camera& cam, WorldContainer& wList, SelectionQueryResult& queryResult, unsigned int pixelX, unsigned int pixelY ) = 0;
   virtual void renderSelectionSingular( Camera& cam, WorldContainer& wList ) = 0;
   virtual void renderSelectionScene( const Camera& cam, WorldContainer& wList, bool clearColorDepthStencilBuffersPriorToRender = true ) = 0;

   /**
      Called by renderSelection when using selection with a x,y coordinate.
      This method returns a WO* to the WO that was selected; NULL, otherwise.
      
      \return WO* The selected WO.
   */
   virtual WO* findLastSelectedWO( unsigned int pixelX, unsigned int pixelY, const Camera& cam, const WorldContainer& wList );
   virtual WO* findLastSelectedWO( const SDL_MouseMotionEvent& e, const Camera& cam, const WorldContainer& wList );
   virtual std::tuple<ModelMesh*, int > findLastSelectedModelMesh( unsigned int x, unsigned int y, const Camera& cam, WO* lastSelectedWO );

   /**
      Given that the:
         -# the (x,y) point passed in represents the window coordinates of the user click.
      This method returns the Global OpenGL World coordinate of where the intersection took place via the out only
      param outFoundCoord. Bool is returned if a coordinate was successfully computed; false, otherwise. If false is
      returned, no change was made to the out-only param.
      \param x The x-coordinate of the mouse click
      \param y The y-coordinate of the mouse click
      \param Vector& The Global OpenGL World Coordinate of the intersection point; If NULL is returned,
      \return true iff, Vector& outFoundCoord was properly updated; false, if no coordinate could be computed and outFoundCoord was not updated.
   */
   virtual bool findLastSelectedCoordinate( unsigned int x, unsigned int y, const Camera& cam, Vector& outFoundCoord );
   /**
      Used as a helper method for finding which child of a selected parent
      was actually clicked on. For example, the upper arm of the human.
   */
   virtual WO* matchWOAgainstPixelColor( WO* wo, GLubyte red, GLubyte green, GLubyte blue );


   virtual void captureNextFrame( bool captureNextFrame ) { this->CaptureNextFrame = captureNextFrame; }
   virtual bool captureNextFrame() { return this->CaptureNextFrame; }

   virtual void captureNextFrameToFile( bool captureNextFrameToFile ) { this->CaptureNextFrameToFile = captureNextFrameToFile; }
   virtual void captureNextFrameToFile( bool captureNextFrameToFile, const std::string& filenamePNGorBMP ) 
                            { this->CaptureNextFrameToFile = captureNextFrameToFile; this->captureFilename = filenamePNGorBMP; }
   virtual bool captureNextFrameToFile() { return this->CaptureNextFrameToFile; }

   virtual void onResizeWindow( int newWidthPixels, int newHeightPixels );

protected:
   AftrGLRendererBase();
   virtual void onCreate();

   //SCOTT: if something requires 3.2 it should be checked to be 3.2 compatable, I was going to do the assignment in the constructor, but I saw no default constructor existed
   //and the assignment operator was explicitly deleted.  I changed it to a pointer which is new'd in the constructor and deleted in the destructor.
   /// Requires OpenGL 3.2, uses a Uniform Block (so it must be initialized somewhere where a check can be made)
   std::unique_ptr< GLSLUniformBlockT< GLSLUniformBlockCameraTransforms > > uniformBlockCameraTransformsGL32 = nullptr;// = { "CameraTransforms", ManagerShader::getUniformBlockBindingCameraTransforms() };

   std::string captureFilename; ///< Sets filename of next frame to be captures. After this frame is captured, this string is reset to "" and must be set again by user

   bool CaptureNextFrame; ///< When true, ManagerFrameCapture will capture a frame during the next render
   bool CaptureNextFrameToFile; ///< When true, ManagerFrameCapture will capture a frame during the next render and write it to file


   //Shadow Mapping members, only used when shadow mapping is enabled
   GLuint depthTex = 0; ///< Texture used to store the depth buffer
   GLuint shadowFBO = 0; ///< FBO with attached depthTex texture (DEPTH) that renders the scene from the shadowMapCam's perspective (which gets placed and oriented at each light)
   unsigned int shadowMapSideLength = 8192; ///< Size of the shadow map texture (8192 @ 32 bpp requires 256 MB Texture memory), only allocated if shadow mapping is turned on
   Camera* shadowMapCam = nullptr; ///< Camera that gets placed at the position of each light and renders the scene
   bool shadowMappingIsInitialized = false; ///< If false, no memory is allocated to shadow mapping. Shadow mapping must be initialized before its use.
   bool IsUsingShadowMapping = false; ///< User may set this to true to initialize shadow mapping. If true and shadow mapping has not been initialized, it will be initialized.

};

} //namespace Aftr
