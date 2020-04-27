#pragma once

#include <vector>
#include <stack>
#include "SteamieGeometryPlane.h"
//#include <cutil.h>
#include <stdio.h>
#include "WO.h"

//#define VOLATILE_NEIGHBOURHOOD
//#define TESTING_SHADOWS

namespace Steamie
{
   class SteamieGeometryPlane;
   class Model;
      class ShadowNeighbourhood;
   class SteamieFrameBufferObject;

class IFaceShadowCaster
{
public:
   IFaceShadowCaster( WO* wo );
   ~IFaceShadowCaster();
   //virtual void setShadowCasterModel(Model* m) { myModel = m; } //SLN: WO now has WO::setModel(Model* m)
   Model* getMyModel() { return myWO->getModel(); }
   virtual void mapEdgeFaceNeighbourhood();
   #ifdef VOLATILE_NEIGHBOURHOOD
   volatile std::vector<ShadowNeighbourhood>* getNeighbourhood() { return neighbourhood; }
   #else
   std::vector<ShadowNeighbourhood>* getNeighbourhood() { return &neighbourhood; }
   #endif
   std::vector<IFaceShadowCaster*>* getShadowChildren() { return &shadowChildren; }
   void castShadow();
   void useZFail();
   void useZPass();
   GLuint* getTextureHandle() { return textureHandle; }
   std::vector<int>* getKeyFaces() { return &keyFaces; }
   virtual void updateVisibility(const Vector& pos);
   float CUDALoad;
   void displayMyTexture(int x);
   GLuint* textureHandle;
protected:
   bool zfail;
   void ZPass(Vector& pos);
   void ZFail(Vector& pos);
   void shadowPass(Vector& pos);
   void shadowFail(Vector& pos);
   bool hasFace(size_t i, size_t j);
   #ifdef VOLATILE_NEIGHBOURHOOD
   volatile std::vector<ShadowNeighbourhood>* neighbourhood;
   #else
   std::vector<ShadowNeighbourhood> neighbourhood;
   #endif
   std::vector<IFaceShadowCaster*> shadowChildren;
   bool alreadyMapped;
   void findTransformationMatrices();//outermost wrapper for finding the transformation matrices
   void findTransformationMatrices(int x, bool* b);
   void findTransformationMatrices(int x, int y, int f, int s, bool* b);
   std::stack<float*> s;
  
   void updateVisibilityTheirWay();
   void updateVisibilityMyWaySoftware();
   void updateVisibilityMyWayHardware1();
   void updateVisibilityMyWayHardware2();
   void updateVisibilityMyWayFeedback();

   void visibilityTimingTest1();//time CUDA call updateVis then CUDA retrieve

   void shadowTimingTestSuite();
   
   void CUDATestWith();
   void CUDATestWithout();
   void CUDATestBuffer();

   void timeSpentAssigningLightLong();
   void timeSpentAssigningLightShort();
   void timeSpentAssigningOutput();

   void printTheStuff(int i);

   void CUDATestWithoutNoLimit();
   void CUDATestWithoutNoLimitOld();

   void CUDAUpdateVisibilityTest();
   void CUDAUpdateVisibilityTest2();
   void CUDAUpdateVisibilityTestNoAssign();
   void CUDAUpdateVisibilityTestLongNoAssign();
   void updateVisibilityMyWayCUDA2();

   void updateVsibilityMyWaySoftwareNoAssign();

   void CUDARetrieve();
   void CUDAKernal();
   void CUDAKernalSynch();
   void CUDASend();
   void CUDASendLong();
   void CUDAAssignLightLong();
   void CUDAKernalNew();

   void constructCUDAHost();

   void comparison1(size_t x);
   void comparison2(size_t x);

   void updateVisibilityTheirWayAt();
   void assignOutputNotAt();

   void assignOutputFrom4Arrays();
   void timeSpentDoing4Memcpys();

   //key faces and key face networks are needed for my implemenation of the contour edge identification
   std::vector<int> keyFaces;
   std::vector<std::vector<int> > keyFaceNetworks;
   Vector transformedPosition;

   //the following are used for storing precomputed information on the graphics card
   void createTexture();
  
   //FBO for hardware 2 mode
   SteamieFrameBufferObject** fbos;

   //stuff for CUDA method - do not use unless you know what you are doing
   void loadNeighbourhoodIntoCUDA();
   void updateVisibilityMyWayCUDA();
   void constructCUDA();
   void destroyCUDA();
   float* device_neighbourhood;
   float* device_lightPosition;
   float* device_output;
   float* host_neighbourhood;
   float* host_lightPosition;
   float* host_output;
   
   size_t size_neighbourhood;
   size_t size_lightPosition;
   size_t size_lightPositionSmall;
   size_t size_output;

   unsigned int sendTime;
   unsigned int recievedTime;
   unsigned int kernalTime;
   unsigned int allTime;
   unsigned int allTimeWithSynching;
   unsigned int theirTime;
   unsigned int assigningLightTime;
   unsigned int sendLongTime;
   unsigned int kernalNewTime;

   int counter;
 
   GLubyte* hardwareBuffer;
   int hardwareSize;

   WO* myWO;//used to keep track of the other side of the multiple inheritance

 //  float* extraBuffer;
};

}

