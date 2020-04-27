#pragma once
#include "AftrConfig.h"
#include "VectorFwd.h"
#include <string>

/**
   This file includes the proper OpenGL include files based on the current platform
   specific setting found in AftrConfig.h. This file is helpful when an engine
   file needs to know what any GL type or function is (ie GLuint, etc), but does
   not want to include everything that is specified within Predefined.h.
*/

#ifdef AFTR_CONFIG_USE_OGL_GLEW //Open GL 3.0 and all extensions (Desktop graphics)
#define GLEW_STATIC
   #include "GL/glew.h"
#elif defined AFTR_CONFIG_USE_OGL_GLES //Mobile Devices OpenGL ES library
   #include <OpenGLES/ES1/gl.h>
   #include <OpenGLES/ES1/glext.h>
#else
   #error User Must use either GLEW or GLES. Do this in AftrConfig.h
#endif

#include "VertexListEntry.h"

namespace Aftr
{

/// When generating VBO/VA data, share normals (SMOOTH) or use one normal per face (FLAT)
enum class MESH_SHADING_TYPE : unsigned char { mstSMOOTH = 0, mstFLAT, mstNONE, mstAUTO, mstNOTINITIALIZED, mstNUM_MESH_SHADING_TYPE };
std::ostream& operator<<( std::ostream& out, const MESH_SHADING_TYPE& mst ); //enables MESH_SHADING_TYPE to work with ostream

/**
   When a Mesh is rendered, it can be rendered using a VA (Vertex Array) or VBO (Vertex Buffer Object). VBOs
   are faster and reside in graphics hardware memory. VAs are deformable since the arrays resides in host
   memory.
*/
enum class MESH_RENDER_TYPE : unsigned char { mrtVA = 0, mrtVBO, mrtVA_AND_VBO, mrtNUM_MESH_RENDER_TYPE };
std::ostream& operator<<( std::ostream& out, const MESH_RENDER_TYPE& mrt ); //enables MESH_RENDER_TYPE to work with ostream

#ifdef AFTR_CONFIG_COLOR_FLOAT
   const size_t VERTEX_LIST_STRIDE = 12 * sizeof( GLfloat );
   const size_t VERTEX_LIST_TEX_COORD_OFFSET = 0;
   const size_t VERTEX_LIST_COLOR_OFFSET = 2 * sizeof( GLfloat );
   const size_t VERTEX_LIST_NORMAL_OFFSET = 6 * sizeof( GLfloat );
   const size_t VERTEX_LIST_VERTEX_OFFSET = 9 * sizeof( GLfloat );
   #define AFTR_COLOR_TYPE GL_FLOAT
   #define AFTR_MAX_COLOR 1
#endif

//use the following if colors are set to GLubyte
#ifdef AFTR_CONFIG_COLOR_UNSIGNED_BYTE
   const size_t VERTEX_LIST_STRIDE = sizeof( VertexListEntry );
   const size_t VERTEX_LIST_TEX_COORD_OFFSET = 0;
   const size_t VERTEX_LIST_COLOR_OFFSET = 2 * sizeof( GLfloat );
   const size_t VERTEX_LIST_NORMAL_OFFSET = 2 * sizeof( GLfloat ) + 4 * sizeof( GLubyte );
   const size_t VERTEX_LIST_VERTEX_OFFSET = sizeof( VertexListEntry ) - sizeof( GLfloat) * 3;//5 * sizeof( GLfloat ) + 4 * sizeof( GLubyte );
   #define AFTR_COLOR_TYPE GL_UNSIGNED_BYTE
   #define AFTR_MAX_COLOR 255
#endif

/// Unsigned Byte colors range from [0,255].
class aftrColor4f;
class aftrColor4ub
{
public:
   aftrColor4ub();
   aftrColor4ub( const Vector& rgb );
   explicit aftrColor4ub( const aftrColor4f& c );
   explicit aftrColor4ub( int r, int g, int b, int a );
   explicit aftrColor4ub( unsigned int r, unsigned int g, unsigned int b, unsigned int a );
   explicit aftrColor4ub( GLubyte r, GLubyte g, GLubyte b, GLubyte a );
   explicit aftrColor4ub( float r, float g, float b, float a );
   GLubyte& operator [] ( size_t i );
   const GLubyte& operator [] ( size_t i ) const;
   //GLubyte operator [] ( size_t i ) const;
   bool operator ==( const aftrColor4ub& c ) const;
   aftrColor4ub operator +( const aftrColor4ub& c ) const;
   aftrColor4ub operator +=( const aftrColor4ub& c );
   aftrColor4ub operator -( const aftrColor4ub& c ) const;
   aftrColor4ub operator -=( const aftrColor4ub& c );
   GLubyte r = 255, g = 255, b = 255, a = 255;
};

aftrColor4ub operator*( const aftrColor4ub& c, float s );
aftrColor4ub operator*( float s, const aftrColor4ub& c );

/// Floating point colors are normalized between [0,1].
class aftrColor4f
{
public:
   aftrColor4f();
   aftrColor4f( const Vector& rgb );
   /// Expects input unsigned bytes to have values in range [0,255].
   explicit aftrColor4f( const aftrColor4ub& c );
   explicit aftrColor4f( GLubyte r, GLubyte g, GLubyte b, GLubyte a );
   explicit aftrColor4f( float r, float g, float b, float a );
   GLfloat& operator [] ( size_t i );
   GLfloat operator [] ( size_t i ) const;
   GLfloat r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;
};

aftrColor4f operator*( const aftrColor4f& c, float s );
aftrColor4f operator*( float s, const aftrColor4f& c );

class aftrVertexData
{
public:
   aftrVertexData();
   ~aftrVertexData();
   float* vert3f; ///< Fixed length of three floats, position x,y,z
   float* normal3f; ///< Fixed length of three floats, normal x,y,z, NULL if no normals
   /**
      Variable number of sets of 1D/2D/3D/4D tex coords for this vertex. Size of each set
      is should align with the texture dimensionality of the corresponding skin bound
      when rendering the ModelMeshRenderData containing this vertex. Accessing the texture
      dimensionality can be done via:
      skin.getMultiTextureSet().at(i)->getTextureData()->getTextureDimensionality()
      Number of sets is ModelMeshRenderData::getTexCoordsOffset().size().
      NULL if no tex coords.
   */
   float* tex;
   /**
      Variable number of vertex attributes. Size of i'th vertex attribute
      for this vertex is ModelMeshRenderData::getAttributesType( i ).
      Number of attributes for this vertex is 
      ModelMeshRenderData::getAttributesOffset().size().
      NULL if no per vertex attributes.
   */
   void* attribute;
   /**
      Color of this vertex. Either 3 channel or 4 channel GLubytes range [0,255].
      Number of channels is accessible via ModelMeshRenderData::getNumColorChannels().
      NULL if no per vertex color.
   */
   GLubyte* color;

   std::string toString() const;

};

class aftrTexture4f
{
public:
   aftrTexture4f( GLfloat u = 0, GLfloat v = 0, GLfloat c = 0, GLfloat d = 0 ) 
   { this->u = u; this->v = v; this->c = c, this->d = d; }
   GLfloat u, v, c, d;
};

} //namespace Aftr

