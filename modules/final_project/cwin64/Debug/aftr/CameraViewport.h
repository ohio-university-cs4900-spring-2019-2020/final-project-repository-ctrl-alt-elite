#pragma once

#include <string>

namespace Aftr
{

/**
   Mirrors the OpenGL Viewport parameters
   http://www.khronos.org/opengles/documentation/opengles1_0/html/glViewport.html
*/
class CameraViewport
{
public:
   CameraViewport();
   CameraViewport( const CameraViewport& toCopy );
   virtual ~CameraViewport();
   CameraViewport& operator =( const CameraViewport& v );
   std::string toString() const;

   /// Returns the x component (in pixels) of the lower left corner of this viewport
   int getX() const { return this->x; }
   /// Returns the y component (in pixels) of the lower left corner of this viewport
   int getY() const { return this->y; }
   /// Returns the width in pixels of this viewport
   unsigned int getWidth() const { return this->width; }
   /// Returns the height in pixels of this viewport
   unsigned int getHeight() const { return this->height; }

   /// Sets the x component (in pixels) of the lower left corner of this viewport
   void setX( int x ) { this->x = x; }
   /// Sets the y component (in pixels) of the lower left corner of this viewport
   void setY( int y ) { this->y = y; }
   /// Sets the width, in pixels, of this viewport
   void setWidth( unsigned int newWidth ) { this->width = newWidth; }
   /// Sets the height, in pixels, of this viewport
   void setHeight( unsigned int newHeight ) { this->height = newHeight; }
   /// Sets the width and height (in pixels) of this viewport
   void setSize( unsigned int newWidth, unsigned int newHeight ) { this->width = newWidth; this->height = newHeight; }
   /// Sets the x and y components (in pixels) of the lower left corner of this viewport
   void setLowerLeftCorner( int x, int y ) { this->x = x; this->y = y; }
   /**
      Overwrites the in passed array with the following viewport information
      outViewport[0] = x, outViewport[1] = y, 
      outViewport[2] = width, outViewport[3] = height
      This is the format expected by glViewport( GLint* viewport ).
   */
   void getGLViewportDataIntoArrayForGL( int outViewport[4] ) const;


protected:
   int x; ///< pixel specifying the leftmost point of the viewport (x,y specify lower left corner)
   int y; ///< pixel specifying the lowest point of the viewport (x,y specify lower left corner)
   unsigned int width; ///< Width of this viewport in pixels
   unsigned int height; ///< Height of this viewport in pixels

};

} //namespace Aftr

