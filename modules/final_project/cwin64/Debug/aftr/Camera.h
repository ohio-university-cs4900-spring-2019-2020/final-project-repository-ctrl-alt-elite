#pragma once

#include "WO.h"
#include "AftrGeometryFrustum.h"
#include "CameraViewport.h"
#include "Mat4.h"

namespace Aftr
{

class GLView;
class HandlerMouseState;

class Camera : public WO
{

public:
   Camera( GLView* glView, HandlerMouseState* mouseHandler );
   virtual ~Camera();

   Camera() = delete;
   Camera( const Camera& toCopy ) = delete;
   Camera& operator=( Camera& toAssign ) = delete;
   Camera& operator=( Camera&& toMove ) = delete;

   void setMouseHandler( HandlerMouseState* mouseHandler );
   HandlerMouseState* getMouseHandler();

   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseWheelScroll( const SDL_MouseWheelEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   virtual void moveInLookDirection();
   virtual void moveInLookDirection( float distance );
   virtual void moveOppositeLookDirection();
   virtual void moveOppositeLookDirection( float distance );
   virtual void moveLeft(); ///< Pans camera to the 'left' (along camera's local +y axis)
   virtual void moveRight(); ///< Pans camera to the 'right' (along camera's local -y axis)
   virtual void changeLookAtViaMouse( int deltaX, int deltaY );
   virtual void attachCameraToWO( WO* WOtoWatch, const Vector& globCoordOfIntersection );
   virtual void detachCameraFromWO();
   virtual float getDistFromJointToCam();
   virtual void setDistFromJointToCam( float distance );
   virtual void render( const Camera& cam ); ///< Renders the Camera's BoundingBox
   virtual void renderSelection( const Camera& cam ); ///< Can only select camera if its bounding box is visible
   virtual void onPhysicsEngineTick();
   virtual void update() = 0;
   virtual void setCameraVelocity( float velocityScalar );
   virtual float getCameraVelocity();
   virtual void setCameraLookAtPoint( const Vector& lookAtPoint );
   virtual void setCameraLookDirection( const Vector& lookDirection );
   virtual void setCameraNormalPoint( const Vector& normalPoint );
   virtual void setCameraNormalDirection( const Vector& normalDirection );
   virtual void setCameraMouseSensitivity( float mouseSensitivityDivider );
   virtual void startCameraBehavior();
   virtual void setActorToWatch( WO* actorToWatch );
   virtual WO* getActorToWatch();
   virtual void setCameraVerticalFOV( float vFOVDeg );
   virtual void setCameraHorizontalFOV( float hFOVDeg );
   virtual void setCameraAspectRatioWidthToHeight( float aspectRatioWidthToHeight );

   virtual void setCameraNearClippingPlaneDistance( float nearClippingPlaneDistance );
   virtual void setCameraFarClippingPlaneDistance( float farClippingPlaneDistance );
   /// Returns the vertical FOV in degrees
   float getCameraVerticalFOVDeg() const;
   /// Returns the horizontal FOV in degrees
   float getCameraHorizontalFOVDeg() const;
   float getCameraNearClippingPlaneDistance() const;
   float getCameraFarClippingPlaneDistance() const;
   float getCameraAspectRatioWidthToHeight() const;

   virtual void setCameraAxisOfHorizontalRotationViaMouseMotion( const Vector& currentSceneUpVector );
   virtual Vector getCameraAxisOfHorizontalRotationViaMouseMotion() const;

   /**
      This method lets the user specify an additional rotation matrix to 
      concatenate with the camera's current display matrix. This is performed
      within Camera::updateViewMatrix() before generating the current view matrix.
      It is specified in same space as the model's display matrix.

      This is useful for example, when using the Oculus Rift. In this way,
      the mouse still controls motion; however, the additional yaw,pitch,
      roll of the Oculus may be passed in to this method, each frame,
      enabling the Oculus' inertial units to control the head motion of 
      the camera.

      The use of this in passed direction cosine matrix (dcm) is enabled
      or disabled via the corresponding boolean argument.
   */
   virtual void setCameraViewMatrixAdditionalRotationWithTranslationTransformMat( bool applyWithinUpdateViewMatrix,
                                                                                  const float dcm4x4[16] );
   
   virtual Vector getCameraLookAtPoint() const;


   /**
      \returns A normalized Vector pointing in the direction the camera is
      currently looking. This is generating by taking the current camera's
      lookAt point and creating a normalized vector between that point and
      the camera's current position.
   */
   virtual Vector getLookDirection() const;

   /**
      Invokes and returns the Vector generated by Camera::getCameraNormal()
      \return The Camera's mathematical normal vector based on the current
      orientation of the camera.
   */
   virtual Vector getNormalDirection() const;

   /**
      Changes this object's relative horizontal offset by delaTheta.
      Mathematically, this method rotates this object's joint transform matrix
      deltaTheta radians about the relative positive z-axis.
      This is equivalent to the pitch.

      \param deltaTheta Radian angle by which this object shall be rotated about
      its relative +z-axis. This is equivalent to the pitch.
   */
   virtual void changeOrientationWRTparentDeltaTheta( float deltaTheta );

   /**
      Changes this object's relative vertical offset by deltaPhi.
      Mathematically, this method rotates this object's joint transform matrix
      deltaPhi radians about the relative positive y-axis.
      This is equivalent to the yaw.

      \param deltaPhi Radian angle by which this object shall be rotated about
      its relative +y-axis. This is equivalent to the yaw.
   */
   virtual void changeOrientationWRTparentDeltaPhi( float deltaPhi );

   /**
      Changes this object's relative roll offset by deltaRoll.
      Mathematically, this method rotates this object's joint transform matrix
      deltaRoll radians about the relative positive x-axis.

      \param deltaRoll Radian angle by which this object shall be rotated about
      its relative +x-axis.
   */
   virtual void changeOrientationWRTparentDeltaRoll( float deltaRoll );

   /**
      This method updates this camera's viewing frustum which is used by the
      GLView during a render for frustum culling of objects outside of the
      viewing frustum.
      This update method should be invoked AFTER the camera's update() method
      finishes execution; otherwise, the camera's normal and lookDirection vectors
      may be out of day causing inaccurate frustum culling of a scene.
   */
   void updateFrustumNormals();

   /// Returns a reference to the current view frustum. Call Camera::updateFrustumNormals()
   /// to update the frustum based on the current camera position/orientation.
   /// This frustum is defined in World Space (not object space).
   const AftrGeometryFrustum& getAftrGeometryFrustum() const { return this->frustum; }
   
   /// Assumes 0,0 is lower left corner of the screen
   /// Returned Vector is normalized
   Vector getVectorFromCamToNearPlanePixel( unsigned int pixelX, unsigned int pixelY );


   /// Returns a reference to the current viewport used by this camera
   CameraViewport& getCameraViewport() { return this->viewportInfo; }
   const CameraViewport& getCameraViewport() const { return this->viewportInfo; }

   CameraViewport getCameraViewportCopy() const { return this->viewportInfo; }

   /// Set's the camera's current viewport to a copy of the in passed reference
   void setCameraViewport( const CameraViewport& v );

   /**
      Updates the camera's internal view matrix based on the camera's current lookAtPoint, position,
      and normal direction. This method is the same as gluLookAt(...) except it does not modify any
      OpenGL state and the resultant matrix is stored internally as this Camera's View Matrix.

      Typical usage of this method is:
      cam->updateViewMatrix();
      glMatrixModel( GL_MODELVIEW );
      glLoadIdentity();
      glMultMatrixf( cam->getCameraViewMatrix() );


      cam->updateViewMatrix() generates the same matrix as 'theViewMatrix' shown the following code 
      (except this method modifies no OpenGL code):

      glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();
      gluLookAt( cameraPosition, cameraLookAtPoint, cameraNormal );
      glGetFloatv( GL_MODELVIEW, theViewMatrix );
   */
   void updateViewMatrix();

   /**
      Returns the current View matrix stored in this camera instance. To update the View
      matrix using the current state of this instance, invoke Camera::updateViewMatrix().
      This method does not modify any OpenGL state.

      This is useful in cases where a nested child needs to render its orientation
      relative to the camera but at a position relative to the parent. For example,
      the billboards may want to use this in certain circumstances. A shader may also
      want the view matrix instead of the MODELVIEW matrix in some cases.
   */
   Mat4 getCameraViewMatrix() const;
   Mat4D getCameraViewMatrixD() const;

   /**
      Same as Mat4 getCameraViewMatrix(); just a different return type.
   */
   template< typename T >
   void getCameraViewMatrix( T outMatrix[16] ) const;

   
   void setCameraViewMatrix(const float v[16]) ;

   /**
      Matrix inverse functions.
   */
   template< typename T >
   void getCameraProjectionMatrixInverse( T outMatrix[16] ) const;
   template< typename T >
   void getCameraViewMatrixInverse( T outMatrix[16] ) const;
   template< typename T >
   void getCameraProjectionViewMatrixInverse( T outMatrix[16] ) const;

   /// Returns normal for the ith plane [0,5]. These normals point out from the interior the view frustum.
   /// top, bottom, left, right, near, far corresponding to indices 0,1,2,3,4,5, respectively.
   /// These normals are defined in World Space (not object space).
   Vector getFrustumPlaneNormal( unsigned int i ) const;
   /// Returns distance from origin along normal for ith plane [0,5].
   /// top, bottom, left, right, near, far corresponding to indices 0,1,2,3,4,5, respectively.
   /// These coefficients are defined in World Space (not object space).
   float getFrustumPlaneCoef( unsigned int i ) const; ///< Returns distance from origin along normal for ith plane [0,5].
   std::string getFrustumToString() const;

   /**
      Updates this camera's internal projection matrix based on the camera's current 
      fovy, aspectRatioWidthToHeight, nearClippingPlane, farClippingPlane. This performs
      the same calculation as a call to aftrGluPerspective(...). This does not 
      modify any OpenGL state.

      Typical usage of this method is:
      cam->updateProjectionMatrixUsingPerspectiveProjection();
      glMatrixModel( GL_PROJECTION );
      glLoadIdentity();
      glMultMatrixf( cam->getCameraProjectionMatrix() );
      
   */
   void updateProjectionMatrixUsingPerspectiveProjection();
   void updateProjectionMatrixUsingPerspectiveProjection_ReversedZHighPrecDepth();
   void updateProjectionMatrixUsingOrthographicProjection();

   /**
      This method references this instances PROJ_MATRIX_PROJ_TYPE camProjectionType variable.
      If this variable is Perspective, a call to Camera::updateProjectionMatrixUsingPerspectiveProjection()
      is performed. If this variable is Orthographic, a call to Camera::updateProjectionMatrixUsingOrthographicProjection().
   */
   void updateProjectionMatrix();

   /**
      A convenience method that updates the view matrix, projection matrix, and frustum information.
      Equivalent to calling these 3 methods individually.
            cam->updateFrustumNormals();
            cam->updateProjectionMatrix();
            cam->updateViewMatrix();
      This is generally called immediately before the camera matrices are passed to Shader Programs / GL for
      rendering.
   */
   virtual void updateAllMatriciesAndFrustumInfo();

   enum class PROJ_MATRIX_PROJ_TYPE : unsigned char { pmptPERSPECTIVE = 0, pmptORTHOGRAPHIC };
   void setCameraProjectionType( const PROJ_MATRIX_PROJ_TYPE& projType );
   PROJ_MATRIX_PROJ_TYPE getCameraProjectionType() const { return this->camProjectionType; }
   void setCameraProjectionMatrix( const float p[16] );
   
   /**
      Returns the current Projection matrix stored in this camera instance. To update the Projection
      matrix using the current state of this instance, invoke Camera::updateProjectionMatrixUsing*()
      methods.
   */
   const Mat4& getCameraProjectionMatrix() const;
   Mat4D getCameraProjectionMatrixD() const;

   /// Returns the current perspective projection matrix regardless of whether the camera's projection type is set to perspective or orthographic
   const Mat4& getCameraPerspectiveProjectionMatrix() const;
   /// Returns the current orthographic projection matrix regardless of whether the camera's projection type is set to perspective or orthographic
   const Mat4& getCameraOrthographicProjectionMatrix() const;
   /// Sets the current perspective projection matrix regardless of whether the camera's projection type is set to perspective or orthographic.
   void setCameraPerspectiveProjectionMatrix( const Mat4& perspectiveProjMat );
   /// Sets the current orthographic projection matrix regardless of whether the camera's projection type is set to perspective or orthographic
   void setCameraOrthographicProjectionMatrix( const Mat4& orthographicProjMat );

   template< typename T >
   void getCameraProjectionMatrix( T outMatrix[16] ) const;

   /// Only used when the camera's projection type is set to orthographic.
   /// This sets the width and height of the near and far planes (left, right, top, bottom) of the rectangular
   /// frustum. This method assumes the frustum is symmetric about 0,0; ie, the distance to the left side of the
   /// frustum is the same as the distance to the right side (from the center).
   /// The near and far planes are set using the corresponding set near/far clipping plane methods.
   void setCameraOrthographicSymmetricFrustumLengths( float distLeftToRight, float distBottomToTop );

   /// Only used when the camera's projection type is set to orthographic.
   /// This sets the left, right, bottom, top, near, and far extents of the orthographic frustum.
   /// The in passed near / far parameters are used to replace this camera's current near and far
   /// plane values.
   void setCameraOrthographicFrustumLengths( float left   = 0.0f,  float right = 1.0f, 
                                             float bottom = 0.0f,  float top   = 1.0f,
                                             float near   = -1.0f, float far   = 1.0f );

   /// This method is only with respect to the orthographic projection settings. For these to be used
   /// the camera's projection type must be set to pmptORTHOGRAPHIC.
   /// Returns the distance between far and near plane, left and right plane, top and bottom plane,
   /// in the x,y,z components, respectively.
   Vector getCameraOrthographicSymmetricFrustumLengths() const;

   std::string toString() const;

   /// If true, this camera and any draw calls made to objects from this camera are intended for a 
   /// shadow map. This means depthMask ought to be enabled as draw calls are made.
   bool isRenderingToShadowMap() const { return this->IsRenderingToShadowMap; }
   /// If set to true, this camera and any draw calls made to objects from this camera are intended 
   /// for a shadow map. This means depthMask ought to be enabled as draw calls are made. Models that explicitly disable
   /// glDepthMask() ought to query this camera's property and enable DepthMask iff the model ought to cast a shadow into the shadowmap;
   /// otherwise, no shadow will be cast by this object.
   void isRenderingToShadowMap( bool cameraUsedToGenerateShadowMap ) { this->IsRenderingToShadowMap = cameraUsedToGenerateShadowMap; }


protected:

   GLView* glView = nullptr; ///< GLView which owns this Camera
   HandlerMouseState* mouseHandler = nullptr; ///< Mouse state information used by this camera for movement
   AftrGeometryFrustum frustum; ///< Current Viewing Frustum for a Perspective or orthogonal Projection
   CameraViewport viewportInfo; ///< Current Viewport used by this camera
   PROJ_MATRIX_PROJ_TYPE camProjectionType = PROJ_MATRIX_PROJ_TYPE::pmptPERSPECTIVE; ///< This camera's default to Perspective or orthographic Projection Mode for the PROJECTION Matrix
   
   /**
      Determines the local +z axis about which "look left/right" rotations occur. This is useful when the camera
      is placed arbitrarily on the surface of a sphere and the local left/right must be parallel with the normal 
      at the position of the camera.
   */
   Vector axisOfHorizontalRotationViaMouseMotion = { 0,0,1 };
   
   /**
      Each time the camera moves (via moveCameraInLookDirection, etc). This scalar is multiplied
      by the camera's current normalized look direction resulting in a distance the camera will
      be moved by. This is basically how far the camera moves forward each 'step'.
   */
   float cameraVelocity;
   
   /**
      Mouse Sensitivity Divider. Larger values decreases responsivness; smaller values increase responsivness.
      The default value is 285.0f.
   */
   float mouseSensitivityDivider;

   /**
      Scalar value multiplied by magnitude of the initial vector from the joint to the camera.
      This scalar determines how 'fast' the camera zooms in/out from the object the camera is attached to.
   */
   float jointZoomFactor;

   /**
      If this camera type is designed to watch and/or follow a specific World Object, such as
      the GLView's current actor, the user can specify that by setting this via the setter/getter.
      Not owned by this instance.
   */
   WO* actorToWatch = nullptr;

   bool IsUsingviewMatrixAdditionalRotationWithTranslationTransformMat; ///< true if user called Camera::setCameraViewMatrixAdditionalRotationWithTranslationTransformMat(...); false otherwise.

   float verticalFOVDeg; ///< Vertical field of view used for this camera instance
   float nearClippingPlane; ///< The near clipping plane distance this camera instance uses
   float farClippingPlane; ///< The far clipping plane distance this camera instance uses
   float aspectRatioWidthToHeight; ///< The aspect ratio of width to height (what OpenGL uses)

   Mat4 viewMatrixAdditionalRotationalTransformMat; ///< Concatenated with display matrix within updateViewMatrix before generating the current view matrix, specified in same space as the model's display matrix, if IsUsingviewMatrixAdditionalRotationWithTranslationTransformMat is true
   Mat4 viewMat; ///< The current OpenGL View matrix used by this camera
   Mat4& projMat; ///< The current OpenGL Projection matrix used by this camera, it is always a reference to either Camera::perspectiveProjMat or Camera::orthoProjMat
   Mat4 perspectiveProjMat; ///< The current perspective projection matrix. Actively used when this camera's PROJ_MATRIX_PROJ_TYPE is PROJ_MATRIX_PROJ_TYPE::pmptPERSPECTIVE
   Mat4 orthographicProjMat; ///< The current orthographic projection matrix. Actively used when this camera's PROJ_MATRIX_PROJ_TYPE is PROJ_MATRIX_PROJ_TYPE::pmptORTHOGRAPHIC

   float orthographicFrustumLeftDist; ///< When projection type is "pmptORTHOGRAPHIC", this is the distance from center of near plane to the left side of frustum
   float orthographicFrustumRightDist; ///< When projection type is "pmptORTHOGRAPHIC", this is the distance from center of near plane to the right side of frustum
   float orthographicFrustumTopDist; ///< When projection type is "pmptORTHOGRAPHIC", this is the distance from center of near plane to the top side of frustum
   float orthographicFrustumBottomDist; ///< When projection type is "pmptORTHOGRAPHIC", this is the distance from center of near plane to the bottom side of frustum

   bool IsRenderingToShadowMap = false; ///< If true, this camera and any draw calls made to objects from this camera are intended for a shadow map. This means depthMask ought to be enabled as draw calls are made.

};

std::ostream& operator<<( std::ostream& out, const Camera::PROJ_MATRIX_PROJ_TYPE& pmpt );

} //namespace Aftr
