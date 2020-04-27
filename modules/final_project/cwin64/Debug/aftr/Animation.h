//----------------------------------------------------------------------
//----------------------------------------------------------------
// Description: The animation class to handle all animations and 
//              movements of objects
// Author: Mitchell Leitch
//----------------------------------------------------------------

#pragma once

#include <vector>
#include <string>

namespace Aftr
{

class WO;
class WOGJoint;


/**
   \class Animation
   \author Mitchell Leitch. Updated to get rid of animation manager Oct 10 2014
   \brief The animation class that will animate the WO it is associated with it
   \This animation class will be able to read the animation from a text file and be able to write the animation to a text file.
   \This encompasses all of the objects animation, so that a WO needs to know only the text file and the WOGJoints that are 
   \being animated. The user must pass the WOGJoints in order that they are ordered in the animation file.
   \{
   */

class Animation
{
public:

   /**Default constructor, allowing for an empty set of animations*/
   Animation();

   /**Constructor which takes a path to a filename.
      This file will contain a 'xmlesque' structure which will populate the animation keyframes.
      jointOrder is a vector of joints, this is usually defined later, but at some point this MUST be defined
      if the animation will work.
      \param animationFilename - the path to the animation
      \param jointOrder - a vector of the joints that will be animated*/
   Animation( const std::string& animationFilename, std::vector< WOGJoint* >* jointOrder = NULL);

   /**Destructor.
      Will clean up any newed data.*/
   virtual ~Animation();

   /**Accessor to get all of the animations for a world object*/
   std::vector< std::vector< std::vector < float >* >* >* getAnimation() { return keyframes; }
   /**Accessor to get all of the animations for a specific joint*/
   std::vector< std::vector< float >* >* getJointAnimation(int jointNumber) { return keyframes->at(jointNumber); }
   /**Accessor to get a specific keyframe from a joint*/
   std::vector< float >* getJointKeyframe(int jointNumber, int keyframe) { return keyframes->at(jointNumber)->at(keyframe); }

   /**Accessor to the filename of the animation*/
   std::string getAnimationPath() { return animationPath; }
   /**Mutator to change the path of the filename to an animation*/
   void setAnimationPath( const std::string& newPath) { animationPath = newPath; }
   /**Accessor to the name of the animation*/
   std::string getAnimationName() { return animationName; }
   /**Mutator to the name of the animation*/
   void setAnimationName( const std::string& name) { animationName = name; }

   /**Reads in a file, which points to an animation.
      If path is left as default, it will read the the path of animationPath.
      Checks for errors and will print out if there is a problem with the file and will return -1.
      Returns 0 on success.
      \param - the path of the animation file*/
   int readAnimationFile( const std::string& path = "" );
   /**Creates a file from the data stored inside of keyframes.
      If there is an error creating the file or any other error will return -1.
      Returns 0 on success.
      \param path - the path to write the animation to*/
   int writeAnimationFile( const std::string& path );

   /*sets the joints in order vector*/
   void setJointOrderVector(std::vector< WOGJoint* >* jointOrder) { jointsInOrder = jointOrder; }

   /**returns the joints in order vector*/
   std::vector< WOGJoint* > * getJointOrderVector() { return jointsInOrder; }

   /**takes a step in the animation.
      When it completes running through the animation it will return true, otherwise it will return false*/
   bool animationStep();

   /**Resets the animation to its initial keyframe*/
   void resetAnimation() { currentKeyframe = 0; }

   /**This will be called when an animation has reached the end of the animation
      The default case, is to reset the joints and take one step into the animation.*/
   virtual void onAnimationFinish();

protected:

   /**The animation keyframes, these will be order specific so you have to match up the vector of keyframes to a 
      world object.
      There will only be 6 values inside of vector < float > to represent: theta, phi, roll, x, y, z.*/
   std::vector< std::vector< std::vector< float>* >* >* keyframes;

   /**This is a vector of joints that will be rotated and soon to be translated (scott) 
      The order is important, it is matching up with the order that the joints are listed in the file.
      */
   std::vector< WOGJoint* >* jointsInOrder;

   /**The path to the animation file*/
   std::string animationPath;

   /**The name of the animation used for identification purposes.
      This will gotten from reading the file.*/
   std::string animationName;

   /**the current key frame that the animation is on*/
   int currentKeyframe;

};

/** \} */

} // namespace Aftr

