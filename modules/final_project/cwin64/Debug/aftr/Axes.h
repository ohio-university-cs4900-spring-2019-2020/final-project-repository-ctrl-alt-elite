//----------------------------------------------------------------------------
//Description: The Axes class has only one static method called ShowAxes.
//This method draws the X, Y, and Z Axes on the OpenGL control.
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once

//----------------------------------------------------------------------------
//Description: The Axes class has only one static method called ShowAxes.
//This method draws the X (Red), Y(Green), and Z(Blue) Axes on the OpenGL
//control.
//----------------------------------------------------------------------------
namespace Aftr
{

   class IndexedGeometryAxes;

   class Axes
   {
   public:
      //-------------------------------------------------------------------------
      //This method is draws the X (Red), Y(Green), and Z(Blue) Axes on the
      //OpenGL control.
      //-------------------------------------------------------------------------
      static void showAxes( const Camera& cam );
      static bool isVisible;
      static IndexedGeometryAxes* axes;
   protected:
      static void showAxesCompatibility( const Camera& cam );
      static void showAxesGL32( const Camera& cam );
   };

} //namespace Aftr
