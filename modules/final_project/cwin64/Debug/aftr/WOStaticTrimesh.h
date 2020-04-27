//----------------------------------------------------------------------------
//Description: The WOStaticTrimesh is a WOStatic which uses
//an ODE Trimesh (mapped exactly to the graphical vertices) as its physics 
//representation.
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOStatic.h"

//----------------------------------------------------------------------------
//Description: The WOStaticTrimesh class 
//----------------------------------------------------------------------------
namespace Aftr
{

class WOStaticTrimesh : public WOStatic
{

public:
   static WOStaticTrimesh* New( const std::string& modelFileName, Vector scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );
   static WOStaticTrimesh* New( const std::string& modelFileName,  MESH_SHADING_TYPE shadingType, Vector scale = Vector(1,1,1) );

   virtual ~WOStaticTrimesh();

   //Creates the ODE Geom of the static object
   virtual void ODEinitializeInODE();


   virtual dReal* getTriMeshVertexList() { return this->triMeshVertexList; }
   virtual unsigned int* getTriMeshIndexList() { return this->triMeshIndexList; }
   virtual unsigned int getTriMeshVertexListLength() { return this->numTriMeshVertexEntries; }
   virtual unsigned int getTriMeshIndexListLength() { return this->numTriMeshIndexEntries; }

   //ODE specific data for a TriMesh
   dGeomID odeGeomID; //saved since this may become useful in the future

protected:
   WOStaticTrimesh();

   dReal* triMeshVertexList; //Used in ODEinitializeInODE to create a vertex list used for the ODE Trimesh.
   unsigned int* triMeshIndexList;    //Used in ODEinitializeInODE to create an index list used for the ODE Trimesh.
   unsigned int numTriMeshVertexEntries; //Length of triMeshVertexList
   unsigned int numTriMeshIndexEntries;  //Length of triMeshIndexList

};
} //namespace Aftr
#endif
