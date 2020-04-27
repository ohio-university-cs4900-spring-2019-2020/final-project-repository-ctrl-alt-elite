//---------------------------------------------------------
// Description: The animation manager that will ensure only 
//              one unique animation will be loaded into memory
//
// Author: Mitchell Leitch
//---------------------------------------------------------

#pragma once


#include <map>
#include "Animation.h"

namespace Steamie
{

/**
   \class AnimationManager
   \author Mitchell Leitch
   \brief This is a static manager class that handles all of the animation in the world.
   \Ensures that only one copy of the animation will be in memory at a time
   \{
   */
class AnimationManager
{
public:

   /**Tests whether the animation has been registered, true if it has
      \param animationPath - */
   static bool animationRegistered(std::string animationPath);

   /**Returns the animation of the string passed into it. 
      If it is not in the list it will return NULL.*/
   static std::vector< std::vector< std::vector< float>* >* >* getAnimation(std::string animationPath);

   /**Creates an animation from the path passed in.
      If the function completes successfully, it will return true, otherwise false.*/
   static void addAnimation(std::string animationName, std::vector< std::vector< std::vector< float>* >* >* keyframes);

   /**Deletes an animation with the path of the string passed in.
      Returns true if the delete was successful.
      False if the delete failed because the animation doesn't exist*/
   static bool deleteAnimation(std::string animationPath);

   /**Deletes all of the animations in the animationManager*/
   static void deleteAllAnimations();

};


/**The map of animations that are in memory*/
static std::map< std::string, std::vector< std::vector< std::vector< float>* >* >* > animationData; 
/**An iterator through the map of animations*/
static std::map< std::string, std::vector< std::vector< std::vector< float>* >* >* >::iterator animationIterator;
} //namespace Steamie


