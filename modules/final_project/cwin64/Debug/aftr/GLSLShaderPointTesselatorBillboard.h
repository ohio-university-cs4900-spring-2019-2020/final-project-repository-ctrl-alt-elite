#pragma once

#include "GLSLShader.h"

namespace Aftr
{

class Camera;
class Model;

class GLSLShaderPointTesselatorBillboard : public GLSLShader
{
public:
   static GLSLShaderPointTesselatorBillboard* New( Camera** cam, Model* m = nullptr );
   virtual ~GLSLShaderPointTesselatorBillboard();

   GLSLShaderPointTesselatorBillboard& operator =( const GLSLShaderPointTesselatorBillboard& shader );

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
   virtual GLSLShader* getCopyOfThisInstance() override;
   void setModel( Model* m ) { this->model = m; }

   virtual void bind() override;
   virtual void bind( const Mat4& modelMatrix, const Mat4& normalMatrix, const Camera& cam, const ModelMeshSkin& skin ) override;
   virtual void unbind() override;
   void setCamera( Camera** cam ) { this->cam = cam; }
   Camera** getCamera() const { return this->cam; }
   void setDimXY( float x, float y ); ///< Sets size of each particle in x,y (horz, vert)
   void getDimXY( float& x, float& y ); ///< out param. Size of each particle in x,y (horz, vert).
protected:
   GLSLShaderPointTesselatorBillboard( GLSLShaderDataShared* dataShared, Camera** cam, Model* m );
   GLSLShaderPointTesselatorBillboard( const GLSLShaderPointTesselatorBillboard& toCopy );

   Camera** cam = nullptr;
   Model* model = nullptr;
   float xDim = 1.0f; ///< Size of each particle in the x (horizontal direction)
   float yDim = 1.0f; ///< Size of each particle in the y (vertical direction)

};

} //namespace Aftr

