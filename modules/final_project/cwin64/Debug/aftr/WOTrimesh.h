//----------------------------------------------------------------------------
//Description: The WOTrimesh is a WO which uses an ODE
//Trimesh (mapped exactly to the graphical vertices) as its physics 
//representation.
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"

//----------------------------------------------------------------------------
//Description: The WOTrimesh class 
//----------------------------------------------------------------------------
namespace Aftr
{

class WOTrimesh : public WOODE
{

public:
   static WOTrimesh* New( const std::string& modelFileName, Vector scale = Vector(1,1,1) );
   virtual ~WOTrimesh();

   //Creates the ODE Geom of the static object
   virtual void ODEinitializeInODE();

   //We must also preserve the last TriMesh Transformation Matrix so ODE can look
   //"backwards in time" to make collisions more efficient!
   virtual void ODEupdateForcesAndJoints();

   virtual void ODEupdateToNewPositionOrientation();


   virtual dReal* getTriMeshVertexList() { return this->triMeshVertexList; }
   virtual unsigned int* getTriMeshIndexList() { return this->triMeshIndexList; }
   virtual int getTriMeshVertexListLength() { return this->numTriMeshVertexEntries; }
   virtual int getTriMeshIndexListLength() { return this->numTriMeshIndexEntries; }

   //ODE specific data for a TriMesh
   dGeomID odeGeomID; //needs to be saved for preserving the previous TriMesh Transformation Matrix!

protected:
   WOTrimesh();

   dReal* triMeshVertexList; //Used in ODEinitializeInODE to create a vertex list used for the ODE Trimesh.
   unsigned int* triMeshIndexList;    //Used in ODEinitializeInODE to create an index list used for the ODE Trimesh.
   unsigned int numTriMeshVertexEntries; //Length of triMeshVertexList
   unsigned int numTriMeshIndexEntries;  //Length of triMeshIndexList

};
} //namespace Aftr
#endif
