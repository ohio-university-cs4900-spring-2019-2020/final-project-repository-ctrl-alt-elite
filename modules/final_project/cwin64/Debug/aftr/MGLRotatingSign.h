#pragma once

#include "MGL.h"
#include <string>

namespace Aftr
{

   enum class ROTATION_STATE : unsigned char { rsFACE1 = 0, rsROTATING1, rsFACE2, rsROTATING2, rsNUM_ROTATION_STATE };
   std::ostream& operator<<( std::ostream& out, const ROTATION_STATE& rs );

   class IndexedGeometryQuad;
   class IndexedGeometrySphere;
   class IndexedGeometryCylinder;
  
   class  MGLRotatingSign: public MGL
   {
   public:      
      MGLRotatingSign( WO* parentWO, const std::string& texture1, const std::string& texture2, float length, float height, const Vector& color);
      virtual ~MGLRotatingSign();
      virtual void render( const Camera& cam );
      //virtual void renderSelection(GLubyte red, GLubyte green, GLubyte blue){};
      void setInternalTimer(unsigned int x) { this->internalTimer = x; }
      void setRotationTimer(unsigned int x) { this->rotationTimer = x; }
      void setRotationState(ROTATION_STATE x) { this->rotationState = x; }
   private:
      float length;
      float height;
      Vector color;
      unsigned int internalTimer;
      unsigned int rotationTimer;
      ROTATION_STATE rotationState;
      IndexedGeometryQuad* quad;
      IndexedGeometrySphere* sphere;
      IndexedGeometryCylinder* cylinder;
   };

}

