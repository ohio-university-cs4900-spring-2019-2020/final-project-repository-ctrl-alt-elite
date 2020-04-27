#include "WO.h"
#include <string>

#pragma once

namespace Aftr
{

   class MGLLight;
   class IndexedGeometryQuad;

   /**
      \author Scott Nykl, Chad Mourning

      This class abstracts the behavior of OpenGL lights to act in a similar manner to the engines World Objects.
      Updated by Scott to take better constructor parameters and work cleanly with a GL 3.2+ shader-based implementation while
      maintaining compatibility with older contexts.
   */
   class WOLight : public WO
   {
   public:	
      /**
         Represents the diffuse, ambient, and specular intesity of this light. This light's ambient contribution is added
         to the ManagerLight::globalAmbient color.
      */
      static WOLight* New( const aftrColor4f& color = aftrColor4f( 1.0f, 1.0f, 1.0f, 1.0f ), ///< Only color intensity is used in default 3.2+ shader
                           const aftrColor4f& diffuse = aftrColor4f( 1.0f, 1.0f, 1.0f, 1.0f ),
                           const aftrColor4f& ambient = aftrColor4f( 0.0f, 0.0f, 0.0f, 1.0f ),
                           const aftrColor4f& specular = aftrColor4f( 1.0f, 1.0f, 1.0f, 1.0f ) );
      
      virtual ~WOLight();
      void setLight(int x);

      void isPointLight( bool lightEmitsFromPointSource ) { this->IsPointLight = lightEmitsFromPointSource; }
      bool isPointLight() const { return this->IsPointLight; }

      void isDirectionalLight( bool lightRaysAreParallel ) { this->IsPointLight = ! lightRaysAreParallel; }
      bool isDirectionalLight() const { return !this->IsPointLight; }

      void isShadowGenerator( bool createsShadows ) { this->IsShadowGenerator = createsShadows; }
      bool isShadowGenerator() { return this->IsShadowGenerator; }

      void setColor( const aftrColor4f& lightColor );
      void setAmbient( const aftrColor4f& ambient );
      void setDiffuse( const aftrColor4f& diffuse );
      void setSpecular( const aftrColor4f& specular );

      const aftrColor4f& getColor() { return lightColor; }
      const aftrColor4f& getAmbient() { return ambient; }
      const aftrColor4f& getDiffuse() { return diffuse; }
      const aftrColor4f& getSpecular() { return specular; }
     
      void setConstantAttenuation( float x );
      void setLinearAttenuation( float x );
      void setQuadricAttenuation( float x );

      GLfloat getConstantAttenuation() { return constantAttenuation; }
      GLfloat getLinearAttenuation() { return linearAttenuation; }
      GLfloat getQuadricAttenuation() { return quadricAttenuation; }

      void lensFlare( const Camera& cam );
      void lensFlareEffect(size_t index, Vector point, unsigned int texture, const Camera& cam);
      bool isOccluded();
      bool useLensFlare;

      virtual void onUpdateWO();
      void setPosition( const Vector& newPosWorldSpace );

   protected:
      WOLight( const aftrColor4f& color, const aftrColor4f& diffuse, const aftrColor4f& ambient, const aftrColor4f& specular );

      virtual void onCreate();
      virtual void createIndexedQuads();

      aftrColor4f lightColor = aftrColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      aftrColor4f diffuse    = aftrColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      aftrColor4f ambient    = aftrColor4f( 0.0f, 0.0f, 0.0f, 0.0f );
      aftrColor4f specular   = aftrColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

      int light; ///< Corresponds to the GL_LIGHT0 + i, where i is 'this->light', this is updated dynamically each time ManagerLight::synchronizeLights() is called
      bool IsPointLight;
      float constantAttenuation;
      float linearAttenuation;
      float quadricAttenuation;
      bool IsShadowGenerator = false; ///< if true, this light is used for shadow mapping

      IndexedGeometryQuad* quads[16];

      GLenum getLightEnum();
   };
}
