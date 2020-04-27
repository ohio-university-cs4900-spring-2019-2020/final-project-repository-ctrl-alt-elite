#pragma once

#include "WO.h"
#include <string>


namespace Aftr
{

class MGLOverlayProgressBar;

/**
   \class WOOverlayProgressBar
   \author Scott Nykl (updated by Chad Mourning)
   \brief An inheritable class used to show a simple progress bar using GUIChan

   \{
*/

class WOOverlayProgressBar : public WO
{
public:
   ///Default constructor, will set up the Meter zero percent filled
   static WOOverlayProgressBar* New();
   static WOOverlayProgressBar* New( const std::string& outterImageBorder, const std::string& innerImageFiller,
                         float outterImageHeight, float outterImageWidth,
                         float innerImageHeight, float innerImageWidth );
   
   
   ///Destructor, handles any memory clean up
   ~WOOverlayProgressBar();

   void setOverlaySize( float outterImageHeight, float outterImageWidth,
                        float innerImageHeight, float innerImageWidth );

   void setOverlayInnerImageOffsetFromCenterOfOutterImage( float x, float y );

   void setFillSpeed( float maxDeltaPercentPerRender );
   void setPercentFull( float percent );
   void increasePercentFull( float percent );
   void decreasePercentFull( float percent );
   float getPercentFull();

protected:
   WOOverlayProgressBar();
   virtual void onCreate( const std::string& outterImageBorder, const std::string& innerImageFiller,
                         float outterImageHeight, float outterImageWidth,
                         float innerImageHeight, float innerImageWidth );

   void construct( const std::string& outterImageBorder, const std::string& innerImageFiller,
                   float outterImageHeight, float outterImageWidth,
                   float innerImageHeight, float innerImageWidth );

};

/** \} */

} //namespace Aftr
