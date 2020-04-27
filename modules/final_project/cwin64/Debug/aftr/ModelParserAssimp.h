#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ASSIMP

#include "ModelParser.h"

namespace Aftr
{

/**
* \brief The Assimp model parser is defined by this class.
* Due to the large verity of model formats that Assimp can handle it is a good idea to support import using this fantastic tool.
* 
*/
   class ModelParserAssimp : public ModelParser
   {
   public:
      ModelParserAssimp( const std::string& filename, const Vector& scale, const MESH_SHADING_TYPE& shadingType );      
      virtual ~ModelParserAssimp() override;
      ModelDataShared* parse() override;

      //https://stackoverflow.com/questions/28786387/c-pimpl-idiom-imcomplete-type-using-stdunique-ptr?rq=1
      //Need to define defaulted constructors and operator assignments so the compiler doesn't inline them
      //when this class is only forward declared

      //ModelParserAssimp( const ModelParserAssimp& noCopy );
      //ModelParserAssimp( ModelParserAssimp&& noMove );
      //ModelParserAssimp& operator=( const ModelParserAssimp& noAssign );
      //ModelParserAssimp& operator=( ModelParserAssimp&& noMoveAssign );

   protected:

      class Pimpl;
      Pimpl* impl = nullptr;

   };   
}

#endif //AFTR_CONFIG_USE_ASSIMP
