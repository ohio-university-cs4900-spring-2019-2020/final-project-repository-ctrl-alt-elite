#pragma once
#include "Mat4Fwd.h"

namespace Aftr
{

class ModelMesh;
class Camera;

class ModelMeshLOD
{
public:
   ModelMeshLOD( ModelMesh* parentMesh );
   virtual ~ModelMeshLOD();
   /// This method is invoked by the engine each frame prior to this instance's render method.
   virtual void onUpdateLOD() = 0;
   /// Renders the billboard representing this mesh. The engine calls this on this instance once per frame.
   virtual void render( const Camera& cam ) = 0;
   /**
      This is a convenience method for developers and debugging. It is a hook to invoke / request 
      a complete update on this instance. The intention of this method is to immediately update the LOD to the
      to its minimal error instead of only performing an iterative and fast update (like onUpdateLOD()).
      
      Many LOD techniques have internal logic which monitor their current error metric and only perform 
      expensive error correcting computations when the error becomes too large. This method basically assumes
      the error threshold has become too great.

      Some LOD techniques may not have an analgous use for this method; if this is the case, overload this method
      to invoke this instance's onUpdateLOD().
   */
   virtual void onFullUpdateLOD() = 0;
   void setDoFullUpdateNextRender( bool performOnFullUpdateLOD );
   bool setDoFullUpdateNextRender();
   virtual ModelMeshLOD* cloneMe() = 0;

protected:
   ModelMesh* parentMesh; ///< Points to the ModelMesh this LOD represents, not owned, do not delete
   bool performFullUpdateNextRender; //if true, onFullUpdateLOD will be invoked before this instance is rendered.
};

} //namespace Aftr

