//---------------------------------------------
// Description: Monkey Mountain, encapsulates all
//              of the MM functionality inside this class
// Author: Mitchell Leitch
//----------------------------------------------

#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOStaticTrimesh.h"
#include "WOBodyPart.h"
#include "Animation.h" //need because OpenEyeAnimation : public Animation


namespace Aftr
{

/**
   \class WOMonkeyMountain
   \author Mitchell Leitch
   \brief Monkey Mountain is a mountain WO that has animateable eyes, and inherits from WOStatic Trimesh
   \{
   */
class WOMonkeyMountain : public WOStaticTrimesh
{

public:
   /**Default constructor, sets up the monkey, its movable pieces and the animation*/
   static WOMonkeyMountain* New();

   /**Destructor, does nothing at the moment other than implicitly calling the parent's destructor*/
   virtual ~WOMonkeyMountain();

   /**Starts the open eye animation, slowly opens the monkey's eyes*/
   void startOpenEyeAnimation() { currentAnimation = openEyeAnimation; }

   /**Accessor, to get the blink animation*/
   Animation* getBlinkAnimation() { return blinkAnimation; }

   /**Overloaded, so every update the monkey blinks at a less rapid pace*/
   void onPhysicsEngineTick();

protected:
   WOMonkeyMountain();
   virtual void onCreate( const std::string& modelFileName );

   /**The left eyelid of the monkey that will be animated*/
   WOBodyPart* r_eyelid;
   /**The right eyelid of the monkey that will be animated*/
   WOBodyPart* l_eyelid;

   /**An animation for the monkey to open his eyes*/
   Animation* openEyeAnimation;

   Animation* blinkAnimation;

   unsigned int lengthBetweenBlinks;

   /**true if the monkey's eyes are open*/
   bool eyesOpen;

};

/** } */

class OpenEyeAnimation : public Animation
{
public:

   OpenEyeAnimation(const std::string& mmAnimationPath, std::vector< WOGJoint* >* jointOrder = NULL);

   virtual ~OpenEyeAnimation();

   virtual void onAnimationFinish();

protected:


};

} //namespace Aftr


#endif
