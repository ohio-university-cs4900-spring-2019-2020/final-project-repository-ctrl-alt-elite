#pragma once

#include "Vector.h"

namespace Aftr
{

class Camera;
class WO;
class ModelMesh;

class AftrFBOTargetBillboardInfo
{
public:
   AftrFBOTargetBillboardInfo();
   virtual ~AftrFBOTargetBillboardInfo();
   void computeFromCamAndWO( Camera* cam, WO* wo );
   void computeFromCamAndModelMesh( Camera* cam, ModelMesh* mesh );
   void computeFromCamAndWOCachingIntermediateState( Camera* cam, WO* wo );
   void computeFromCamAndModelMeshCachingIntermediateState( Camera* cam, ModelMesh* mesh );
   void computeFromCamAndWSVecs( Camera* cam, const Vector& bbLxLyWS, const Vector& inBillboardCenterInWS );
   float dispMat[16]; ///< Orientation of the billboard w.r.t the camera
   Vector posWS; ///< World Space global position of the billboard
   Vector lxlyWS; ///< World Space lengths of the billboard; x component is the width of the billboard, y component is the height
};

} //namespace Aftr

