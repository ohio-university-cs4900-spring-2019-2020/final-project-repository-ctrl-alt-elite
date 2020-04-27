#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_CAL3D

#include <string>
#include <map>
#include <vector>

class CAL3DModel;
class CalModel;
class CalCoreModel;

namespace Aftr
{

class CAL3DModelData
{

public:
   CAL3DModelData( const std::vector< int >& animationList,
                   float renderScale, float lodLevel,
                   std::string path, std::string fileName );
   CAL3DModelData( CAL3DModel* cal3DModel );
   virtual ~CAL3DModelData();

   std::vector< int > animationList;
   float m_renderScale;
   float lodLevel;
   std::string pathToFileName;
   std::string fileName;
   void incrementNumInstances() { ++this->numInstances; }
   void decrementNumInstances() { --this->numInstances; }
   int getNumInstances() { return this->numInstances; }

protected:
   void populateData( const std::vector< int >& animationList,
                      float renderScale, float lodLevel,
                      std::string path, std::string fileName );

   int numInstances;
};

class ManagerCAL3DModelMultiplicity
{
public:
   static void init();
   static CAL3DModel* loadModel( const std::string& configFilePath );
   static void removeInstanceModel( const std::string& configFilePath );
   static void deleteAllModels();

protected:
   /**
      Loads a Cal3D Core Model from file, initializes it, and places it
      in the Manager's list of currently loaded CalCoreModels.
      Returns true iff CalCoreModel is properly loaded and initialized; false, otherwise.
   */
   static bool createCalCoreModel( const std::string& configFilepath );
   static CAL3DModel* createInstanceCalModel( std::map< std::string, std::pair< Aftr::CAL3DModelData*, CalCoreModel* > >::iterator& it );

   /**
      std::string - the relative path from the working directory to the Cal3D .cfg file that gets loaded
      CAL3DModelData - Data that is not shared between Cal3D instances, but must be properly initialized
                       when an instance is created.
      CalCoreModel - The shared data between all Cal3D Model instances.
   */
   static std::map< std::string, std::pair< Aftr::CAL3DModelData*, CalCoreModel* > > currentCalCoreModels;

};

} //namespace Aftr

#endif //AFTR_CONFIG_USE_CAL3D
