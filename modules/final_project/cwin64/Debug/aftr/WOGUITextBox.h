#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUITextBox : public WOGUI
{
public:
   static WOGUITextBox* New( WOGUI* parentWOGUI, float width, float height );
   virtual ~WOGUITextBox();
   virtual void setText( const std::string& text );
   std::string getText();

   virtual void onMouseClicked( const SDL_MouseButtonEvent& e );
   virtual void onMouseEnter( const SDL_MouseMotionEvent& e );
   virtual void onMouseLeave( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& e );
   virtual void onKeyUp( const SDL_KeyboardEvent& e );

protected:
   WOGUITextBox( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height );

   static const float BORDER_WIDTH; ///< Default textures are 64x64 with 1 pixel border, so
};

} //namespace Aftr
