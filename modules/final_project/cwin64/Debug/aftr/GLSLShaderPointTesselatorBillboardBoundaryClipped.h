#pragma once

#include "GLSLShader.h"
#include "Vector.h"

namespace Aftr
{

class Camera;
class Model;

class GLSLShaderPointTesselatorBillboardBoundaryClipped : public GLSLShader
{
public:
   static GLSLShaderPointTesselatorBillboardBoundaryClipped* New( Camera** cam );
   virtual ~GLSLShaderPointTesselatorBillboardBoundaryClipped();

   GLSLShaderPointTesselatorBillboardBoundaryClipped& operator =( const GLSLShaderPointTesselatorBillboardBoundaryClipped& shader );

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
   void setClipMax( const Vector& clipMax ) { this->clipMax = clipMax; }
   void setClipMin( const Vector& clipMin ) { this->clipMin = clipMin; }

   virtual void bind();
   virtual void unbind();
   void setCamera( Camera** cam ) { this->cam = cam; }
   Camera** getCamera() const { return this->cam; }
   void setDimXY( float x, float y ); ///< Sets size of each particle in x,y (horz, vert)
   void getDimXY( float& x, float& y ); ///< out param. Size of each particle in x,y (horz, vert).
protected:
   GLSLShaderPointTesselatorBillboardBoundaryClipped( GLSLShaderDataShared* dataShared, Camera** cam );
   GLSLShaderPointTesselatorBillboardBoundaryClipped( const GLSLShaderPointTesselatorBillboardBoundaryClipped& toCopy );

   Camera** cam = nullptr;
   Model* model = nullptr;
   float xDim; ///< Size of each particle in the x (horizontal direction)
   float yDim; ///< Size of each particle in the y (vertical direction)
   Vector clipMax; ///< Max point; beyond this point the region is clipped
   Vector clipMin; ///< Min point; beyond this point the region is clipped

};

} //namespace Aftr

