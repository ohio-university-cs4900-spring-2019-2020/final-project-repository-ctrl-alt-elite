#pragma once

#include "MGL.h"
#include <string>
#include <vector>

namespace Aftr
{
   class GLView;
   class Camera;
   class IndexedGeometryQuad;

   /** \{
   \class - MGLBillboard
   \brief - This is the billboard openglmodel. This will follow the location of the camera so it is always facing the screen.
   Warning** If the scale changes or the distance between the vertices YOU MUST call setBoundingBox again and pass in the new 
   dimensions of the model
   */
   class MGLBillboard : public MGL
   {
   public:

      MGLBillboard( WO* parentWO, std::vector<std::string> textures, Camera** cam, int slices, float height, float width );
      virtual ~MGLBillboard();

      /*purely virtual render functions, which are necessary to draw just a sphere to represent a vertex instead of a model
      these MUST be overriden in the child class if you want to create a openGL model that you create by drawing yourself*/
      virtual void render( const Camera& cam );
      //render selection for billboard objecst will use the default bounding box render, bounding boxes should be set properly
      //virtual void renderSelection( GLubyte red, GLubyte green, GLubyte blue );

   protected:
      /** storage for the GLView */
      Camera** cam;
      /** storage for the scale, rotation, and translation */
      float height;
      float width;
      /** the number of planes */
      int planes;	
      IndexedGeometryQuad* quad;
   };

   /** \} */
}  //namespace Aftr

