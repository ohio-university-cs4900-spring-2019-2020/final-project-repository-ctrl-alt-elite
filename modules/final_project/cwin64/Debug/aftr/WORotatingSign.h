#pragma once

#include "WO.h"
#include <string>

namespace Aftr
{

   enum class ROTATION_STATE : unsigned char;

   /**

   \class WORotatingSign
   \author Chad Mourning
   \brief A sign that rotates.

   */

class WORotatingSign: public WO
{
public:
   /**
   The constructor for the WOSign.  Defaults to  a sign of length 2 and height 1 with a red frame.

   \param texture1 The texture for the front face of the sign.
   \param texture2 The texture for the back face of the sign.
   \param timeOnFace1 The time spent on the front face before rotating
   \param timeRotating The time spent rotating 180 degrees.  Is the same for both transitions.
   \param timeOnFace2 The time spent on the back face before rotating.  If -1 will use the same time as face 1.
   \param length The length of the sign.
   \param height The height of the sign.
   \param r The unsigned representation of the red contribution of the color of the frame.
   \param g The unsigned representation of the green contribution of the color of the frame.
   \param b The unsigned representation of the blue contribution of the color of the frame.

   */
   static WORotatingSign* New(const std::string& texture1, const std::string texture2, unsigned int timeOnFace1 = 5000, unsigned int timeRotating = 2000, unsigned int timeOnFace2 = -1, float length = 2, float height = 1, Vector color = Vector(0,0,0));
   virtual ~WORotatingSign();
   virtual void onPhysicsEngineTick();
   virtual void render( const Camera& cam );
private:
   virtual void onCreate(const std::string& texture1, const std::string& texture2, float length, float height, const Vector& color);
   WORotatingSign(unsigned int timeOnFace1, unsigned int timeRotating, unsigned int timeOnFace2);
   unsigned int internalTimer;
   unsigned int timeOnFace1;
   unsigned int timeRotating;
   unsigned int timeOnFace2;
   ROTATION_STATE rotationState;
};

}

