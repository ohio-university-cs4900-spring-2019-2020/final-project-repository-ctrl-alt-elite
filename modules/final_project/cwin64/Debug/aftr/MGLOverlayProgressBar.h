#pragma once

#include "MGL.h"
#include "Vector.h"

namespace Aftr
{
   class IndexedGeometryQuad;

   class MGLOverlayProgressBar : public MGL
   {
   public:
      MGLOverlayProgressBar( WO* parentWO, std::string outterImageBorder, 
                             std::string innerImageFiller,
                             float height, float width,
                             float heightFiller, float widthFiller );
      virtual ~MGLOverlayProgressBar();
      virtual void render( const Camera& cam );

      void setOverlaySize( float outterImageHeight, float outterImageWidth,
         float innerImageHeight, float innerImageWidth );
      void setOverlayInnerImageOffsetFromCenterOfOutterImage( float x, float y );
      void setFillSpeed( float maxDeltaPercentPerRender );
      void setPercentFull( float percent );
      void increasePercentFull( float percent ) { this->setPercentFull( this->percentFull + percent ); }
      void decreasePercentFull( float percent ) { this->setPercentFull( this->percentFull - percent ); }
      float getPercentFull() { return this->percentFull; }

   protected:

      float computeFillWidth();

      //textureNames[0] is outterImageBorder
      //textureNames[1] is innerImageBorder

      float mHeightBorder;
      float mWidthBorder;
      float mHeightFiller;
      float mWidthFiller;
      float mInnerImageOffsetX;
      float mInnerImageOffsetY;

      Vector fillerTexPos;

      float percentFull;

      float mPercentFullDuringLastRender;
      float maxDeltaPercentPerRender;

      IndexedGeometryQuad* quad;

   };

} //namespace Aftr

