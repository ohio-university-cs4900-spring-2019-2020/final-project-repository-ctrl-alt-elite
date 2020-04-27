#pragma once

#include "WO.h"
#include "IFaceGUIWidget.h"

namespace Aftr
{

class WOGUILabel;
class WOGUIFTGLLabel;

class WOGUI : public WO, public IFaceGUIWidget 
{
public:
   static WOGUI* New( WOGUI* parentWOGUI, float width, float height, std::string panelTex = "" );
   static WOGUI* New( WOGUI* parentWOGUI, float width, float height, Texture* tex );
   virtual ~WOGUI();

   /**
      Returns true iff this WOGUI and ALL of its ancestors contain pixel x,y within
      their bounding boxes AND this WOGUI widget is not underneath some other widget.
      This traverses the GUI tree in a Post order depth first fashion, which is exactly
      opposite the order in which the widgets are rendered (pre order depth first).
      This way, the 'last' gui widget rendered is on top and the first gui widget we
      check for pixel containment is the topmost rendered widget. This way a widget
      buried underneath the topmost widget will not be returned as containing the
      pixel.
   */
   WOGUI* guiContainsPixel( int x, int y );

   /**
      Returns true iff the mouse cursor is visible AND this widget is the topmost
      widget containing the cursor. Internally, this method ensures the cursor is
      visible, gets the current cursor location and then calls 
      this->guiContainsPixel( x, y ). 
      
      Thus a widget contains the cursor if this WOGUI and ALL of its ancestors 
      contain pixel x,y within their bounding boxes AND this WOGUI widget is 
      not underneath some other widget AND the cursor is visible.
   */
   bool hasMouseCursor();

   /**
      This method enables any WOGUI to forward all local events to another WOGUI. The WOGUI
      returned by this method becomes the widget the UI invokes all events on. For example,
      if this widget was a dumb string contained within a smart parent button, then setting
      this method to return a pointer to the parent would cause all events, such as mouse 
      clicks, etc, to be invoked on the parent.

      This is useful when a dumb widget is encapsulated within an intelligent widget and
      the user would like the intelligent widget to process the events. The default behavior
      for this method returns a pointer to this instance.
   */
   virtual WOGUI* getProxyWOGUI();

   /**
      This method enables any WOGUI to forward all local events to another WOGUI. The WOGUI
      returned by this method becomes the widget the UI invokes all events on. For example,
      if this widget was a dumb string contained within a smart parent button, then setting
      this method to return a pointer to the parent would cause all events, such as mouse 
      clicks, etc, to be invoked on the parent.

      This is useful when a dumb widget is encapsulated within an intelligent widget and
      the user would like the intelligent widget to process the events. This value 
      defaults to a pointer to this instance.
   */
   virtual void setProxyWOGUI( WOGUI* proxy );

   /**Invoked when this WO is the current actor and the user presses a mouse button*/
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   /**Invoked when this WO is the current actor and the user releases a mouse button*/
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   /**Invoked when the user clicks on this WOGUI. That is, the user presses a mouse
      button down within this widget, and also releases the mouse button within this
      widget.
   */
   virtual void onMouseClicked( const SDL_MouseButtonEvent& e );
   /**Invoked when this WO is the current actor and the user moves a mouse*/
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   
   virtual void onMouseEnter( const SDL_MouseMotionEvent& e );
   virtual void onMouseLeave( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& e );
   virtual void onKeyUp( const SDL_KeyboardEvent& e );
   virtual void onHasFocus();
   virtual void onLostFocus();
   bool isFocusable();
   void isFocusable( bool isFocusable );
   bool hasFocus();
   bool receivesEvents();
   void receivesEvents( bool receiveUIEvents );

   virtual void onResizeWindow( int newWidthInPixels, int newHeightInPixels );

   ///Sets this WOGUI's position relative to its parent, z value is ignored
   virtual void setPosition( const Vector& newXYZ );
   ///Sets this WOGUI's position in absolute coordinates, z value is ignored
   virtual void setPositionAbs( const Vector& newXYZ );

   ///Returns the WOGUI's position relative to its parent, z value is always 1
   Vector getPosition();
   /// Returns the WOGUI's absolute position on the screen, z value is always 1
   Vector getPositionAbs();

   float getWidthGUI();
   float getHeightGUI();

   void setWidthGUI( float widthAbs );
   void setHeightGUI( float heightAbs );
   void setSizeGUI( float widthAbs, float heightAbs );

   /// Takes a vector relative to this WOGUI and returns the absolute
   /// screen coordinates.
   Vector makeRelCoordAbsolute( const Vector& v );
   /// Takes a vector in absolute screen coordinates and returns a vector
   /// relative to this WOGUI's position
   Vector makeAbsCoordRelative( const Vector& v );

   /// Takes an absolute height and returns the height relative to this WOGUI's height
   float makeAbsHeightRelative( float absHeight );
   /// Takes an aboslute width and returns the width relative to this WOGUI's width
   float makeAbsWidthRelative( float absWidth );

   virtual void render( const Camera& cam );
   virtual void renderFromFBO();
   virtual void renderSelection() {};

   /// This will enlarge this WOGUI's bounding box to encapsulate this instance's this->text
   /// label. This way, positioning and spacing this object will work with longer multi line labels.
   virtual void resizeToFitText();
   /// Method above will have excess room in the background quad if the content shrinks, this can lead to funny behavior for "centered" text
   /// Method below shrinks the quad to fix this, may not handle hierarchical groups properly
   virtual void resizeToFitTextShrinkingQuad();

   virtual void setText( const std::string& text );
   virtual void setTextFont( const std::string& fontPath );
   virtual void setTextSize( float fontSize );
   virtual void setTextColor( const aftrColor4ub& color );
   virtual void setFontJustification( const FONT_JUSTIFICATION& justification );
   virtual void setFontOrientation( FONT_ORIENTATION orientation );

   WOGUILabel* getGUILabel() { return this->text; }

   virtual void isUsingStencilBuffer( bool useStencilBufferForClipping );
   virtual bool isUsingStencilBuffer();

   /// Recursively invokes isUsingStencilBuffer(bool useStencil) on this widget and all children.
   /// Recursion operates as a depth first traversal, left to right.
   virtual void isUsingStencilBufferForMeAndAllMyChildren( bool useStencilBufferForClipping );
      
protected:
   WOGUI( WOGUI* parentWOGUI );
   virtual void onCreate( float width, float height, std::string panelTex = "" );
   virtual void onCreate( float width, float height, Texture* tex );
   
   /// returns true iff pixel x,y is within this WOGUI's 2D bounding box
   bool pixelResidesInBoundingRect( int x, int y );

   /**
      Invoked on all children of a WOGUI when that WOGUI's setPositionAbs() is invoked.
      setPositionAbs() is always invoked by setPosition().
      This way, all children are always fully current w.r.t their global position.
   */
   void onWOGUIParentPositionChanged();

   WOGUI* proxyWOGUI = nullptr; ///< Pointer to WOGUI which receives all events that happen to this instance

   WOGUILabel* text = nullptr;
   //WOGUIFTGLLabel* text = nullptr;

   bool HasFocus = false; ///< true if this widget is the currently focused object
   bool IsFocusable = true; ///< true if this widget can obtain focus
   bool ReceivesEvents = true; ///< if true, event callbacks will be invoked on this widget; if false, no callbacks will be invoked on this widget

   /**
      x,y components range from [0,0], [1,1]; lower left of parent to upper 
      right of parent. z remains at 1.0f.
   */
   Vector relToParent;

};


} //namespace Aftr

