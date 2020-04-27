#pragma once

#include "MGL.h"

namespace Aftr
{

   class GLView;
   class WOOcean;
   class WOWater;
   class IndexedGeometryQuad;

   class MGLOcean : public MGL
   {

   public:
      MGLOcean( WO* parentWO, WOOcean* woOceanParent, GLView* view = NULL, int x = 1000, int y = 1000, WOWater* wo = NULL, bool autoFollow = true);
      virtual ~MGLOcean(); 
      virtual void render( const Camera& cam );
      virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
      //VectorD* findWaterNormal(float x, float y);
      GLfloat findWaterHeight(float x, float y);
      int* findLocation(float x, float y);
      WOWater* getBehavior();
      virtual bool isInViewingFrustum( const AftrGeometryFrustum& viewportFrustum );

      void addTexture(unsigned int waterTextureGL) { waterTexture = waterTextureGL; }

   protected:		  
      GLView* glview;
      WOOcean* woOceanParent; //parent world object - THE LOGIC SHOULD BE IN THE PARENT - NOT IN THIS MODEL!!!!
      int gridx, gridy;
      int fullLength, fullWidth;
      WOWater* behavior;
      bool autoFollow;
      unsigned int waterTexture;
      IndexedGeometryQuad* quad;
   };


}  //namespace Aftr

