#pragma once

#include "Camera.h"
#include "Vector.h"

namespace Aftr
{

class WOGridECEF;

/**
   The camera instantiated when CAM_CHASE_TYPE is CameraChaseActorSmoothWGS84.
*/
class CameraChaseActorSmoothWGS84 : public Camera
{
public:
   CameraChaseActorSmoothWGS84( GLView* glView, HandlerMouseState* mouseHandler );
   virtual ~CameraChaseActorSmoothWGS84();

   CameraChaseActorSmoothWGS84() = delete;
   CameraChaseActorSmoothWGS84( const CameraChaseActorSmoothWGS84& toCopy ) = delete;
   CameraChaseActorSmoothWGS84& operator=( CameraChaseActorSmoothWGS84& toAssign ) = delete;
   CameraChaseActorSmoothWGS84& operator=( CameraChaseActorSmoothWGS84&& toMove ) = delete;
   
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseWheelScroll( const SDL_MouseWheelEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   virtual void attachCameraToWO( WO* WOtoWatch, const Vector& globCoordOfIntersection );
   virtual void update();
   virtual void startCameraBehavior();

   virtual void setOffsetFromParent( const Vector& offsetFromParent ) { this->offsetFromParent = offsetFromParent; }
   virtual Vector getOffsetFromParent() { return this->offsetFromParent; }

   virtual void setStayAboveTerrain( WOGridECEF* grid, const VectorD& centerOfWorldInLLA );

protected:

   float chaseModeVelocityRatio;
   Vector offsetFromParent; ///< Point always near the actor that the camera continually tries to catch
   float pivotThetaRad; ///<  When ALT is pressed in this cam mode, the mouse motion rotates horizontally about actor
   float pivotPhiRad; ///<  When CTRL is pressed in this cam mode, the mouse motion rotates vertically about actor
   float pivotRadius; ///<
   float jointMouseMotionSensitivity;

   VectorD centerOfWorldLLA; ///< When camera is set to remain above terrain, this stores the center of world in LLA
   WOGridECEF* grid; ///< When this is non-NULL, the camera is set to remain above the terrain

};


} //namespace Aftr
