#pragma once
#include "AftrSDLIncludes.h"

namespace Aftr
{

class HandlerMouseState
{
public:
   HandlerMouseState();
   virtual ~HandlerMouseState();
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseWheelScroll( const SDL_MouseWheelEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );

   /**
      Sets the xCoord and yCoord to the position (pixels) the cursor was located
      before disappearing due to a mouse button event.
      xCoord and yCoord are out parameters only, there values are overwritten.
   */
   void getMouseDownPosition( unsigned int& xCoord, unsigned int& yCoord );

   /// Returns the horizontal change the mouse has moved in pixels since entering a mouse button pressed state
   int getMouseMotionDeltaX() { return this->deltaX; }

   /// Returns the vertical change the mouse has moved in pixels since entering a mouse button pressed state
   int getMouseMotionDeltaY() { return this->deltaY; }

   /// Returns true iff Left Mouse button is currently pressed; false, otherwise.
   bool isMouseDownLeftButton() { return this->leftMouseButtonDown; }

   /// Returns true iff Right Mouse button is currently pressed; false, otherwise.
   bool isMouseDownRightButton() { return this->rightMouseButtonDown; }

   /// Returns true iff Middle Mouse button is currently pressed; false, otherwise.
   bool isMouseDownMiddleButton() { return this->middleMouseButtonDown; }

   bool isMouseDownLeftButtonMostRecent() { return this->leftMouseButtonMostRecentDown; }
   bool isMouseDownRightButtonMostRecent() { return this->rightMouseButtonMostRecentDown; }
   bool isMouseDownMiddleButtonMostRecent() { return this->middleMouseButtonMostRecentDown; }

   bool isMouseDragging() { return this->hasBeenDragged; }

   bool hideCursorOnMouseDrag() { return this->HideCursorOnMouseDrag; }

   /**
      Iff true, the mouse cursor will disappear when a mouse button is pressed AND
      the mouse is dragged. Internally, this will continually warp the mouse cursor
      back to the center of the screen allowing for infinite dragging left/right and/or
      up/down without reaching the end of the screen.

      If false, the mouse cursor will not disappear when a mouse button is pressed AND
      the mouse is dragged. This also implies once the mouse cursor reaches the edge of 
      the screen, no further motion in that direction can be detected. Hence, this limits
      the length of a mouse drag.
   */
   void hideCursorOnMouseDrag( bool enableHidingCursorOnMouseDrag );

   virtual void reset();

protected:

   unsigned int mouseDownAtX; ///< XCoord where the mouse was pressed
   unsigned int mouseDownAtY; ///< YCoord where the mouse was pressed

   bool leftMouseButtonDown;
   bool rightMouseButtonDown;
   bool middleMouseButtonDown;

   bool leftMouseButtonMostRecentDown;
   bool rightMouseButtonMostRecentDown;
   bool middleMouseButtonMostRecentDown;

   bool leftMouseButtonMostRecentUp;
   bool rightMouseButtonMostRecentUp;
   bool middleMouseButtonMostRecentUp;

   int deltaX;
   int deltaY;

   bool hasBeenDragged;

   bool HideCursorOnMouseDrag;

   /**
      Set to true when onMouseDown is processed by this handler. This is checked
      by the onMouseUp is processed by this handler. This way, the handler will
      not SDL_Warp the mouse cursor unless it handled both the down and up events.
      This is useful when a UI widget handles an onMouseDown and the user then drags
      the cursor off the widget.
   */
   bool mouseHandlerProcessedCorrespondingOnMouseDownEvent;

};


} //namespace Aftr


