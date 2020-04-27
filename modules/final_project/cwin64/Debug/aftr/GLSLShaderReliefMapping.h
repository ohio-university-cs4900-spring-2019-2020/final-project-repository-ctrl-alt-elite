#pragma once

#include "GLSLShader.h"

namespace Aftr
{

class Camera;
class Model;
class WOLight;

class GLSLShaderReliefMapping: public GLSLShader
{
public:
   static GLSLShaderReliefMapping* New( Model* m, Camera* cam, WOLight* light, float scaleFactorOfModel = 1.0f );
   virtual ~GLSLShaderReliefMapping();

   GLSLShaderReliefMapping& operator =( const GLSLShaderReliefMapping& shader );

   /**
      Returns a copy of this instance. This is identical to invoking the copy constructor with
      the addition that this preserves the polymorphic type. That is, if this was a subclass
      of GLSLShader with additional members and methods, this will internally create the
      shader instance as that subclass, thereby preserving polymorphic behavior, members, and
      methods.

      This is in contrast with a copy constructor in the case where one performs:
      GLSLShader* myCopy = new GLSLShader( shaderToBeCopied );
      This will always create a GLSLShader* instance, not a subclass corresponding to the exact
      type of shaderToBeCopied.
   */
   virtual GLSLShader* getCopyOfThisInstance();
   void setModel( Model* m ) { this->model = m; }
   Model* getModel() { return this->model; }

   void setCamera( Camera* cam ) { this->cam = cam; }
   Camera* getCamera() const { return this->cam; }

   void setLight( WOLight* light ) { this->light = light; }
   WOLight* getLight() const { return this->light; }

   void setDepth( float depth ) { this->depth = depth; }
   float getDepth() { return this->depth; }

   void setDiscardDepthBelow( float depthScalar ) { this->discardDepthBelow = depthScalar; }
   float getDiscardDepthBelow() { return this->discardDepthBelow; }

   void setScaleOfModel( float scale ) { this->scaleFactorOfModel = scale; }
   float getScaleOfModel() { return this->scaleFactorOfModel; }

   virtual void bind();
   virtual void unbind();

protected:
   GLSLShaderReliefMapping( GLSLShaderDataShared* dataShared, Model* m, Camera* cam, WOLight* light, float scaleFactorOfModel );
   GLSLShaderReliefMapping( const GLSLShaderReliefMapping& toCopy );

   Camera* cam = nullptr; ///< Not owned, don't delete
   Model* model = nullptr; ///< Not owned, don't delete
   WOLight* light = nullptr; ///< Not owned, don't delete
   float depth = 0.1f; //typically [0,1], 0.1 works well
   float discardDepthBelow = 0.9f; ///< Discards fragment if the intersection w/ depth map is below this value [0,1]
   float scaleFactorOfModel = 1.0f;

};

} //namespace Aftr

