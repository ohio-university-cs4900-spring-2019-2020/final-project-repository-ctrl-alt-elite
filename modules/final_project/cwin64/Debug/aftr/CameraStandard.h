#pragma once

#include "Camera.h"

namespace Aftr
{

class CameraStandard : public Camera
{
public:
   CameraStandard( GLView* glView, HandlerMouseState* mouseHandler );
   virtual ~CameraStandard();

   CameraStandard() = delete;
   CameraStandard( const CameraStandard& toCopy ) = delete;
   CameraStandard& operator=( CameraStandard& toAssign ) = delete;
   CameraStandard& operator=( CameraStandard&& toMove ) = delete;
   
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseWheelScroll( const SDL_MouseWheelEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   virtual void attachCameraToWO( WO* WOtoWatch, const Vector& globCoordOfIntersection );
   virtual void update();
   virtual void startChasingCurrentActor() {};
   void changeJointTheta( float deltaTheta );
   void changeJointPhi( float deltaPhi );
   void setJointMouseMotionSensitivity( float sensitivity );
   float getJointMouseMotionSensitivity() { return this->jointMouseMotionSensitivity; }

protected:

   float jointTheta;
   float jointPhi;
   float jointRho;
   float jointMouseMotionSensitivity;
   float m[16];
};


} //namespace Aftr
