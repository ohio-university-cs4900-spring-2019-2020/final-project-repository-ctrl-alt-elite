#pragma once

#include "AftrSDLIncludes.h"

namespace Aftr
{

class WOGUI;

/**
   This is a policy layer class that handles the processing of events for all WOGUI* widgets
   pushed in the GLView's WorldContainer. This class determines if an event should be handled
   by the UI or passed to the objects within the simulation.
*/

class UI
{
public:
   static UI* New();
   virtual ~UI();

   /**
      This is the primary method which determines if the UI will handle the event
      or pass the event onto the simulation.
   */
   bool handleWOGUIEvent( const SDL_Event& e );

   /**
      Each of these methods determine if the UI will handle the event, and if so,
      these methods define the policy/behavior taken to process the event.
   */

   /**
      If the UI handles any mouse button activity, the current
      GLView's mouse handler must be notified. Mouse motion does not need
      to cause notification to the mouse handler since that would cause the
      cursor to disappear and be treated as though the user was turning within
      the simulation.
   */
   bool handleMouseMotionEvent( const SDL_MouseMotionEvent& e );
   bool handleMouseDownEvent( const SDL_MouseButtonEvent& e );
   bool handleMouseUpEvent( const SDL_MouseButtonEvent& e );

   bool handleKeyDownEvent( const SDL_KeyboardEvent& e );
   bool handleKeyUpEvent( const SDL_KeyboardEvent& e );

   /**
      Depth first pre order traversal of GUI tree returning the widget
      after the widget currently having focus. NULL is returned if no
      focusable widget exists.
   */
   WOGUI* getNextFocusableWidget();

   /**
      Depth first pre order traversal of GUI tree returning the widget
      before the widget currently having focus. NULL is returned if no
      focusable widget exists.
   */
   WOGUI* getPrevFocusableWidget();

   /**
      Returns the currently focused widget, NULL if no widget is currently focused.
   */
   WOGUI* getFocusedWidget();

   /**
      Returns the last widget in which a mouse down event occurred.
   */
   WOGUI* getLastWOGUItoHaveMouseDownEvent();

   /**
      This method allows the user to directly set which WOGUI* the UI should recognize
      as the last WOGUI to have a mouse down event. This is useful when children WOGUI
      objects (such as strings) have no intelligence and the user would like all events
      that occur on these objects to be forwarded to their parent WOGUI.
   */
   void setLastWOGUItoHaveMouseDownEvent( WOGUI* wo );
   void setLastWOGUIContainingCursor( WOGUI* wo );
   void setLastWOGUItoBeClicked( WOGUI* wo );
   void setFocusToWOGUI( WOGUI* woguiToGainFocus );

protected:
   UI();
   virtual void onCreate();

   WOGUI* lastWOGUIContainingCursor; ///< Points to the non-root WOGUI* widget which last held the cursor

   /**
      Points the the non-root WOGUI* widget which last had a MouseDown event occur.
      This is used to determine when a mouse click occurs
   */
   WOGUI* lastWOGUItoHaveMouseDownEvent;

   /** Points to the non-root WOGUI* widget which was last clicked by the user.
   */
   WOGUI* lastWOGUItoBeClicked;

   WOGUI* focusedWidget; ///< Used to maintain UI state pertaining to focus


};


} //namespace Aftr

