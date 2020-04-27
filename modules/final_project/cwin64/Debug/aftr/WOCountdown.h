#pragma once

#include "WO.h"

namespace Aftr
{

   /**

   \class Chad Mourning

   */

class WOCountdown : public WO
{
public:
   /**

   \param slides Paths to the texture to be used for each slide of the countdown
   \param timePerSlide the time per slide before switching to the next
   \param minScale of slide NOT IMPLEMENTED

   */
   static WOCountdown* New(const std::vector<std::string>& slides, unsigned int timePerSlide = 1000);
   virtual ~WOCountdown(){};
   virtual void onUpdateWO();
   /**
   Must be called to begin a countdown.
   */
   virtual void begin();
   /**
   Will be called when a countdown ends.
   */
   virtual void end() {};
protected:
   virtual void onCreate(const std::vector<std::string>& slides);
   WOCountdown(unsigned int timePerSlide);
   unsigned int internalTimer;
   unsigned int timePerSlide;
};


}

