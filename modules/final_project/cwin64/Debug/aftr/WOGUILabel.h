#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUILabel : public WOGUI
{
public:
   static WOGUILabel* New( WOGUI* parentWOGUI );
   virtual ~WOGUILabel();
   virtual void setColor( aftrColor4ub color );
   virtual void setColor( GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255 );

   virtual void setText( const std::string& text );
   virtual std::string getText();
   virtual void setFontPath( const std::string& fontPath );
   virtual void setFontSize( float fontSize );
   virtual void setFontOrientation( FONT_ORIENTATION orientation );
   virtual void setFontEmboldeningCoefficient( float x );

   float getCurrentStringHeight();

   virtual void onResizeWindow( int newWidthInPixels, int newHeightInPixels );
protected:
   WOGUILabel( WOGUI* parentWOGUI );
   virtual void onCreate();
};

} //namespace Aftr

