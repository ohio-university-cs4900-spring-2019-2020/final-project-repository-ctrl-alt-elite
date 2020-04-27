/**
   
   \class ManagerLight
   \author Chad Mourning
   \brief Managers synchronization and compression of lights, as well as global lighting effects.

   The light manager controls synchronization for lights.  Some implementations of OpenGL require
   that all previous lights be used to use the next light. For instance if you want to use LIGHT4
   you must also make sure LIGHT0, LIGHT1, LIGHT2, and LIGHT3 are enabled.  In the Aftr engine
   you should never have to make an actual call to LIGHTX, just add a light and it will all work.

   Light Synchronization happens between render, so as soon as you turn a light off, the next
   render it will no longer have any effect.
*/

#pragma once

#include <vector>
#include <iostream>
#include "GLSLUniformBlock.h"
#include "GLSLUniformBlockDataStructs.h"

namespace Aftr
{

class WOLight;
class WOLightShadowCasting;
class Camera;

class ManagerLight
{
public:
   friend class WOLight;//give access to lights
   friend class WOLightShadowCasting;//give access to shadowcasting 
   ///initialization function for the light manager
   static void init();
   static void shutdown();
   ///accessors for number of active lights
   static int getNumLightsOn(){return numLights;}
   static size_t getNumLightsTotal(){ return lights.size(); }
   ///synchronize lights every render pass 
   static void synchronizeLights( const Camera& cam );
   ///basically a destructor for the light manager
   static void clearAllLights();
   ///performs all lighting effects that are done after objects are rendered
   ///effects performed in this functions:
   ///  shadow casting
   ///  lens flare effects
   static void performPostRenderLightingEffects( const Camera& cam);
   ///calls lens flare for all lights
   static void lensFlare( const Camera& cam);
   ///returns the shadowFrag1 shader

   ///syncs opengl light positions with world object positions
   static void syncLightPositionsFromWOToOpenGL();
   static void setGlobalAmbientLight( const aftrColor4f& ambientColor );

   static const std::vector< WOLight* >& getLights() { return lights; }

protected:

   static GLSLUniformBlockT< GLSLUniformBlockLightInfo >* uniformBlockLightInfoGL32;
   static aftrColor4f globalAmbientColor;

   ///registers a light with the ManagerLight, called in WOLight constructor
   static void registerLight(WOLight* x);
   ///number of active lights in the world
   static int numLights;
   ///list of all lights in the world
   static std::vector<WOLight*> lights;   
};

}

