#pragma once

#include "MGL.h"
#include "ManagerTexture.h"
#include "Vector.h"

namespace Aftr
{

   class MGLGrid : public MGL
   {
   public:
      //static MGLGrid* New(std::vector<std::vector<VectorD> > grid, VectorD scale);
      MGLGrid( WO* parentWO );
      MGLGrid( WO* parentWO, std::vector<std::vector<VectorD> > grid, VectorD scale, std::vector< std::vector< aftrColor4ub > > colors = std::vector< std::vector< aftrColor4ub > >());
      virtual ~MGLGrid();  
      virtual void render( const Camera& cam );
      virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
      size_t getRows(){return row-1;}
      GLfloat* getNormalList(){return normalList;}
      GLfloat* getVertexList(){return vertexList;}
      virtual void defineIndices();
      virtual void defineVertices();
      virtual void defineTextureCoords();
      virtual void defineNormals();
      virtual void defineColors( const aftrColor4ub* c = NULL );
      virtual void makeVBO(int splits = 0);
      virtual size_t getFaceCount();
   protected:
      //virtual void onCreate();
      GLfloat* vertexList;//list of descriptions of those vertices 
      GLubyte* colorList;
      GLfloat* normalList;
      GLfloat* textureList;
      size_t row;//strictly positive
      size_t column;
      std::vector<std::vector<VectorD> > grid;
      std::vector< std::vector< aftrColor4ub > > colors;
      VectorD scale;

      GLuint vertexData;
      GLuint indexData;
   };

}  //namespace Aftr

