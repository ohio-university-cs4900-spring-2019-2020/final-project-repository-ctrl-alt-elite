#pragma once

#include "AftrGlobals.h"
#include "Vector.h"
#include "AftrOpenGLIncludes.h"
#include <string>

namespace Aftr
{

class ModelDataShared;

/**
   This class provides an interface allowing an arbitrary formatted model
   to be converted into a Aftr Model that is rendered quickly as an
   Indexed Geometry VBO or VA.

   The user inherits from this file and overloads this class's parse()
   method. The user then creates a ModelDataShared instance and properly
   populates it. After population is complete, the user returns a pointer
   to the newly created object and the Aftr Engine will register the
   structure with the multiplicity manager and then many instances of that
   same object can be created using one shared collection of geometry
   information. Each instance can modify all skin/texture properties
   independent of each other.

   To Populate a ModelDataShared Object:
      1) Create a std::vector< ModelMesh* > meshes. (Each mesh is a collection of geometry that shares 
         a skin/texture/shader).
         1.1) For each ModelMesh:
             1.1.1) Create a ModelMeshRenderDataGenerator object:
                Insert verticies, indicies, and set of sets of texture coordinates (multitexturing). 
                One tex coord must exist for each vertex (VBO/
                VA - Indexed Geometry requirement). Mulitple sets
                of texture coordinates and texture dimensionalities
                can be inserted into the vector of texture coordinates.
                Each parallel texture represents a set of textures used
                on the corresponding ModelMesh for multitexturing.
            1.1.2) Create a ModelMeshDataShared Object and pass the newly
                created ModelMeshRenderDataGenerator object into the constructor. The
                ModelMeshDataShared Object takes ownership of the in passed
                ModelMeshRenderDataGenerator Object; the user should not delete the
                ModelMeshRenderDataGenerator Object.
            1.1.3) Create a ModelMeshSkin:
                Set all colors, materials, shaders, and shading type to the
                desired values.
         1.2) Create a ModelMesh instance passing in the newly created ModelMeshSkin
              and the ModelMeshDataShared instances. Insert this ModelMesh instance
              into a std::vector< ModelMesh* >.
      2) Create a ModelDataShared instance passing in the std::vector< ModelMesh* > meshes.
      3) Internally, the ModelDataShared Object makes a copy of the std::vector< ModelMesh* >;
         as a result, the user is responsible for deleting the vector of ModelMeshes before
         returning the newly created ModelDataShared instances to avoid memory leaks.
      4) Return the newly created ModelDataShared pointer.

*/
class ModelParser
{
public:
   /**
      Base class for a parser that reads a file and returns a ModelDataShared*.
   */
   ModelParser( const std::string& fileName, const Vector& scale, const MESH_SHADING_TYPE& shadingType );

   /**
      Destructor for base parser
   */
   virtual ~ModelParser();

   /**
      Returns the ModelDataShared* if successfully parsed file; NULL, otherwise.
   */
   virtual ModelDataShared* parse() = 0;
   std::string getModelFileName() { return this->fileName; }
protected:
   std::string fileName; ///< file name of the model to be parsed
   Vector scale; ///< Scale of the model to be parsed
   /**
      MESH_SHADING_TYPE::mstSMOOTH - this parser will set all default skins to smooth shaded
      MESH_SHADING_TYPE::mstFLAT - this parser will set all default skins to flat shaded
      MESH_SHADING_TYPE::mstAUTO - this parser will set each skin to either MESH_SHADING_TYPE::mstSMOOTH or MESH_SHADING_TYPE::mstFLAT dependent upon
                information specified within the file. If the file does not specify shading
                information, then each skin will be set to smooth shaded
   */
   MESH_SHADING_TYPE shadingType;
};

} //namespace Aftr

