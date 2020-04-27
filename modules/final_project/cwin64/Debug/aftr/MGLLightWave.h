#pragma once

#include "MGL.h"
#include "IndexedGeometryAxes.h"

namespace Aftr
{

   class IndexedGeometryQuad;

   class MGLLightWave : public MGL
   {
   public:
      MGLLightWave(WO* parentWO, WO* source, WO* sink, Camera** cam, float width );
	  MGLLightWave( WO* parentWO, const Vector& source, const Vector& sink, Camera** cam, float width );
      virtual ~MGLLightWave();
      virtual void render( const Camera& cam );
      virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
      void setLightWaveWidth( float width );
      float getLightWaveWidth();
      void setSourceOfLightWave( const Vector& src ) { this->src = src; }
      void setSinkOfLightWave( const Vector& sink ) { this->snk = sink; }
      void setCamera( Camera** camPtr );
      Camera** getCamera();

   protected:
      WO* source;
      WO* sink;
	   Vector src;
	   Vector snk;
      float width;
      Camera** cam;
      IndexedGeometryQuad* quad;
      IndexedGeometryAxes* axes;
   };

} //namespace Aftr

