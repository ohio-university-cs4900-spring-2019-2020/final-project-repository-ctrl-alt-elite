#pragma once

#include "WOGUI.h"
#include "CameraStandardEZNav.h"

namespace Aftr
{

class WOGUIRoot : public WOGUI
{
public:
   static WOGUIRoot* New( WOGUI* parentWOGUI, float width, float height );
   virtual ~WOGUIRoot();

   virtual void render( const Camera& notUsedByWOGUIRenderPERIODaccessWOGUIRootgetCameraForRenderingMethodInstead );

   //WOGUIRoot must resize its FBO on a screen resize
   virtual void onResizeWindow( int newWidthInPixels, int newHeightInPixels );

   virtual void setOrthographicProjectionMatrix( bool useCustomOrthoProjMat, const float orthoProj[16] );
   virtual void setStereoscopicOffsetOfRoot( bool useOffsetAtRender, const Vector& offset );

   const Camera& getCameraForWOGUIRendering() const;
   Camera& getCameraForWOGUIRendering();

protected:
   WOGUIRoot( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height );

   float orthoProj[16]; ///< Can be set prior to rendering WOGUIRoot. This overloads the default
                        ///orthographic projection matrix used. It is useful when using a display
                        ///such as the Oculus Rift when you need to account for overlays
   bool UseCustomOrthographicProjectionMatrix;
   
   Vector stereoscopicOffset;
   bool UseStereoscopicOffset;

   /// This camera is used to render WOGUI objects that expect an orthogrphic projection for rendering.
   /// The default orthographic projection of this camera is to use a frustum of 
   /// left,right,top,bottom,near,far = (0,1,0,1,-1,1).
   /// This camera is the camera passed to the render method of all WOGUI objects, NOT the standard camera
   /// owned within the GLView. To access this camera or manipulate it, use WOGUIRoot::getCameraForWOGUIRendering()
   std::unique_ptr< CameraStandardEZNav > guiCameraUsedToRenderWOGUIs = nullptr;
};

} //namespace Aftr

