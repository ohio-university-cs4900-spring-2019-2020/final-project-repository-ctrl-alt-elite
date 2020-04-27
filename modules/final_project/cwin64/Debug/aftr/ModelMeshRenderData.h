#pragma once

#include "AftrGlobals.h"
#include "AftrOpenGLIncludes.h"
#include "GLSLAttribute.h"
#include "Vector.h"


namespace Aftr
{

class ModelMeshRenderDataGenerator;

class ModelMeshRenderData
{
public:

   friend class ModelParser;
   friend class ModelParserAssimp;

   //using value_type = V;        //Interleaved_Vertex_T;
   //using vertex_value_type = V; //Interleaved_Vertex_T;
   //using index_value_type = I;  //Index_T;

   ModelMeshRenderData();

   ModelMeshRenderData( void* VAIdx,
                        void* VAVtx,
                        GLsizei idxSize,
                        GLsizei vtxSize,
                        GLenum idxMemType,
                        GLsizei vtxStride,
                        bool isUsingColorsArray,
                        GLenum numColorChannels,
                        unsigned int vertsOffset,
                        unsigned int colorsOffset,
                        unsigned int normalsOffset,
                        const std::vector< unsigned int >& texCoordsOffset,
                        const std::vector< unsigned int >& attributesOffset,
                        const std::vector< GLSLAttributeType >& attributesType,
                        const std::map< std::string, GLuint >& attributesNameToIndex,
                        void* NormalVAIdx,  ///< Indices into the 'per vertex data' array (flatVtx) (VA handle)
                        void* NormalVAVtx,    ///< Contiguous array of per vertex data (vert, color, textures, normals, etc) (VA handle)
                        //GLuint NormalVBOIdx, ///< VBO IndexList id (Used by OpenGL) (VBO handle)
                        //GLuint NormalVBOVtx, ///< VBO VertexList id (Used by OpenGL) (VBO handle)
                        GLsizei NormalidxSize, ///< Number of indicies into the 'per vertex data' array (Vtx)
                        GLsizei NormalvtxSize, ///< Number of elements in the Vertex Array
                        GLenum NormalidxMemType, ///< Is each index into the vertex list a GLubyte, GLushort, GLuint?
                        GLenum NormalglPrimType );///< GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_QUAD_STRIP, GL_QUADS, and GL_POLYGON are accepted.    );

   ModelMeshRenderData( const ModelMeshRenderData& toCopy );

   virtual ~ModelMeshRenderData();

   ModelMeshRenderData& operator =( const ModelMeshRenderData& r );

   GLuint getVAOHandle() const { return this->VAOHandle; }
   void* getVAIdx() const { return this->VAIdx; }
   void* getVAVtx() const { return this->VAVtx; }
   GLuint getVBOVtx() const { return this->VBOVtx; }
   GLuint getVBOIdx() const { return this->VBOIdx; }
   void setVAOHandle( GLuint VAOGLHandle ) { this->VAOHandle = VAOGLHandle; }
   void setVBOVtx( GLuint VBOVtxHandle ) { this->VBOVtx = VBOVtxHandle; }
   void setVBOIdx( GLuint VBOIdxHandle ) { this->VBOIdx = VBOIdxHandle; }
   GLsizei getIdxSize() const { return this->idxSize; }
   void setIdxSize( unsigned int x ) { this->idxSize = x; }
   GLsizei getVtxSize() const { return this->vtxSize; }
   void setVtxSize( GLsizei vtxSize ) { this->vtxSize = vtxSize; }
   GLenum getIdxMemType() const { return this->idxMemType; }
   void setIdxMemType( GLenum idxMemType ) { this->idxMemType = idxMemType; }

   void* getNormalVAIdx() const { return this->NormalVAIdx; }
   void* getNormalVAVtx() const { return this->NormalVAVtx; }
   //GLuint getNormalVBOVtx() const { return this->NormalVBOVtx; }
   //GLuint getNormalVBOIdx() const { return this->NormalVBOIdx; }
   //void setNormalVBOVtx( GLuint NormalVBOVtxHandle ) { this->NormalVBOVtx = NormalVBOVtxHandle; }
   //void setNormalVBOIdx( GLuint NormalVBOIdxHandle ) { this->NormalVBOIdx = NormalVBOIdxHandle; }
   GLsizei getNormalIdxSize() const { return this->NormalidxSize; }
   GLsizei getNormalVtxSize() const { return this->NormalvtxSize; }
   GLenum getNormalIdxMemType() const { return this->NormalidxMemType; }

   bool isLoaded() const { return this->IsLoaded; }

   GLsizei getVtxStride() const { return this->vtxStride; }
   bool isUsingColorsArray() const { return this->IsUsingColorsArray; }
   GLenum getNumColorChannels() const { return this->numColorChannels; }
   void setNumColorChannels( GLenum GL_RGB_or_GL_RGBA ) { this->numColorChannels = GL_RGB_or_GL_RGBA; }
   GLsizei getNumColorChannelsAsInt() const { return ( (this->numColorChannels == GL_RGBA )? 4 : 3 ); } ///< Returns 4 if GL_RGBA or 3 if GL_RGB; other formats not yet supported
   
   unsigned int getVertsOffset() const { return this->vertsOffset; }
   unsigned int getColorsOffset() const { return this->colorsOffset; }
   unsigned int getNormalsOffset() const { return this->normalsOffset; }

   const std::vector< unsigned int >& getTexCoordsOffset() const { return this->texCoordsOffset; }
   const std::vector< unsigned int >& getAttributesOffset() const { return this->attributesOffset; }
   const std::vector< GLSLAttributeType >& getAttributesType() const { return this->attributesType; }
   const std::map< std::string, GLuint >& getAttributesNameToIndex() const { return this->attributesNameToIndex; }

   void destroyCPUSideDataPreservingGPUSideVAData();
   void destroyAllCPUSideAndGPUSideData();
   bool hasValidVAHandles() const { return this->VAIdx != NULL; }
   bool hasValidVBOHandles() const { return this->VBOIdx != 0; }

   std::string toString() const;
   std::string toStringStereolithography();//was going to make it const, but it may have to map the render data which requires manipulating the glMapBufferPtr

   //I don't think this is correct; the thesis sentance indicates that the index data
   //is stored in the VBO, the vertex and index data are stored in seperate buffers
   //See: GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER
   //From what I can tell, this doesn't touch the index list at all.
   //Also, I didn't see a good mechanism for cases when the size of the lists change.
   /**
      This method must be called prior to using any methods which read or write
      vertex or index data stored within this ModelMeshRenderData's VBO.
      This is not necessary for data stored within this ModelMeshRenderData's VA.

      Internally this method wraps glMapBuffer() using the VBO handle for this
      ModelMeshRenderData. glMapBuffer() will take the server-side memory pointing
      to the VBO and map that into client-side memory. Once mapped, the VBO data
      can be read/written. This mapping must be performed before any attempt to
      modify the VBO data occurs.

      Once this method returns, all setters/getters that
      operate on the VBO data will work properly (ie setColorArray, 
      getVertexPtr, etc).

      After reading/writing is done, the user must invoke a corresponding
      unMapVBODataFromClientMemory(). The user should ensure the unmap
      is performed before any other buffer is bound to OpenGL.

      The glAccessType defines which methods the user will request upon the
      VBO data. Valid values are:
      GL_READ_ONLY, GL_WRITE_ONLY, or GL_READ_WRITE.
   */
   bool mapVBODataToClientMemory( GLenum glAccessType = GL_READ_WRITE );

   /**
      This unmaps the server-side VBO data from the client-side memory space.
   */
   void unMapVBODataFromClientMemory();

   //see above, but for index list (untested)
   bool mapVBOIdxDataToClientMemory( GLenum glAccessType = GL_READ_WRITE );
   void unMapVBOIdxDataFromClientMemory();

   bool getVertexDataAtIndexInVertexList( unsigned int index, aftrVertexData* outData ) const;

   bool setColorArrayAtIndexInVertexList( unsigned int index, const aftrColor4ub* color );
   bool setColorArrayAtIndexInIndexList( unsigned int index, const aftrColor4ub* color );
   float* getVertexPtrAtIndexInVertexList( unsigned int index );

   void recalcNormals( float scale );

protected:

   void initMemberData();
   //void populateFromGenerator( const ModelMeshRenderDataGenerator& gen );

   //at the moment the Vtx and Idx maps are both using this points, should probably change to use two seperate ones incase people need to access them both at the same time
   void* glMapBufferPtr = nullptr; ///< Only valid if this render data uses a VBO and this::mapVBODataToClientMemory() has completed successfully.

   GLuint VAOHandle = 0; ///< If GL Context is 3.2 or higher, a VAO will be created when the ModelMeshDataShared::sendDataServerSide is invoked w/ this MMRD
   void* VAIdx = nullptr; ///< Indicies into the 'per vertex data' array (flatVtx) (VA handle)
   void* VAVtx = nullptr; ///< Contiguous array of per vertex data (vert, color, textures, normals, etc) (VA handle)
   GLuint VBOIdx = 0; ///< VBO IndexList id (Used by OpenGL) (VBO handle)
   GLuint VBOVtx = 0; ///< VBO VertexList id (Used by OpenGL) (VBO handle)
   GLsizei idxSize = 0; ///< Number of indicies into the 'per vertex data' array (Vtx)
   GLsizei vtxSize = 0; ///< Number of elements in the Vertex Array
   GLenum idxMemType = GL_UNSIGNED_SHORT; ///< Is each index into the vertex list a GLubyte, GLushort, GLuint? (GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT)
   GLenum glPrimType = GL_TRIANGLES; ///< GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_QUAD_STRIP, GL_QUADS, and GL_POLYGON are accepted.

   void* NormalVAIdx = nullptr; ///< Indicies into the 'per vertex data' array (flatVtx) (VA handle)
   void* NormalVAVtx = nullptr; ///< Contiguous array of per vertex data (vert, color, textures, normals, etc) (VA handle)
   //GLuint NormalVBOIdx; ///< VBO IndexList id (Used by OpenGL) (VBO handle)
   //GLuint NormalVBOVtx; ///< VBO VertexList id (Used by OpenGL) (VBO handle)
   GLsizei NormalidxSize = 0; ///< Number of indicies into the 'per vertex data' array (Vtx)
   GLsizei NormalvtxSize = 0; ///< Number of elements in the Vertex Array
   GLenum NormalidxMemType = GL_UNSIGNED_SHORT; ///< Is each index into the vertex list a GLubyte, GLushort, GLuint? (GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT)
   GLenum NormalglPrimType = GL_LINES; ///< GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_QUAD_STRIP, GL_QUADS, and GL_POLYGON are accepted.                

   MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO; ///< Shading type used on this vertex array (MESH_SHADING_TYPE::mstFLAT, MESH_SHADING_TYPE::mstSMOOTH, MESH_SHADING_TYPE::mstNONE)
   bool IsLoaded = false;

   GLsizei vtxStride = 0; ///< Length of each interleaved element of vertex data (vertex, normal, color, texture, shader attributes, etc)
   bool IsUsingColorsArray = false; ///< True iff a per vertex color array is being used w/ this VA/VBO
   GLenum numColorChannels = GL_RGBA; ///< GL_RGB or GL_RGBA
   unsigned int vertsOffset = 0; ///< Offset to the first vertex (x coord) of each interleaved element (in bytes)
   unsigned int colorsOffset = 0; ///< Offset to the first GLubyte color (Red) of each interleaved element (in bytes)
   unsigned int normalsOffset = 0; ///< Offset to the first normal (x normal) of each interleaved element (in bytes)

   /**
      Set of offsets to the first texture coord(u coord) of each interleaved
      element for the i'th texture; where i is the index into this std::vector (in bytes).
   */
   std::vector< unsigned int > texCoordsOffset;

   /**
      Set of offsets to the shader attribute value of each interleaved
      element for the i'th attribute; where i is the index into this std::vector (in bytes).
   */
   std::vector< unsigned int > attributesOffset;

   /**
      This array is parallel to attributesOffset; that is, the size of each is the
      same and the i'th index of attributesOffset corresponds to the i'th index
      of attributesType. This vector stores the GLSLAttributeType residing in the
      i'th index of the attributesOffset vector (in bytes).
   */
   std::vector< GLSLAttributeType > attributesType;

   std::map< std::string, GLuint > attributesNameToIndex;
};

} //namespace Aftr


