/**
\class GLSLAttribute
\author Chad Mourning
\brief A wrapper for GLSL Attributes.
*/

#pragma once

#include "AftrConfig.h"

#ifdef AFTR_CONFIG_USE_OGL_GLEW
#include "AftrOpenGLIncludes.h"
#include "GLSLAttribute.h"
#include <string>
#include <vector>
#include "VectorFwd.h"

namespace Aftr
{

class GLSLAttributeArray
{
public:

   /**
   \param name Attribute name
   \param animated If true, update called
   */

   GLSLAttributeArray( const std::string& name, GLSLAttributeType type);
   GLSLAttributeArray( const GLSLAttributeArray& x );
   virtual ~GLSLAttributeArray();
   std::string getName() const { return attributeName; }
   void addElement( float* float_data);
   void addElement( int* int_data);
   void addElement( bool* bool_data);
   void addElement( const Vector& x );
   void setElement( size_t index, float* float_data);
   void setElement( size_t index, int* int_data);
   void setElement( size_t index, bool* bool_data);
   void setElement( size_t index, const Vector& x );

   GLSLAttributeType getType() const { return type; }
   const std::vector< GLvoid* >* getElements() const { return &elements; }
   std::vector< GLvoid* >* getElements() { return &elements; }

protected:

   std::string attributeName = "";
   GLSLAttributeType type = atVEC3;

   std::vector< GLvoid* > elements;

};

}
#endif //AFTR_CONFIG_USE_OGL_GLEW
