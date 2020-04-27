#pragma once

#include "WO.h"
#include "Wave.h"

namespace Aftr
{
   class GLView;
   class MGLWater;

   class WOWater : public WO
   {
      /**
      \author Chad Mourning

      This is the water.  o0o pretty.
      */
   public:
      /**
      default constructor

      \param view parent view class
      \param x x-length of grid
      \param y y-height of grid (not used)
      \param z z-length
      \param t height perterb threshhold
      \param n fidelity (~rows)
      \param s number of display list states used
      \param u update timer
      \param r number of rows (might always be one)
      \param c number of columns (not used)
      \param b wave behavior
      \param min min phase shift
      \param max max phase shift
      \param v velocity increase of phase shift in units per millisecond
      \param l level of detail (not used, yet)


      */   
      static WOWater* New(GLView* view, int x = 100, int y = 0, int z = 100, float t = .025, int n = 0, int s = 0, int u = 100, int r = 1, int c = 1, Wave b = Wave(100,1), float min = 0, float max = 100, float v = 0, int l = 3);
      
      /**Destructor*/
      virtual ~WOWater();
      /**
      Returns the amount of time between updates

      \return \see MGLWater::updateTimer
      */
      int getUpdateTimer();

      /**Shifts phase by x*/
      void phaseShift(float x);

      /**Shares the model between multiple instances, no longer used*/
      void shareModel(WO* wo, bool shared = false);

      /**Returns description size*/
      size_t getDescriptionSize();

      virtual void onUpdateWO();
   protected:	 
      virtual void onCreate(GLView* view, int x, int y, int z, float t, int n, int s, int u, int r, int c, Wave b, float min, float max, float v, int l);
      WOWater();
      unsigned int internalTimer;
   };


} //namespace Aftr
