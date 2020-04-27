#pragma once

#include "MGL.h"

namespace Aftr
{

class Camera;
class GLSLShader;

class MGLSkyBox : public MGL
{
public:
   MGLSkyBox( WO* parentWO, std::string texture, Camera** cam, float sideLen = 50 );
   MGLSkyBox( WO* parentWO, std::vector< std::string > textures, Camera** cam, float sideLen = 50 );
   virtual ~MGLSkyBox();
   virtual void render( const Camera& cam );
   virtual void renderGL32();
   virtual void renderCompatibility();

   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );

   float getSideLength();
   void setSideLength( float newSideLength );

   Camera** getCameraPtrPtr() { return this->cam; }
   void setCameraPtrPtr( Camera** cam ) { this->cam = cam; }

   void setSideLengthAccordingToGLFarPlaneDistance( float distanceToFarPlane );
   float getLengthToGLFarPlaneDistance();

protected:
   void initStateVariables( float sideLen, Camera** cam );
   void initGLData(); ///< Initializes all index/vertex GL data to nullptr / 0 prior to initStateVariables() being called

   void generateInterleavedVBOData();
   void createVBOFaceA( GLubyte vertOffset = 0, GLubyte indexOffset = 0 ); ///< Face A - "Left" side of sky box
   void createVBOFaceB( GLubyte vertOffset = 4, GLubyte indexOffset = 6 ); ///< Face B - "Front" side of sky box
   void createVBOFaceC( GLubyte vertOffset = 8, GLubyte indexOffset = 12 ); ///< Face C - "Right" side of sky box
   void createVBOFaceD( GLubyte vertOffset = 12, GLubyte indexOffset = 18 ); ///< Face D - "Back" side of sky box
   void createVBOFaceE( GLubyte vertOffset = 16, GLubyte indexOffset = 24 ); ///< Face E - "Bottom" side of sky box
   void createVBOFaceF( GLubyte vertOffset = 20, GLubyte indexOffset = 30 ); ///< Face F - "Top" side of sky box
   void updateGPUBuffers();

   float fAs, fAe; ///< Face A Start Tex Coord and Face A End Tex Coord
   float fBs, fBe;
   float fCs, fCe;
   float fDs, fDe;
   float fEs, fEe;
   float fFs, fFe;

   float s; ///Length of each side of sky box (perfect cube)

   Camera** cam = nullptr;

   std::array< GLushort, 6 * 6> indexList; ///< Model's member indexList to be of type GLubyte* instead of GLuint* (save space)   
   std::array< VertexListEntry, 4 * 6 > vertexList; ///< Interleaved array containing texture, color, normal, position for each vertex
   GLuint VBOVertexListInterleavedData = 0; ///< VBO VertexList id (Used by OpenGL)
   GLuint VBOVertexListIndicies = 0; ///< VBO IndexList id (Used by OpenGL)
   GLuint vaoHandle = 0;

   std::unique_ptr< GLSLShader > skyboxShader;
};

}

