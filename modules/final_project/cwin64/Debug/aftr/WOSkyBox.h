//----------------------------------------------------------------------------
//Description: The  class
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once

#include "WO.h"
#include <string>
#include "Vector.h"

//----------------------------------------------------------------------------
//Description: The WOVehicleFourWheeled class 
//----------------------------------------------------------------------------
namespace Aftr
{

class Camera;

class WOSkyBox : public WO
{

public:
   static WOSkyBox* New( const std::string& skyBoxImageName, Camera** cam );
   static WOSkyBox* New( const std::string& skyBoxImageName, Camera** cam, float sideLength );
   static WOSkyBox* New( const std::vector< std::string >& skyBoxImageNames, Camera** cam );
   static WOSkyBox* New( const std::vector< std::string >& skyBoxImageNames, Camera** cam, float sideLength );

   virtual ~WOSkyBox();
   void renderSelection() {/*SkyBoxes are not selectable*/}

   float getSideLength();
   void setSideLength( float newSideLength );
   void setSkyboxNormalVector( const Vector& normalDirection, bool ignoreAssociatedCamerasNormalDir = false );
   void setIgnoreAssociateCamerasNormalDir( bool ignoreCamAxisRot ) { this->ignoreAssociatedCamerasNormalDir = ignoreCamAxisRot; }
   bool getIgnoreAssociateCamerasNormalDir() { return this->ignoreAssociatedCamerasNormalDir; }

   void setSideLengthAccordingToGLFarPlaneDistance( float distanceToFarPlane );

   /** SkyBox is a special case because the SkyBox's position must always be located w.r.t
       the local camera's position. Therefore, the in passed newXYZ is NEVER USED. Instead
       the local camera's position is used as the position of this SkyBox.
       \param newXYZ This is NOT USED regardless of its value because the WOSkyBox is a 
       special object that must be positioned w.r.t the local camera and not by the server.
   */
   void setPositionToCamerasPosition();

   /** Rotate through all loaded textures for this skybox */
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );

   /** WOSkyBox needs to reposition itself to be centered on the camera before each render */
   virtual void onUpdateWO();
   Camera** getCamPtrPtr();
   virtual void setCamPtrPtr( Camera** cam );

protected:
   WOSkyBox();
   virtual void onCreate( const std::string& skyBoxImageName, Camera** cam, float sideLen );
   virtual void onCreate( const std::vector< std::string >& skyBoxImageNames, Camera** cam, float sideLen );
   
   //Camera** cam;
   Vector curAxisOfHorizontalRotationViaMouseMotion;
   bool ignoreAssociatedCamerasNormalDir = false;

};
} //namespace Aftr
