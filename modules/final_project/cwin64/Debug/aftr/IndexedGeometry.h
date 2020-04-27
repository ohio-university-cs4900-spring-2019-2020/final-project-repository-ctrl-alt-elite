#pragma once

#include "AftrOpenGLIncludes.h"
#include <vector>

namespace Aftr
{
   class IndexedGeometry
   {
   public:
      virtual ~IndexedGeometry();
      virtual void render();
      virtual void renderGL32();
      virtual void renderCompatibility();
      virtual void renderSelection(GLubyte red, GLubyte green, GLubyte blue);
      virtual void setGLPrimType(GLenum x) { renderType = x; }

      /// Returns a pointer to a list containing all verticies within this model.
      /// This list is indexed by the corresponding CompositeIndexList.
      virtual const std::vector< Vector >& getCompositeVertexList() const;

      /// Returns a pointer to a list containing all indicies into the corresponding
      /// CompositeVertexList.
      virtual const std::vector< unsigned int >& getCompositeIndexList() const;

      GLubyte* getColors() { return colors; }
      GLfloat* getNormals() { return normals; }
      GLfloat* getVertices() { return vertices; }
      GLfloat* getTextureCoords() { return textureCoords; }
      GLvoid* getIndices() { return indices; }
      GLsizei getVertexCount() { return vertexCount; }//number of vertices
      GLsizei getIndexCount() { return indexCount; }

      virtual void updateColorBuffer();
      virtual void updateVertexBuffer();
   protected:
      IndexedGeometry( bool useTextureCoords = false,  bool useNormals = false, bool useColors = false );
      virtual void init();
      virtual void createVAO();
      virtual void createVertices() = 0;
      virtual void createIndices() = 0;
      virtual void createTextureCoords(){}
      virtual void createNormals(){}
      virtual void createColors(){}
      virtual void reattach();
      GLubyte* colors = nullptr;
      GLfloat* normals = nullptr;
      GLfloat* textureCoords = nullptr;
      GLfloat* vertices = nullptr;
      GLsizei vertexCount = 0;
      GLvoid* indices = nullptr; //type depends on amount of vertices (GLubyte, GLushort, GLuint)
      GLsizei indexCount = 0;

      bool useTextureCoords = false;
      bool useNormals = false;
      bool useColors = false;

      GLenum renderType = GL_TRIANGLES;
      GLenum memoryType = GL_UNSIGNED_SHORT;
      
      GLuint vertexLocation   = -1; ///< GLSL Attribute locations within the shader, queried and populated during creation
      GLuint normalLocation   = -1; /// These are initialized to -1 even though they are unsigned because "0" is a valid GL attribute location
      GLuint colorLocation    = -1;
      GLuint texCoordLocation = -1;

      GLuint vao = 0; ///< Vertex Array Object which stores all buffer binding states required to render this VAO
      GLuint indexBuffer = 0; ///< OpenGL Buffer containing indices to render the geometry
      GLuint vertexBuffer = 0; ///< OpenGL Buffer location for the vertex attributes (set of vertices passed to shader)
      GLuint normalBuffer = 0; ///< OpenGL Buffer location for the normal attributes (set of normals passed to shader)
      GLuint colorBuffer = 0;  ///< OpenGL Buffer location for the colors attributes (set of colors passed to shader)
      GLuint textureBuffer = 0;///< OpenGL Buffer location for the textures attributes (set of textures passed to shader)
   };
}

