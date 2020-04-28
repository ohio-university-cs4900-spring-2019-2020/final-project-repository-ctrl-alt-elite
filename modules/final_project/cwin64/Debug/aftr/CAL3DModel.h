#pragma once
#ifdef AFTR_CONFIG_USE_CAL3D

#include <fstream>
#include <string>
#include <vector>
#include "AftrOpenGLIncludes.h"
#include "cal3d/cal3d.h" //this way, a user simply need include CAL3DModel.h
                         //in Aftr Modules and doesn't need to know about
                         //the CAL3D include files.

namespace Aftr
{
   class CAL3DModelData;
}

/**
   \class CAL3DModel
   This class represents a CAL3D Model (Character Animation Library). These models are typically
   read in from a .cfg file and support skeletal animation, material properties, mesh hierachies,
   etc. These models can be directly exported from 3DS Max after installing the CAL3D Max Exporter.
   This exporter is located in the Aftr Repository at
   Aftr\trunk\engine\src\cal3d-0.11rc2\plugins\max9_cal3d_exporter. The install instructions
   reside in that folder as well.

   This class encapsulates all the needed animation methods to cause the model to play any desired
   animation any number of times in combination with other animations simultaneously.
*/

class CAL3DModel
{
public:
   friend class Aftr::CAL3DModelData;
   CAL3DModel( CalCoreModel* calCoreModel );
   virtual ~CAL3DModel();

   /**
      Play the animation represented by animationID exactly once. The weight indiciates
      how influential this particular animation is on the model. If two animations are
      simultaneously running on one model, Cal3D automatically blends the two 
      animations' influences (based on the weight) upon the model and causes the model to move
      as a combination of those two weights. Many animations can be playing simultaneously
      on a single model.

      \param animationID The ID of the animation to be played exactly once (generated by Cal3D at load time).
      \param weight A float between (0.0,1.0] indicating how much influence this particular
                    animation has over the model.
      \param fadeInDelay The delay until the given weight will be reached (in seconds).
      \param fadeOutDelay The delay until the animation reaches a weight of zero after playing one time (in seconds).
   */
   void animationPlayAction( int animationID, float weight, float fadeInDelay, float fadeOutDelay );

   /**
      Continuously play the animation represented by animationID. The weight indiciates
      how influential this particular animation is on the model. If two animations are
      simultaneously running on one model and both have weights of 0.5, Cal3D automatically
      blends the two animations' influences upon the model and causes the model to move
      as a combination of those two weights. Many animations can be playing simultaneously
      on a single model.

      \param animationID The ID of the animation to be played repeatedly (generated by Cal3D at load time).
      \param weight A float between (0.0,1.0] indicating how much influence this particular
                    animation has over the model.
      \param fadeInDelay The delay until the given weight will be reached (in seconds).
   */
   void animationPlayLoop( int animationID, float weight, float fadeInDelay );

   /**
      Stops playing animationID on this model; animationID's weight will be zero after
      fadeOutDelay seconds elapses.
      \param fadeOutDelay The time, in seconds, before animationID has a weight of zero.
   */
   void animationStop( int animationID, float fadeOutDelay );

   /**
      Stops all current animations on this model; all animation weights will be zero after
      fadeOutDelay seconds elapses.
      \param fadeOutDelay The time, in seconds, before all running animations have a weight of zero.
   */
   void animationStopAll( float fadeOutDelay );

   //void executeAction( int action ); //should be cleaned up
   const std::vector< int >& getAnimationList(); ///< Returns a vector of available animations this CAL3DModel can use.
   float getLodLevel(); ///< Returns the current Level Of Detail (LOD) of this Cal3D instance model
   void setLodLevel( float lodLevel ); ///< Sets this instance Cal3D model's Level Of Detail. This is somewhat expensive, do not call every render.
   float getRenderScale();
   bool initCalCoreModel( const std::string& strFilename ); ///< Called by ManagerCAL3DModelMultiplicity when creating an CalCoreModel*. A User should not need to explicitly invoke this method.
   bool initCalModelInstance( const Aftr::CAL3DModelData* data ); ///< Called by ManagerCAL3DModelMultiplicity when creating an instance CalModel*. A User should not need to explicitly invoke this method.
   void onRender(); ///< Renders this CAL3DModel
   void onUpdate(float elapsedSeconds); ///< Simulates all current animations forward by elapsedSeconds. This should be called periodically to ensure smooth animations.
   void setPath( const std::string& strPath ); ///< Set a path to override any config file path. Aftr automatically sets the correct path for the cal3d model.
   std::string getFileName() { return this->fileName; } ///< Returns the config file this CAL3DModel's CalModel* is an instance of.
   CalModel* getCalModel(); ///< Returns a pointer to the internal Cal3D CalModel instance.
   std::string toString(); ///< Returns a string containing information about this CAL3DModel instance.
   static int readInt( std::ifstream* file ); ///< Static method used by CAL3DModel::loadTexture()'s parser for reading ints from the config file without endian issues occurring.
   //void setState(int state, float delay); //remove!!!

protected:
   GLuint loadTexture(const std::string& strFilename); ///< At load time, all associated textures are loaded to OpenGL.
   void renderMesh(bool bWireframe, bool bLight); ///< Renders this model at the current Level Of Detail.
   void renderSkeleton(); ///< Renders the skeletal frame used as the envelopes of influence by this model.
   void renderBoundingBox(); ///< Renders this Cal3DModel's bounding boxes for each mesh

   bool isValidAnimationID( int animationID );

   CalCoreModel* calCoreModel; ///< CalCoreModel associated with this Object's CalModel instance.
   CalModel* calModel; ///< CalModel wrapped by this Object.

   //CAL3DModelData BEGIN
   std::vector< int > animationList; ///< List of available animations this instance can currently use.
   float m_renderScale;//maybe remove this if its not gonna be used?
   float lodLevel; ///< Current Level of detail the meshes of this model are rendered at. Range is (0,1.0].
   std::string pathToFileName; ///< Path to the folder where the config file is located. Used by the parser in CAL3DModel::initCalCoreModel().
   std::string fileName; ///< Name of the config file this CAL3DModel's corresponding CalModel* is an instance of.
   //CAL3DModelData END
};

#endif //AFTR_CONFIG_USE_CAL3D