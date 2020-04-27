#pragma once

#include "MGLWayPointAbstract.h"

namespace Aftr
{
   class Camera;
   class IndexedGeometrySphereTriStrip;

   class MGLWayPointSpherical : public MGLWayPointAbstract
   {
   public:
      MGLWayPointSpherical( WOWayPointAbstract* parent = NULL ///parent WOWayPoint that uses this model
         );
      virtual ~MGLWayPointSpherical();
      virtual void renderMe( const Camera& cam );
   protected:
      IndexedGeometrySphereTriStrip* sphere;
      ModelMeshSkin redSkin;
      ModelMeshSkin greenSkin;
   };


}  //namespace Aftr

