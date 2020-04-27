#pragma once

namespace Aftr
{
   //Useful mathematical constants that are used by Aftr quite frequently
   extern const float PI;
   extern const double PId;
   extern const float TWOPI;
   extern const float NEG_PI;
   extern const float NEG_TWOPI;
   extern const float DEGtoRAD;
   extern const double DEGtoRADd;
   extern const float RADtoDEG;
   extern const double RADtoDEGd;
   extern const float GRAVITY;
   extern const float SQRT2;
   extern const float ONE_OVER_SQRT2;
   extern const float NEG_ONE_OVER_SQRT2;
   extern const float SQRT3;
   extern const float ONE_OVER_SQRT3;
   extern const float NEG_ONE_OVER_SQRT3;
   extern const float E;
   extern const double Ed;

   //Useful physics constants
   //extern const float G;
   //extern const double Gd;//universal graviational constant (N (m/kg)^2)
   extern const float GM; //"geocentric gravitational constant"
   extern const double GMd; //universal gravitational constant (N (m/kg)^2) multiplied by the mass of the earth to reduced numerical instabilities

   //Useful conversations
   extern const float FEET_TO_METERS;
   extern const float METERS_TO_FEET;
   extern const float NAUTICAL_MI_2_METERS;
   extern const float METERS_2_NAUTICAL_MI;

   extern const double FEET_TO_METERSd;
   extern const double METERS_TO_FEETd;
   extern const double NAUTICAL_MI_2_METERSd;
   extern const double METERS_2_NAUTICAL_MId;

   /**
   STANDARDLOOK: User can free look with mouse. Holding down the left mouse button allows the user to look around. Holding down
   the right mouse button allows the user to move forward/backward along the axis in which he is looking. Holding down Left ALT
   and left clicking will cause the camera to look at the clicked 
   point and let the user pan around horizontally. Subsequently, holding down the Left CTRL key will let the user pan vertically
   about the point. This mode is very useful to freely navigate. The Left ALT and Left CTRL allow the user to easily orient themselves
   to look at exactly what they desire.
   This creates a camera instance of type CameraStandard.

   HELICOPTER: This mode spins the camera about the current actor varying the camera's z values as it circles.
   This creates a camera instance of type CameraChaseActorHelicopter.

   CHASEACTORLOOK: This locks the camera directly behind the current actor. Once behind, the user may hold down the left mouse to pan
   horizontally/vertically. The user may hold down the right mouse to zoom in/out from the actor. Setting to CHASEACTORLOOK after
   manipulating the view will reset the camera directly behind the actor.
   This creates a camera instance of type CameraChaseActorAbsNormal.

   CHASEACTORLOOK2: Similar to CHASEACTORLOOK; however, there is a more smooth motion of the camera. The camera gently, "drifts" behind
   the actor giving a more "flowing" feel. This mode is great for 3rd person views of people walking, cars driving, boats sailing, etc.
   This creates a camera instance of type CameraChaseActorSmooth.

   CHASEACTORLOOK3: Similar to CHASEACTORLOOK; however, this mode uses the actor's current normal vector as the camera's "up" vector.
   Thus, for example, if the actor is chasing an F16 through a valley and the F16 rolls upside down, the camera will roll upside down
   as well. Thus the valley will actually appear on the top of the screen. This mode is great for flight simulators and space flight.
   This creates a camera instance of type CameraChaseActorRelNormal.

   CHASEACTORLOOK4: Similar to CHASEACTORLOOK2, except instead of looking towards the horizon, the camera looks at the current actor.
   This is useful when, for example, you want to smoothly follow an aircraft that is changing altitude
   This creates a camera instance of type CameraChaseActorSmoothWatchActor.

   CHASEACTORLOOK5: Similar to CHASEACTORLOOK3; however, this mode smoothly trails behind the actor while looking at the
   actor. Keep in mind that camera's normal is based on the actor's normal direction yet smoothly follows the actor.

   CHASEACTORLOOK6: Similar to CHASEACTORLOOK3; except the camera looks at the current actor, and chases a point at a global offset
   from the actor.

   LOCKEDGLOBAL: locks with a target, and stays at a specified global offset

   LOCKEDRELATIVE: locks with a target, and stays at a specified relative offset

   STANDARDEZNAV: Similar to STANDARDLOOK. However right clicking moves you in the look direction. Holding down Left Shift while right
   clicking moves you opposite the look direction. Scrolling the mouse wheel up will increase the camera velocity while scrolling
   the mouse wheel down will decrease the camera velocity. This way, one does not need to drag the mouse to move, and the velocity of
   movement is easy to dynamically change.
   */
   enum CAM_CHASE_TYPE { STANDARDLOOK = 0, HELICOPTERLOOK, STATIONARYLOOK,
                         CHASEACTORLOOK, CHASEACTORLOOK2, CHASEACTORLOOK3, CHASEACTORLOOK4, 
                         CHASEACTORLOOK5, CHASEACTORLOOK6, LOCKEDGLOBAL, LOCKEDRELATIVE,
                         STANDARDEZNAV, cctCameraChaseActorSmoothWGS84, cctNUM_CAM_CHASE_TYPE };

   class WOGJoint;
   class WO;
   class WO;
   class GLView;
   class Model;
}

