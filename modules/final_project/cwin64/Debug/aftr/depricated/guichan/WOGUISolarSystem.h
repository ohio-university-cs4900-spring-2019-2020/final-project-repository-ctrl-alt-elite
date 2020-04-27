/** This is the object that represents the planetary set up for the 
    for the Solar System overlay for tide island
*/
#pragma once

#ifdef STM_CONFIG_USE_GUICHAN

#include <string>
#include <iostream>
#include <cmath>
#include "WO.h"

namespace Steamie
{

class GUI;
class MGLGUISolarSystem;

/**
   \class WOGUISolarSystem
   \author Mitchell Leitch
   \brief The GUI overlay object for the solar system
   This allows for representing solar system objects on the screen that will always stay at the
   the front of the screen. They will revolve around their parent object. If the object's parent is set
   to null then the object will not revolve around anything. All of the objects will rotate around the 
   center point.
   \{
   */
const int ROTATION_SENSITIVITY = 5;
class WOGUISolarSystem : public WO
{

public:
   static WOGUISolarSystem* New( const std::string& path, WOGUISolarSystem * parent );
   /** The constructor for the WOGUISolarSystem, takes an image in to be used to
       to display the object*/
   WOGUISolarSystem(); 
   /**Destructor for the Solar System Widget, will free up the memory used for the image*/
   virtual ~WOGUISolarSystem();

   /**The Overloaded render selection for the WOGUISolarSystem*/
   void renderSelection();
   
   /** Accessor function, returns whether the left click is down on the widget*/
   bool clicked() { return leftClicked; }

   /** Updates the position, translates the widget to the proper location, helps for translating the moon with
       the Earth*/
   void updatePosition();

   /** Mutator for the radius, sets the distance from the center of the widget to the center of the widget*/
   void setDistanceFromParent(float rad) { radius = rad; }

   ///Moves the solar system widget one unit (int) in the positive direction.
   ///Positive means towards 360 degrees (on a circle)
   void movePositive();
   ///Moves the solar system widget one unit (int) in the negative direction.
   ///Negative means towards 0 degrees (on a circle)
   void moveNegative();

   ///Accessor function, which returns the variable movePositive, to determine which direction the solar system widget should be moving
   ///True if in the positive direction, false if in the negative direction
   bool getMoveDirection() { return moveDirection; }

   ///Accessor function, gets location of solar system object in reference to its parent (i.e. the earth's parent is the sun, the moon's parent is the earth).
   ///Returns the location in radians based on a circle
   ///Return value in radians
   float getLocation();

   ///Mutator function, sets the location of the solar system object in reference to its parent
   ///Must be in radians
   void setLocation(float loc); 

   ///Accessor function to get the offset. This is so that the solar system object can be zeroed at a certain position
   ///to be able to use relative locations, measured in radians
   float getOffSet() { return offSet; }

   ///Mutator function for offSet
   ///Must be in radians
   void setOffSet(float oSet); 

   ///Accessor function to get the revolution offset
   float getRotOffset() { return rotOffset; }

   ///Mutator function for the revolution offset 
   ///oSet is measured in degrees
   void setRotOffset(float oSet);

   ///Rotates the original image a certain degree and stores it into the rotated image.
   ///@param angleOfRotation the amount in radians to rotate the image.
   void revolveImage(float angleOfRotation);

   ///Rotates the image about itself in the positive direction
   void rotatePositive();
   ///Rotates the image about itself in the negative direction
   void rotateNegative();
   ///Accessor functions, which returns the amount the image is rotated
   ///Value returned in radians
   float getRotationAmount() { return (rotated * (PI / 180) ); }

   ///Adjusts the location so that it is in the range of 0-360
   void bringRevolutionAmountInRange();
   ///Adjusts the rotated so that it is in the range of 0-360 
   void bringRotationAmountInRange();

   ///Adds a water bulge to the solar system object, can be used for other highlighting of planets, but right mainly for theEarth
   void addHighlightImage(std::string highlightPath);

   ///Rotates the solar systems object and modifies the ellipse based on eccentricity of the ellipse.
   void rotateHighlightEllipse();

   ///Adjusts the ellipse, changing the rotation of the ellipse and the eccintricity.
   ///ellipseRotation is kept in the range of (0 - 2Pi).
   ///Automatically calls rotateHighlightEllipse to allow for redraw
   void adjustEllipse(float rot, float ecc);


   /**Changes the dimensions of the image (x,y only) to be able to have different sized solar system objects*/
   void changeImageDimensions(float x, float y);
   /**Accessor, returns the dimensions of the image, return value is a pair*/
   std::pair<float, float> getImageDimensions();
   /**Changes the dimensions of the image (x,y only) to be able to have different sized solar system objects*/
   
   void changeImageHighlightDimensions(float x, float y);
   /**Accessor, returns the dimensions of the image, return value is a pair*/
   std::pair<float, float> getHighlightImageDimensions();

   /**Mouse Specific handling for the Solar System, this calls the GUI->update and passes itself as a parameter
      so if you ever want to do specific mouse handling functions in your gui to interact with this object, you
      must write the handler in your gui specific code.
      In the base class update does nothing.*/
   virtual void onMouseDown(const SDL_MouseButtonEvent& mouse);
   
   /**Overloaded, On mouse up to handle dragging of the solar systems in a circular fashion around the parent.
      This will stop the dragging*/
   virtual void onMouseUp(const SDL_MouseButtonEvent& mouse);

   virtual void onMouseMove(const SDL_MouseMotionEvent& mouse);
   /**Overloaded, The render function specific to the GUISolarSystem.*/
   virtual void render();

   /**Overloaded set position, calls the inherited set position then updates the absolute position accordingly*/
   virtual void setPosition( const Vector& newXYZ );

   /**Overloaded moveRelative, calls the inherited move relative and then updates the absolute position vector accordingly*/
   virtual void moveRelative( const Vector& dXdYdZ );

   /**Set the gui handling the SolarSystem object.
      This cascades down to the children, so if you want SolarSystem objects with different parents but are related to each other
      you will need to set them individually and the proper order.*/
   void setGUI(GUI* gui);
   /**Returns the gui that handles this object*/
   GUI* getGUI() { return parentGUI; }

   /**Selects the Solar System object, setting selected to true so it can draw the highlight to let the user know what is selected*/
   void select() { selected = true; }
   /**Deselects the solar system object, setting selected to false*/
   void deselect() { selected = false; }

   /**Sets the amount to rotate the highlight image, rotate needs to be in degrees*/
   void setHighlightRotationAmt(float rotate) { highlightRotated = rotate; }
   /**Returns the amount the highlight image is rotated in radians*/
   float getHighlightRotationAmt() { return (highlightRotated * (PI / 180)); }


protected:
   virtual void onCreate( const std::string& path, WOGUISolarSystem * parent );

   /** The distance from the parent the object is or the radius of orbit around the parent*/
   float radius;
   /** The location of the planet in reference to the sun, based on the angle it makes with the sun being the origin and the x axis running directly to the  of the sun and y running directly vertical with the sun*/
   float location;
   ///The amount the solar system object is rotated
   float rotated;
   ///The amount of the highlight image to be rotated
   ///This can be different than the regular image
   ///For the most part you can set these equal
   float highlightRotated;
   /**The absolute position on the screen of this Solar System overlay.
      Cannot be less than 0 (x or y) or greater than  Steamie::SCREEN_WIDTH, Steamie::SCREEN_HEIGHT (x or y respectively).
      */
   Vector absolutePosition;
   ///Boolean, if true this means the left mouse button is down. Used when determining if the Solar System Widget is being clicked and dragged
   bool leftClicked;
   ///Boolean, if true this means the right mouse button is down. Used when determining if the Solar System Widget is being clicked and dragged
   bool rightClicked;
   ///The last clicked mouse position on the x-axis
   int lastClickedX;
   ///The last clicked mouse position on the y-axis
   int lastClickedY;
   ///If true when the solar system widget is moved it will move in the positive direction, if not it will move negatively 
   bool moveDirection;

   ///The quadrant where the mouse is clicked
   int quadrant;

   ///The path of the image that is used to draw the solar system object
   std::string imagePath;

   ///The offset for the solar system object so it can be zeroed on a certain position
   float offSet;

   ///The revolution offset so when you want to rotate the image from a different starting spot from the revolution location
   float rotOffset;
   
   ///The path to the water bulge dynamically showing off where the tides are.
   ///Right now for theEarth only.
   std::string* highlightImagePath;

   ///The eccintricity of the ellipse, the lower the eccintricity the more circular the ellipse is (0 = circle)
   float ellipseEccentricity;
   ///The amount to rotate the ellipse
   float ellipseRotation;

   /**The gui the solar system is attached to*/
   GUI* parentGUI;

   /**True if the SS object is selected, this will draw an highlight to accentuate the selection*/
   bool selected;

};

/** \} */

} //namespace steamie

#endif //STM_CONFIG_USE_GUICHAN
