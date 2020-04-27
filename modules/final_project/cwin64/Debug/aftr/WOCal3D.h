#pragma once
#ifdef AFTR_CONFIG_USE_CAL3D

#include "WO.h"

namespace Aftr
{

class MGLCal3D;

class WOCal3D : public WO
{

public:
   static WOCal3D* New( const std::string& cal3DConfigFile );

   virtual ~WOCal3D();

   virtual void onPhysicsEngineTick();

   virtual void onKeyDown( const SDL_KeyboardEvent& key );

   #ifdef AFTR_CONFIG_USE_TNL
      //Network Subsystem Specific ----------------------------------------------
      virtual void packNetState( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      virtual void unPackNetState( TNL::Vector< TNL::S32 >& intVec, TNL::Vector< TNL::F32 >& floatVec );
      //-------------------------------------------------------------------------
   #endif

   /**
      Enables animation jitter.
      Random constant time-based animation scalar useful for causing 
      many instances of the same Cal3D object to drift apart so their
      animations are out of phase; so they look more independent from
      each other
   */
   void isUsingAnimationJitter( bool enableAnimationJitter ) { this->useJitter = enableAnimationJitter; }
   
   /**
      Returns true iff this instances is currently performing animation 
      jitter; false, otherwise.
   */
   bool isUsingAnimationJitter() { return this->useJitter; }

protected:
   WOCal3D( const std::string& cal3DConfigFile );
   virtual void onCreate( const std::string& cal3DConfigFile );

   std::string Cal3DConfigFile;
   unsigned int lastMainLoopIteration;
   unsigned int lastAnimationTimeStamp;
   
   /**
      Random constant time-based animation scalar useful for causing 
      many instances of the same Cal3D object to drift apart so their
      animations are out of phase; so they look more independent from
      each other.
   */
   float jitter;

   /**
      Perform animation jitter if set to true; otherwise, perform no
      animation jitter.
   */
   bool useJitter;
   

};
} //namespace Aftr
#endif //AFTR_CONFIG_USE_CAL3D
