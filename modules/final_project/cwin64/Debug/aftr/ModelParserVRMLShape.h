//----------------------------------------------------------------------------
//Description: The ModelParserVRMLShape class is the instantiation of a collection of
//faces which are adjacent and share the same texture.
//
//Users shall NEVER call public methods from THIS class. Users shall ONLY call
//public methods of the ModelParserVRML Class.
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

//----------------------------------------------------------------------------
//Description: The ModelParserVRMLShape class is the instantiation of a collection of
//faces which are adjacent and share the same texture.
//----------------------------------------------------------------------------
namespace Aftr
{

class BoundingBox;
class ModelParserVRMLFace;
class TextureVertex;
class ModelParserVRML;

class ModelParserVRMLShape
{
public:
	//-------------------------------------------------------------------------
	//Constructor that instantiates a new ModelParserVRMLShape.
	//-------------------------------------------------------------------------
	ModelParserVRMLShape( ModelParserVRML* parentModel );

	//-------------------------------------------------------------------------
	//Destructor that deletes and NULL-ifys all pointers owned by this 
	//instance.
	//-------------------------------------------------------------------------
	virtual ~ModelParserVRMLShape();

	//-------------------------------------------------------------------------
	//This method is the core of the VRML Parser.  It is responsible for 
	//ensuring the Texture File Name, Verticies, Texture Verticies, Face
	//indicies, and texture indicies are all read in and parsed appropriately.
	//sr: input stream to the VRML data being read in.
	//bBox: the bounding box responsible for determining
	//the center point of the 3D ModelParserVRML.
	//-------------------------------------------------------------------------
	bool readModelVrml( std::ifstream* sr, BoundingBox* bBox, const Vector& scale );

	std::vector< Vector* >* getOriginalVertexList() { return &verticies; }
	std::vector< int >* getOriginalIndexList() { return &indicies; }

   std::vector< TextureVertex* >& getTextureVerticies() { return this->textureVerticies;}
   std::vector< GLuint >& getTextureCoordIndicies() {return this->textureCoordIndicies;}
   
   std::vector< std::string >& getTextureNames() { return textureNames; }


	//-------------------------------------------------------------------------
	//This method binds the shape's current texture to OpenGL and then
	//rasterizes the complex 3 Dimensional image and places the rasterization
	//in the current OpenGL buffer. This essentially "draws the ModelParserVRMLShape" to
	//the screen with the appropriate texture. The ModelParserVRMLShape is drawn in 
   //ONE solid color; this is useful for OpenGL Selection.
	//-------------------------------------------------------------------------   

   ModelParserVRML* getParentModel() { return this->parentModel; }

   void setShadingFlat();
   void setShadingSmooth();

   //Used by vertex lists
   std::map<int, Vector>* getNormals(){return &normals;}

   ///for flat shading add in duplicate vertices
   int duplicateVerticesForFlatShading();

   ///texture correction
   std::vector<int> replicateVerticesForTextureCorrection();

protected:

	//-------------------------------------------------------------------------
	//Sets the input stream just past the first occurance of the specified 
	//string.
	//sr: input file stream of a VRML file generated from Q3BSP.EXE
	//s: string to search for within the input stream.
	//RETURN: true if string was found and input stream was set successfully, 
	//false otherwise.
	//-------------------------------------------------------------------------
	bool lookFor( std::ifstream* sr, std::string s );

	//-------------------------------------------------------------------------
	//Searches the input stream for the first occurance of a texture file name
	//and reads it in.
	//sr: the input stream through which to search.
	//RETURN: bool: true if a texture file name was found and read in 
	//successfully; false, otherwise.
	//-------------------------------------------------------------------------
	bool readTextureFileName( std::ifstream* sr );

	//-------------------------------------------------------------------------
	//Searches the input stream for the first occurance of a collection of
	//verticies and reads them in.
	//sr: the input file stream through which to search.
	//bBox: the bounding box which finds the minimum and 
	//maximum verticies within the entire ModelParserVRML Object.
	//RETURN: bool: true if a collection of verticies was found and read in 
	//successfully; false, otherwise.
	//-------------------------------------------------------------------------
	bool readVerticies( std::ifstream* sr, BoundingBox* bBox, const Vector& scale );

	//-------------------------------------------------------------------------
	//Searches the input stream for the first occurance of a collection of
	//texture verticies and reads them in.
	//sr: the input file stream through which to search.
	//RETURN: bool: true if a collection of texture verticies was found and 
	//read in successfully; false, otherwise.
	//-------------------------------------------------------------------------
	bool readTextureVertices( std::ifstream* sr );

	//-------------------------------------------------------------------------
	//Searches the input stream for the first occurance of a collection of
	//face indexes and reads them in.
	//sr: the input file stream through which to search.
	//RETURN: bool: true if a collection of face indexes was found and 
	//read in successfully; false, otherwise.
	//-------------------------------------------------------------------------
	bool readFaceIndexes( std::ifstream* sr );

	//-------------------------------------------------------------------------
	//Searches the input stream for the first occurance of a collection of
	//texture indexes and reads them in.
	//sr: the input file stream through which to search.
	//RETURN: bool: true if a collection of face indexes was found and 
	//read in successfully; false, otherwise.
	//-------------------------------------------------------------------------
	bool readTextureIndexes( std::ifstream* sr );

	//-------------------------------------------------------------------------
	//This method eats the leading and trailing whitespace from the passed
	//in string and returns a trimmed string.
	//string s: the string which shall have the leading and trailing
	//white spaces trimmed off.
	//RETURN: a copy of the string with no leading or trailing white space.
	//-------------------------------------------------------------------------
	std::string trimWhiteSpace( const std::string& s );

   //recompute normals that are averaged across shared verticies
   void calcAveragedFaceNormalsAcrossSharedVerts();

	std::vector< ModelParserVRMLFace* > faces; ///Stores all ModelFaces of this ModelParserVRMLShape
	std::vector< Vector* > verticies; ///Stores all verticies of this ModelParserVRMLShape
	std::vector< int > indicies; ///Stores all indicies into the verticies of this ModelParserVRMLShape
	std::vector< TextureVertex* > textureVerticies; ///Stores all texture verticies
   std::map<int, Vector > normals;
   std::vector< GLuint > textureCoordIndicies;


   std::vector< std::string > textureNames;    ///the paths to the textures


   bool isBlenderVRML;

   ModelParserVRML* parentModel;

   void mapNeighbourhood();
   void mapLightVisibility();

   
};

} //namespace Aftr
