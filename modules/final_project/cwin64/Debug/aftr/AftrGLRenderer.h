#pragma once
#include "AftrGLRendererBase.h"
#include "VectorFwd.h"

namespace Aftr
{

class AftrFrameBufferObject;
class IndexedGeometryQuad;
class WO;
class Camera;

class AftrGLRenderer : public AftrGLRendererBase
{
public:
   static AftrGLRenderer* New();
   virtual ~AftrGLRenderer();

   /**
      Invokes either renderSingular() (monoscopic camera using double buffering (one viewpoint)) or
      renderStereo() (stereoscopic camera using quad buffering (two viewpoints (right/left eyes))).
      After the above invocation completes, this method swaps the buffers displaying the
      newly generated frame to the screen.
      The camera's update methods may be invoked. These include methods like Camera::updateViewMatrix,
      Camera::updateProjectionMatrix, Camera::updateFrustumNormals, Camera::update, etc. However,
      after the camera is setup, it will be a const Camera& into the actual renderScene(...) method.
   */
   virtual void render( Camera& cam, WorldContainer& wList );
	
   /**
      Draws all WO* within the worldLst; typically called from 
      renderSingular() or renderStereo() or an FBO render.

      Draws all objects contained in wList from the perspective of cam. All objects are drawn into which
      ever buffer is currently bound. This could be the GL_BACK_BUFFER, a GL Texture bound via an FBO,
      or any other valid buffer object.
   */
   virtual void renderScene( const Camera& cam, WorldContainer& wList, bool clearColorDepthStencilBuffersPriorToRender = true );

   /**
      Called by render when rendering the world using stereoscopic mode (3D goggles).
      Computes asymmetric stereoscopic frustum.
      Invokes setUpStereoCamera() for right eye, calls renderScene() for right eye.
      Invokes setUpStereoCamera() for left eye, calls renderScene() for left eye.
   */
   virtual void renderStereo( Camera& cam, WorldContainer& wList ); ///< Invokes setUpStereoCamera then invokes renderScene twice, once for right eye, once for left

   /**
      Called by render when rendering the world in non-stereoscopic mode (no 3D goggles).
      Invokes setUpSingleCamera() and then invokes renderScene().
   */
   virtual void renderSingular( Camera& cam, WorldContainer& wList );
   
   /**
      Updates the camera's position and frustum culling information.
      Sets up OpenGL Projection / Modelview matrices based on camera pose.
      This is for non-stereoscopic rendering (ie, no 3D goggles)
   */
   //virtual void setUpSingleCamera( Camera* cam ); //uses AftrGLRendererBase::setUpSingleCamera
   
   /**
      Updates the camera's position and frustum culling information.
      Positions the camera properly for either the right or left eye.
      Sets up OpenGL Projection / Modelview matrices based on input params
      and camera pose.
      This is for stereoscopic rendering (ie, using 3D goggles on a 3D display)
   */
   virtual void setUpStereoCamera( float left, float right, float bottom, float top, 
                                   float Near, float Far, bool righthandCamera, 
                                   float eyeSeperationDist,  Camera& cam  );

   /**
     Renders for stereo modes that require each pair of frames to be spliced either vertically or horizontally 
   */
   virtual void renderSplit( Camera& cam, WorldContainer& wList );

   /**
      Generates 1 frame that contains the left eye image on the left half of the screen, and the right eye image on the right side of the screen.
   */
   virtual void renderSplitVertically( Camera& cam );

   /**
      Generates 1 frame that contains the left eye image on the bottom half of the screen, and the right eye image on the top half of the screen.
   */
   virtual void renderSplitHorizontally( Camera& cam );


   /**
      Methods that perform selection. The scene is rendered via selection to identify a WO or point selected from a mouse click or other
      event.
   */
   //virtual void renderSelection( Camera& cam, WorldContainer& wList );
   virtual void renderSelection( Camera& cam, WorldContainer& wList, SelectionQueryResult& queryResult, unsigned int pixelX, unsigned int pixelY );
   virtual void renderSelectionSingular( Camera& cam, WorldContainer& wList );
   virtual void renderSelectionScene( const Camera& cam, WorldContainer& wList, bool clearColorDepthStencilBuffersPriorToRender = true );


protected:
   AftrGLRenderer();
   virtual void onCreate();

   //stereoscopic information - maybe should be per camera?
   float eyeSeparationDistanceInCM;///< Half the distance, in cm, between the eyes used in stereoscopic equations
   float stereoscopicProjectionPlaneDistance;///< Distance to the stereoscopic projection plane

   //void initializeStereoFrameBuffers();
   AftrFrameBufferObject* leftOrBottomStereoFBO;
   IndexedGeometryQuad* leftOrBottomStereoQuad;
   AftrFrameBufferObject* rightOrTopStereoFBO;
   IndexedGeometryQuad* rightOrTopStereoQuad;

};

} //namespace Aftr
