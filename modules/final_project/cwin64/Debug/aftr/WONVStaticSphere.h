//#pragma once
//#include "AftrConfig.h"
//#ifdef AFTR_CONFIG_USE_NV_PHYSX
//
//#include "WONVPhysX.h"
//
//namespace Aftr
//{
//
//class WONVStaticSphere : public WONVPhysX
//{
//public:
//   
//   /**
//       Default constructor, sets pointers to NULL, sets everything up to be a static or ghost world object
//   */
//   static WONVStaticSphere* New();
//
//   /**
//       Constructor, accepts a vrml file as a parameter and processes the file and creates a graphical and physical model of the file
//       \param modelFileName The path to the model's filename.
//   */
//   static WONVStaticSphere* New( const std::string& modelFileName, const Vector& scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );
//
//   virtual ~WONVStaticSphere();
//
//   //Must implement the abstract virtual methods defined in IFaceWONVStaticSphere interface
//   virtual void onCreateNVPhysXActor();
//   //virtual void updatePoseFromPhysicsEngine();
//
//protected:
//   WONVStaticSphere();
//   virtual void onCreate( const std::string& modelFileName, const Vector& scale, MESH_SHADING_TYPE shadingType );
//   virtual void onCreate();
//
//
//};
//
//} //namespace Aftr
//
//
//#endif //AFTR_CONFIG_USE_NV_PHYSX
//