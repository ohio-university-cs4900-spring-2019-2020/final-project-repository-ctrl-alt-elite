//-------------------------------------------------------
//
// File: GUIBox
// Author: Mitchell Leitch
//
// An encompassing GUI class which, all dialog boxes,
// question boxes, and any other box that would like to inherit
// from can and have base functionality
//
//-------------------------------------------------------


#pragma once

#ifdef STM_CONFIG_USE_GUICHAN

union SDL_Event;

#include "guichan/widgets/window.hpp"

namespace gcn
{
   class ImageFont;
}

namespace Steamie
{

   class GLView;
   class GUI;

   /**
      \class GUIBox
      \author Mitchell Leitch
      An encompassing GUI class which, all dialog boxes,
      question boxes, and any other box that would like to inherit
      from can and have base functionality
      \{
      */
class GUIBox : public gcn::Window
{
public:

   GUIBox( gcn::ImageFont* font );

   virtual ~GUIBox();

   /**
      Checks to see if the box has the mouse with mouse up/down/motion
      \param new_event - the sdl event which contains the mouse information
      \returns bool - true if the GUIBox has the mouse
      */
   bool eventPerformedOnGUIBox(const SDL_Event& new_event);

   /**
      Toggles showing the the GUIBox
      */
   void show();

   /**
      Makes the GUIBox invisible
      */
   void hide();

   /**
      Function NEEDS to be declared in the children to set up the GUIBox so that the widgets are all in the right place
      */
   virtual void displayCurrentIndex() {};

   /**
      function clicks the widget with the mouse that is focused (black box surrounding it)
      Simulates a mouse click
      */
   virtual void clickFocusedWidget() {};

   /**
      overload focus function to allow for control of tabbing through the gui objects without 
      crashing, another shortcoming of guichan :(
      */
   virtual void focusPrevious();
   
   /**
      overload focus function to allow for control of tabbing through the gui objects without 
      crashing, another shortcoming of guichan :(
      */
   virtual void focusNext();

   /**
      sets the screen position of the dialog box relative to the screen based off of the screen size
      e.g. 800 x 600
      */
   void setScreenPosition(int x, int y) { positionx = x; positiony = y; }
protected:

   /**
      The index of the current page of information of the GUIBox.
      Can have multiple pages of information
      */
   int currentIndex;
   /**
      The number of times the GUIBox has been made visible.
      */
   int numTimesShown;

   /**
      the screen position of the dialog box to be shown at, default is the center of the screen
      */
   int positionx, positiony;
};

/** \} */

} //namespace Steamie

#endif //STM_CONFIG_USE_GUICHAN
