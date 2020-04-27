//--------------------------------------------------
// Description: The model for the WOGUISolarSystem
//              basically a plane which displays the image of the
//              solar system object
// Author: Mitchell Leitch
//-------------------------------------------------

#pragma once

#include "MGL.h"

/**
   \class MGLGUISolarSystem
   \author Mitchell Leitch
   \brief The actual model representation of the WOGUISolarSystem
   This will draw the actual image the solar system object that is passed in.
   \{
   */
namespace Aftr
{
   class IndexedGeometryQuad;

class MGLGUISolarSystem : public MGL
{
public:

   /**Constructor, takes a path to an image that the solar system object will use.*/
   MGLGUISolarSystem( WO* parentWO, std::string imagePath );
   /**Destructor*/
   virtual ~MGLGUISolarSystem();

   /**Overloaded render for the MGLGUISolarSystem*/
   virtual void render( const Camera& cam );
   /**renders an overlay displaying that this object has been selected*/
   virtual void renderWhileSelected();
   /**Overloaded renderselection for the MGLGUISolarSystem*/
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
   /**Renders the highlight image for the solar system object*/
   virtual void renderHighlightImage();
 
   /**Mutator, to change the dimensions of the image*/
   void changeDimensions(float x, float y);
   /**Accessor, to get the dimensions of the image, returns a pair*/
   std::pair<float, float> getDimensions() { return ( std::make_pair(imageX, imageY) ); }
   /**Changes the dimensions of the highlight image*/
   void changeHighlightDimensions(float x, float y) { highlightImageX = x; highlightImageY = y; }
   /**Gets the highlight image dimensions*/
   std::pair< float, float> getHighlightDimensions() { return ( std::make_pair(highlightImageX, highlightImageY) ); }

   /**Adds the highlight image to the model, will only render if one is passed in*/ 
   void addHighlightImage( const std::string& highlightPath );
   
   /**The amount to revolved the SolarSystem around its parent*/
   float revolutionAmt;

   
protected:

   /**The horizontal dimension of the image*/
   float imageX;
   /**The vertical dimension of the image*/
   float imageY;

   /**The horizontal dimension of the highlightImage*/
   float highlightImageX;
   /**The vertical dimension of the highlightImage*/
   float highlightImageY;

   IndexedGeometryQuad* quad;
};

/** \} */


} //namespace Aftr

