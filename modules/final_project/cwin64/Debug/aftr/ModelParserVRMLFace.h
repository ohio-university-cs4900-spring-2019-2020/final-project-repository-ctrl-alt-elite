//----------------------------------------------------------------------------
//Description: The ModelParserVRMLFace class is the instantiation of 3 connected 
//verticies in three-space.  This is a 3D polygon with exactly 3 edges and 
//3 verticies.  Additionally, each ModelParserVRMLFace has a corresponding normal vector
//that dictates the direction perpendicular to the surface of the polygon.
//
//Users shall NEVER call public methods from THIS class. Users shall ONLY call
//public methods of the Model Class.
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once

#include <vector>
#include <string>
#include "Vector.h"
#include "AftrOpenGLIncludes.h"


//----------------------------------------------------------------------------
//Description: The ModelParserVRMLFace class is the instantiation of 3 connected 
//verticies in three-space.  This is a 3D polygon with exactly 3 edges and 
//3 verticies.  Additionally, each ModelParserVRMLFace has a corresponding normal vector
//that dictates the direction perpendicular to the surface of the polygon.
//----------------------------------------------------------------------------
namespace Aftr
{

class TextureVertex;
class ModelParserVRMLShape;

class ModelParserVRMLFace
{
public:
   //-------------------------------------------------------------------------
   //Constructor that instantiates a new ModelParserVRMLFace. The ModelParserVRMLFace is created
   //from the indexes contained within the string and uses these indexes to
   //point to the actual verticies from the parenting ModelParserVRMLShape's list of
   //verticies.
   //str: string containing 3 indexes referring to actual 
   //verticies contained within the parenting ModelParserVRMLShape's list of verticies.
   //These verticies are then stored locally inside of the face.
   //verticies: reference to the parenting ModelParserVRMLShape's list of verticies.
   //-------------------------------------------------------------------------
   ModelParserVRMLFace( ModelParserVRMLShape* parentModelShape, std::string str, 
              const std::vector< Vector* >& verticies, 
              std::vector< int >& indicies );

   //-------------------------------------------------------------------------
   //Destructor that deletes and NULL-ifys all pointers owned by this 
   //instance.
   //-------------------------------------------------------------------------
   virtual ~ModelParserVRMLFace();

   //-------------------------------------------------------------------------
   //This method parses indexes to textures passed in via the string and uses
   //these indexes to point to the actual texture verticies from the parenting
   //ModelParserVRMLShape's list of texture verticies.
   //string str: string containing indexes to the corresponding texture
   //verticies.
   //textureVerticies: reference to the parenting ModelParserVRMLShape's list of texture
   //verticies.
   //-------------------------------------------------------------------------
   void setTextureIndicies( const std::string& str, 
                 const std::vector< TextureVertex* >& textureVerticies );

   //-------------------------------------------------------------------------
   //Rasterizes the complex 3 Dimensional image and places the rasterization
   //in the current OpenGL buffer. This essentially "draws the ModelParserVRMLShape" to
   //the screen.
   //-------------------------------------------------------------------------
   void render( const Camera& cam );


   //-------------------------------------------------------------------------
   //Rasterizes the complex 3 Dimensional image and places the rasterization
   //in the current OpenGL buffer. This essentially "draws the ModelParserVRMLFace" to
   //the screen.The ModelParserVRMLFace is drawn in ONE solid color; this is useful
   //for OpenGL Selection.
   //-------------------------------------------------------------------------   
   void renderSelection( GLubyte red, GLubyte green, GLubyte blue );

   ModelParserVRMLShape* getParentModelShape(){ return this->parentModelShape; }

   void setFaceNormal( int i, Vector* newNormal ) ;
   const Vector* getFaceNormal(int i) { return this->normal.at(i); }
   const std::vector< int >& getIndexOfVerts() { return this->indexOfVerts; }

   std::vector<int>* getNeighbours(){return &neighbours;}
   std::vector<bool>* getVisibleToLights(){return &visibleToLights;}

   //-------------------------------------------------------------------------
   //This method computes a normal vector.  That is, it creates a vector that
   //is perpendicular to the polygon formed from the face's 3 verticies. The
   //normal vector has a magnitude of exactly one.
   //-------------------------------------------------------------------------
   void calculateNormalOfFace();

protected:
   
   std::vector< Vector* > verts;   //Stores all verticies of this ModelParserVRMLFace
   std::vector< int > indexOfVerts;
   std::vector< TextureVertex* > textureVerts; //Stores all texture verticies
   std::vector<Vector*> normal;                  //This face's normal vector
   std::vector<int> neighbours;                  
   std::vector<bool> visibleToLights;

   ModelParserVRMLShape* parentModelShape;
};
} //namespace Aftr
