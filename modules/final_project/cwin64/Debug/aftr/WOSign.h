#pragma once

#include "WO.h"
#include <string>

namespace Aftr
{

   /**
      \class WOSign
      \author Chad Mourning
      \brief A textured sign that you can place in your world
   */

class WOSign: public WO
{
public:
   /**
   The constructor for the WOSign.  Defaults to  a sign of length 2 and height 1 with a red frame.

   \param texture The texture for the sign.
   \param length The length of the sign.
   \param height The height of the sign.
   \param r The unsigned represenation of the red contribution of the color of the frame.
   \param g The unsigned represenation of the green contribution of the color of the frame.
   \param b The unsigned represenation of the blue contribution of the color of the frame.

   */
   static WOSign* New(const std::string& texture, float length = 2, float height = 2, Vector color = Vector(0,0,0));
   virtual ~WOSign();
protected:
   virtual void onCreate(const std::string& texture, float length, float height, const Vector& color);
   WOSign();
};

}

