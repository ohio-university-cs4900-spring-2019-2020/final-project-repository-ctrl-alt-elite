#pragma once
#include "AftrConfig.h"

#include "WO.h"
#include "Vector.h"

namespace Aftr
{

   class WOQuad;

   class WOCompass : public WO
   {
   public:
      static WOCompass* New( float width, float height );
      virtual ~WOCompass();
      virtual void setHeading( float headingDeg );
      virtual void setLLA( const VectorD& lla, const VectorD& centerOfWorld );
      virtual void onUpdateWO();
      virtual void setSource( WO* source ) { this->source = source; }
      virtual void setWorldNormal( const Vector& worldNormal );
      virtual void render( const Camera& cam );

   protected:
      WOCompass();
      virtual void onCreate( float width, float height );

      Vector worldNormal;

      WO* source; ///< WO providing pitch ladder info
      WOQuad* needle; ///< Compass Needle
      VectorD lla; ///< lat, lng, alt determining where true north is relative to this point
      VectorD centerOfWorld;
      float headingDeg;

   };

} //namespace Aftr

