//#pragma once
//#include "AftrConfig.h"
//#ifdef AFTR_CONFIG_USE_NV_PHYSX
//
//#include "PxPhysicsAPI.h"
//#include "WONVPhysX.h"
//#include "WOLightWave.h"
//
//namespace Aftr
//{
//
//struct NVFluidParticle;
//
//class WONVFluid : public WONVPhysX
//{
//public:
//   static WONVFluid* New( const Vector& initialPos, const Vector& initialExtents, unsigned int numParticles, float* initialOrientation = NULL );
//   virtual ~WONVFluid();
//
//   virtual void onCreateNVPhysXActor();
//   virtual void updatePoseFromPhysicsEngine();
//
//   virtual float getFluidViscosity();
//   virtual void setFluidViscosity( float newViscosity );
//
//   virtual void setClippingBorderMaxPt( const Vector& clipMax );
//   virtual void setClippingBorderMinPt( const Vector& clipMin );
//
//   virtual void render( const Camera& cam );
//   virtual void renderVelocityVectors();
//
//   /// p must be between [ 0, 1.0 ]
//   void setPercentageOfRenderVelocityVectorsToRender( float p );
//   void setRenderVelocityVectors( bool renderVelVectors ) { this->RenderVelocityVectors = renderVelVectors; }
//   bool setRenderVelocityVectors() { return this->RenderVelocityVectors; }
//
//protected:
//   virtual void onCreate();
//   WONVFluid( const Vector& pos, const Vector& initialExtents, unsigned int numParticles, float* initOrient = NULL );
//
//   virtual void createInitialFluidState( NxFluidDesc& desc );
//   virtual void createFluid( NxFluidDesc& desc );
//
//   //Taken from PhysX SDK
//   void createParticleAABB( NxParticleData& pd, unsigned maxParticlesTotal, unsigned maxParticles, bool append, NxBounds3& aabb, const NxVec3 vel, float lifetime, float distance );
//   void createParticleSphere( NxParticleData& pd, unsigned maxParticles, bool append, const NxVec3& pos, const NxVec3 vel, float lifetime, float distance, unsigned sideNum );
//
//   NVFluidParticle* pBuf; //< Particle Buffer that gets data to/from the simulation
//   unsigned int pBufSize; //< Number of particles updated back by PhysX simulation this tick
//   NxFluid* fluid; //< Pointer to the NVIDIA PhysX fluid
//   NxU32 maxParticles; //< Max number of particles allocated inside of this->pBuf
//
//   //Initialization variables, deleted and not used after the fluid is fully created
//   //and sent to PhysX
//   NVFluidParticle* initParticles;
//   unsigned int initParticlesNum;
//   float initOrient[16];
//   Vector initStartPos; ///< Initial starting position of the fluid (center point)
//   Vector initExtents; ///< Initial lengths in each dimension of the aabb
//
//   bool RenderVelocityVectors; ///< if true, particle velocity vectors are visualized
//   float PercentOfVelVecsToRender;
//   std::set< unsigned int > velVecIDsToRender;
//
//   WOLightWave* velVec; ///< Graphical representation of particle velocity vectors
//
//};
//
///**
//   Stores elements which can be received from the SDK.
//*/
//struct NVFluidParticle
//{
//   NxVec3 position;
//   NxVec3 velocity;
//   NxReal density;
//   NxReal lifetime;
//   NxU32 id;
//   NxVec3 collisionNormal;
//};
//
//} //namespace Aftr
//
//#endif //AFTR_CONFIG_USE_NV_PHYSX
//