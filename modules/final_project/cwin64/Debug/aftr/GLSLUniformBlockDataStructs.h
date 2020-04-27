#pragma once

namespace Aftr
{
   /**
      This head declares structures that match Uniform Blocks in a GLSL Shader program
      All data should align to std140 standard, and each shader using these Uniform Blocks
      should specify std140.
      For example:
      layout( binding = 0, std140 ) uniform CameraTransforms
      {
         mat4 View;
         mat4 Projection;
      } T;

      The above declares a data structure laid out using std140. We can then create a 
      POD C Structure that directly maps into this data format making it easy to update
      the GLUniformBlockT<T>
   */

   struct GLSLUniformBlockCameraTransforms
   {
      float View[16];
      float Projection[16];
      float Shadow[16];
      // A Value of 0 = Render w/ No shadows (shadow mapping is not used)
      // A Value of 1 = Generate depth map only (for updating the shadow map prior to a fully shaded render to the color buffer)
      // A Value of 2 = Render w/ Shadow mapping (fully shaded render w/ shadow mapping shadows drawn)
      int ShadowMapShadingState = 0; ///< Non-zero value indicates this is a shadow map generation pass. IE, only the depth buffer need be populated, no fancy shading
   };

   struct GLSLUniformBlockLightInfo
   {
      static const int MAX_NUM_LIGHTS_IN_SHADER = 8; ///< Maximum Number of lights supported within shader
      float PosEyeSpace[MAX_NUM_LIGHTS_IN_SHADER][4]; ///< Eye space (view space) position of light (used in fragment shader)
      float Irgb[MAX_NUM_LIGHTS_IN_SHADER][4]; ///< Intensity for ambient, diffuse, specular. Element[3] not used.
      float GlobalAmbient[4];
      int NumActiveLights = 0; ///< Current number of active lights
   };
   //const int GLSLUniformBlockLightInfo::MAX_NUM_LIGHTS_IN_SHADER = 8; //storage for this variable so its address can be taken (it can be an l-value this way)

   //struct GLSLUniformBlockLightInfoSet
   //{
   //   static const size_t MAX_NUM_LIGHTS_IN_SHADER = 8; ///< Magic Constant 8 matches the Magic Constant in the Shader Program
   //   GLSLUniformBlockLightInfo Lights[MAX_NUM_LIGHTS_IN_SHADER];
   //};

} //namespace Aftr
