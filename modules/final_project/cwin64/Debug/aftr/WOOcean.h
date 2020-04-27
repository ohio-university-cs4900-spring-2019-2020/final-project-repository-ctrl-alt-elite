#pragma once


#include "WOBuoyancyFluid.h"

namespace Aftr
{

   class GLView;
   class MGLOcean;
   class WOWater;
   class Wave;

   /**
   \author Chad Mourning (Updated by Scott Nykl)

      This class is meant to act as a special container to hold multiple waters 
      and give them extra functionality such as interacting with a GUI to get tidal 
      adjuaftrents and height at a given point.
   */


class WOOcean : public WOBuoyancyFluid
{

public:
   /**
   Constructor

   \param view Parent GLView
   \param x Length of the ocean
   \param y Width of the ocean
   \param wo Water behavior to use, if NULL a default behavior is created
   \param l Liquid Density, needed by buoyency objects

   */
   static WOOcean* New(GLView* view, WOWater* wo, int x = 1000, int y = 1000, bool autoFollow = true, float l = 1020);
   static WOOcean* New(GLView* view, Wave behavior, float velocity, int x = 1000, int y = 1000, int fidelity = 4,
      int timer = 100, int waterx = 200, int waterz = 100, bool autoFollow = true, float liquidDensity = 1020);

   
   /**Destructor*/
   virtual ~WOOcean();
   
   /**
   Returns the normal at a point, not tested
      \param x the x coordinate you are searching for the normal of
      \param y the y coordinate you are searching for the normal of
      \return a pointer you own whose value is a VectorD containing the normal of the point you were searching for
   */
   //VectorD* findWaterNormal(float x, float y);
   
   /**
      Returns the height at a given point, you own the returned memory
      \param x the x coordinate you are searching for the height of
      \param y the y coordinate you are searching for the height of
      \return a pointer you own whose value is a GLfloat indicating the height at the point you were searching for
   */
   virtual float findWaterHeight(float x, float y);
   
   /**
      Mutator for the tidal percentage
      \param tidePercent percent to set the tide to
   */
   void setTidalPercentage( float tidePercent );

   /**
      Returns the tidal percentage.
      \return tidal percentage
   */
   float getTidalPercentage();
   #ifdef AFTR_CONFIG_USE_TNL
      virtual void packNetState( TNL::VectorD< TNL::S32 >& intVec, TNL::VectorD< TNL::F32 >& floatVec );
      virtual void unPackNetState( TNL::VectorD< TNL::S32 >& intVec, TNL::VectorD< TNL::F32 >& floatVec );
   #endif
   virtual void onUpdateWO();

protected:
   virtual void onCreate(WOOcean* parent, GLView* view, int x, int y, WOWater* water, bool autoFollow);
 
   WOOcean(float liquidDensity);

   /**The tidal percentage*/
   float tidalPercentage;
};

} //namespace Aftr

