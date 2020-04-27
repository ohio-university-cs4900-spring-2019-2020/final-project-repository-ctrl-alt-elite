#pragma once
#include <set>
#include "Mat4Fwd.h"

namespace Aftr
{

class Model;
class ModelMesh;
class Camera;

class ModelLODPolicy
{
public:
   ModelLODPolicy( Model* parentModel );
   virtual ~ModelLODPolicy();
   virtual void onApplyPolicy( const std::set< ModelMesh* >& visibleMeshesForThisFrame, const Mat4& modelMatrix, const Mat4& normalMatrix, const Camera& cam );
   bool isEnabled() { return this->IsEnabled; }
   void isEnabled( bool isEnabled ) { this->IsEnabled = isEnabled; }
   void setTimeInMSForNextPolicyApplication( unsigned int timeInMS );
   unsigned int getTimeInMSForNextPolicyApplication() { return this->timeMS; }

protected:

   Model* parentModel;
   bool IsEnabled; ///< If true, this policy is currently active, and its onApplyPolicy() will be invoked by
                   ///< the parent model's render method
   unsigned int timeMS; ///< Time in milliseconds the onApplyPolicy() method has to complete its task

};

}

