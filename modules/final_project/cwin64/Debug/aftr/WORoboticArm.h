#pragma once

#include "WO.h"

namespace Aftr
{
   class WOBodyPart;

/** This class is the human (avatar <-- this'll piss off scott) world object that handles the movement 
    and animation of the human.
*/
class WORoboticArm : public WO
{
public:
   static WORoboticArm* New();
   ~WORoboticArm();

   /** Constructs the human piece by piece and places them into the world connected to the human in the proper orientation*/
   void constructRoboticArm();

   virtual void onUpdateWO();

   //User Keyboard Input Specific
   //-----------------------------------
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );
   //-----------------------------------

   virtual void onMouseDown( const SDL_MouseButtonEvent& mouse );
   virtual void onMouseDownSelection( const SDL_MouseButtonEvent& mouse );
   virtual void onMouseDownChildWasSelected( const SDL_MouseButtonEvent& mouse, WO* selectedChild );

   virtual void processRoboticSelection( const SDL_MouseButtonEvent& mouse, WO* selectedPart );

   WO* getBaseArm() { return this->baseArm; }
   WO* getUpperArm() { return this->upperArm; }
   WO* getHand() { return this->hand; }
   WO* getRotateTarget() { return this->target; }

protected:
   WORoboticArm();
   virtual void onCreate( const std::string& modelFileName, Vector scale = Vector( 1, 1, 1 ), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );

   /** The body parts of the human world object, each piece represents a part of the human*/
   WO* baseArm = nullptr;
   WO* upperArm = nullptr;
   WO* hand = nullptr;

   WO* target = nullptr; ///< used by processRoboticSelection to determine which robot arm to manipulat with key presses
};

} //namespace Aftr

