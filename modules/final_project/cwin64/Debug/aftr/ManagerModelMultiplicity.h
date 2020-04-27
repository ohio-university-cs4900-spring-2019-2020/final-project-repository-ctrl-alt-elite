#pragma once

#include "AftrGlobals.h"
#include "AftrOpenGLIncludes.h"
#include "ModelDataSharedID.h"
#include "Vector.h"
#include <string>
#include <map>

namespace Aftr
{

class ModelDataShared;

/**
   This class manages all multiplicities of all ModelDataShared objects that
   were loaded from a file format such as .3ds or .wrl.
*/

enum class RENDER_HW_MODE : unsigned char { rhmVA_VERTEX_ARRAY, rhmVBO_VERTEX_BUFFER_OBJECT, rhmNUM_RENDER_HW_MODE };
std::ostream& operator<<( std::ostream& out, const RENDER_HW_MODE& rhm );

class ManagerModelMultiplicity
{
public:
   static void init();
   static void shutdown();
   /**
      Loads and manages all multiplicities of a model's geometry, textures, colors, material
      properties, shaders, etc. The in passed modelData is overwritten by this method. When
      this method returns, modelData points to the valid ModelDataShared object populated
      from the corresponding file.
   */
   static void loadModelDataShared( ModelDataShared** modelData, const std::string& modelFileName, 
                                    const Vector& scale, const MESH_SHADING_TYPE& shadingType );
   
   ///This method is called automatically within a ModelDataShared destructor. Internally, this calls
   /// destroyModelSahredData(...) to free the memory of the 
   static void unRegisterOneModelDataSharedInstance( const ModelDataSharedID& id );

   /// This method is used by unRegisterOneModelDataSharedInstance
   static void destroyModelSharedData( ModelDataShared* s );

   static RENDER_HW_MODE getRenderMode() { return hardwareRenderMode; }
   static void sendModelDataSharedServerSide( ModelDataShared* m );
protected:

   static ModelDataShared* getModelDataSharedFromFile( const std::string& modelFileName,
                               const Vector& scale, const MESH_SHADING_TYPE& shadingType );

   static RENDER_HW_MODE hardwareRenderMode; ///< If VBOs are supported, they are used; otherwise, VAs are used.
   static std::map< ModelDataSharedID, ModelDataShared* > models;

};

} //namespace Aftr

