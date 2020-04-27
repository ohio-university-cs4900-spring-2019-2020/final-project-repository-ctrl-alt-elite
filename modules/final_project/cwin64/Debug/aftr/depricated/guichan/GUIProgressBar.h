#pragma once

#ifdef STM_CONFIG_USE_GUICHAN

#include "guichan/widget.hpp"
#include <string>

namespace gcn
{
   class Image;
}

namespace Steamie
{

/**
   \class GUIProgressBar
   \author Scott Nykl 
   \brief An inheritable class used to show a simple progress bar using GUIChan

   \{
*/

class GUIProgressBar : public gcn::Widget
{
public:
   ///Default constructor, will set up the Wood Meter 0 percent filled
   GUIProgressBar();

   GUIProgressBar( std::string outterImageBorder, std::string innerImageFiller );
   
   ///Destructor, handles any memory clean up
   ~GUIProgressBar();

   ///The overloaded draw function
   virtual void draw(gcn::Graphics* graphics);

   void setFillSpeed( unsigned int maxDeltaPixelSizePerRender );

   void setPercentFull( float percent );
   void increasePercentFull( float percent ) { this->setPercentFull( this->percentFull + percent ); }
   void decreasePercentFull( float percent ) { this->setPercentFull( this->percentFull - percent ); }
   float getPercentFull() { return this->getPercentFull(); }

protected:

   void construct( std::string outterImageBorder, std::string innerImageFiller );

   gcn::Image* outterImg;
   gcn::Image* innerImg;
   
   float percentFull;
   unsigned int fillSpeed;
   unsigned int mWidthDuringLastRender;


};

/** \} */

} //namespace Steamie
#endif //STM_CONFIG_USE_GUICHAN
