#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUIButton : public WOGUI
{
public:
   static WOGUIButton* New( WOGUI* parentWOGUI, float width, float height, 
                            std::string panelTex = "",
                            std::string onPanelSelectedTex = "", 
                            std::string onPanelMouseDownTex = "" );
   virtual ~WOGUIButton();

   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseClicked( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   virtual void onMouseEnter( const SDL_MouseMotionEvent& e );
   virtual void onMouseLeave( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& e );
   virtual void onKeyUp( const SDL_KeyboardEvent& e );

protected:
   WOGUIButton( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height, 
                          std::string panelTex = "",
                          std::string onPanelSelectedTex = "", 
                          std::string onPanelMouseDownTex = "" );

   /**
      Used to determine which skin to display on the widget. This is affected by
      onMouseLeave, onMouseEnter, onMouseDown, and onMouseUp
   */
   enum WIDGET_MOUSE_STATE { wmsDEFAULT = 0, wmsHAS_CURSOR, wmsMOUSE_DOWN };
   WIDGET_MOUSE_STATE skinState;
};

} //namespace Aftr

