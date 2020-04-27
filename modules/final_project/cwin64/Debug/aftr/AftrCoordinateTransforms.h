#pragma once

#include <vector>
#include "VectorFwd.h"
#include "Mat4Fwd.h"


namespace Aftr
{

   class Camera;

   class AftrCoordinateTransforms
   {
   public:

      /**
         Using the viewing properties of the in passed camera (current viewing state), each Vector
         in ptsToTransform is transformed from World Space (global coordinates) to screen space and
         placed in outTransformedPts. outTransformedPts[i] is the transformed vertex of ptsToTransform[i].
         outPerspectiveDivideScalar[i] stores the w (perspective divide) value used during the viewport
         transformation of ptsToTransform[i].

         std::vector< Vector >& outTransformedPts is output only, it is cleared completely and repopulated
         by this method.

         std::vector< float >& outPerspectiveDivideScalar is output only, it is cleared completely and repopulated
         by this method.

         Transforming many points at once is more efficient than calling this method many times as the
         aggregated transformation matrix is computed only once, and then each source point is transformed
         by that aggregated matrix.

         outTransformedPts[i].x is the x coordinate (Lower left of the viewport is 0,0).
         outTransformedPts[i].y is the y coordinate (Lower left of the viewport is 0,0).
         outTransformedPts[i].z is the z coordinate, this is the distance from the camera's near plane (or the 
         camera's position, not sure yet) "into" the scene, i.e., the depth from the near plane to the coordinate's
         location.

         The perspective divide value, w, used during the homogeneous coordinate transformation is stored in
         outPerspectiveDivideScalar[i]. This is returned in case the user would like to use it for some reason.
      */
      template< typename T >
      static void transformFromWorldSpaceToScreenSpace( Camera* cam, 
                                                        const std::vector< VectorT<T> >& ptsToTransform,
                                                        std::vector< VectorT<T> >& outTransformedPts, 
                                                        std::vector< T >& outPerspectiveDivideScalar, 
                                                        std::vector< VectorT<T> >* outTransformedPtsClipSpace = nullptr );

      ///**
      //   Double precision version of transformFromWorldSpaceToScreenSpace (uses doubles instead of floats
      //*/
      //static void transformFromWorldSpaceToScreenSpaceD( Camera* cam,
      //   const std::vector< VectorD >& ptsToTransform,
      //   std::vector< VectorD >& outTransformedPts,
      //   std::vector< VectorD >& outTransformedPtsClipSpace,
      //   std::vector< double >& outPerspectiveDivideScalar );

      /**
         This method converts a set of vertices from screen space to world space using the view matrix and projection matrix 
         specified within the in passed camera (basically, it uses the camera's view frustum, position, orientation, FOV, etc,
         to transform ptsToTransform from screen space to world space). Note, for this to work properly, the .x,.y of each 
         Vector in ptsToTransform specify the pixel location on the screen and the .z value specifies the depth INTO the screen.
         The depth is used by the OpenGL Depth buffer to determine if a pixel on a certain object should be drawn in front of
         another object that is further away from the camera (eyeball).

         One does not need to pass ANY values in to the perspectiveDivideScalars, this is no longer used internally by these
         methods.
      */
      //static void transformFromScreenSpaceToWorldSpace( Camera* cam, 
      //   const std::vector< Vector >& ptsToTransform,
      //   std::vector< Vector >& outTransformedPts,
      //   const std::vector< float >& perspectiveDivideScalars );

      /**
         Double precision version of transformFromWorldSpaceToScreenSpace (uses doubles instead of floats
      */
      template< typename T >
      static void transformFromScreenSpaceToWorldSpace( Camera* cam,
                                                        const std::vector< VectorT<T> >& ptsToTransform,
                                                        std::vector< VectorT<T> >& outTransformedPts,
                                                        const std::vector< T >& perspectiveDivideScalars );

      template< typename T >
      static void transformFromClipSpaceToWorldSpace( Camera* cam, 
                                                      const std::vector< VectorT<T> >& ptsToTransform,
                                                      std::vector< VectorT<T> >& outTransformedPts,
                                                      const std::vector< T >& perspectiveDivideScalars );


      /**
         A smaller conversion method that converts from Eye space (also called View space) to world space.
      */
      template< typename T >
      static void transformFromEyeSpaceToWorldSpace( T viewMat[16],
                                                     const std::vector< VectorT<T> >& ptsToTransform,
                                                     std::vector< VectorT<T> >& outTransformedPts );

      /**
            Given a X vector and Z vector (look direction and up direction), that are perpendicular to each other, generate the matrix forming
            the orthonormal coordinate system for this transform. Also, transform all of the ptsToTransfrom into this new coordinate system by
            multiplying through the inverse of the generated matrix (since the matrix is orthonormal, just multiply ptsToTransform through the
            transpose of outTBNMatrix and then store them in outTransformedPts.
      */
      template< typename T >
      static void transformFromWorldSpaceToTangentSpace( const VectorT<T>& tangentXdir,
                                                         const VectorT<T>& tangentZdir, const T modelMat[16],
                                                         const std::vector< VectorT<T> >& ptsToTransform,
                                                         std::vector< VectorT<T> >& outTransformedPts,
                                                         T* outTBNMatrix = nullptr );

      /// Given a latitude/longitude pair, this method generates and returns (via localBodySpaceToLTP), the matrix that will
      /// transform a vector from local body space (model space) to the Local Tangent Place space derived from the latitude/longitude.
      /// The transpose (inverse) of this matrix will transform a vector from LTP space to local body space.
      template< typename T >
      static void getLocalBodySpaceToLTPSpace( const VectorD& lla, T localBodySpaceToLTP[16] );

      //static void getLocalBodySpaceToLTPSpaceD( const VectorD& lla, double localBodySpaceToLTP[16] );

      /**
         Computes a Local Tangent Plane on the WGS-84 geoid. Takes the current Lat/Lng and uses
         this to construct the local tangent plane facing true north. X points to true north along
         tangent plane, Z points perpendicular to the ground at that Lat/Lng point, and Y points
         as Z cross X...

         LocalBodySpace is the local body frame of the input and outWorldSpaceOrient is the local 
         body frame transformed to worldSpace (NAV Frame).

         If outRollPitchYawInDegInNAVFrame is not NULL, it is populated with the Euler angles 
         extracted from the outWorldSpaceOrient matrix. The angle ranges are defined as follows:

         Roll (-180,180): Positive is right wing down (Pos right handed rot about rel X)
         Yaw (-180, 180): 0 is north, 90 is east, 180 is south, -90 is west.
         Pitch (-90,90): Positive is nose up (relX dot relZ is positive).
      */
      template< typename T >
      static void transformFromLLAToECEFOrient( const VectorD& lla, const T localBodySpaceOrient[16],
                                                T outWorldSpaceOrient[16],
                                                VectorD* outRollPitchYawInDegInNAVFrame = nullptr );

      /**
         This method takes as input an orthonormal 4x4 display matrix (only uses the upper 3x3 orientation
         data) and returns a Vector whos X,Y, and Z components hold the roll (rotation about rel X axis), 
         pitch (rotation about rel Y axis), and yaw (rotation about rel Z axis), respectively. Roll, Pitch,
         and Yaw are in degrees. The 4x4 display matrix is assumed to be orthonormal, column major.
      */
      template< typename T >
      static VectorD transformFromDisplayMatrixToRollPitchYaw( const T m[16] );

      /**
         This methods takes as input a Vector whos X,Y, and Z components hold the roll (rotation about rel X axis), 
         pitch (rotation about rel Y axis), and yaw (rotation about rel Z axis), respectively, in degrees. This 
         method sets the outDispMat to a 4x4 orthonormal display matrix matching that orientation.
      */
      template< typename T >
      static void transformFromRollPitchYawToDisplayMatrix( const VectorD& rollPitchYawDeg, T outDispMat[16] );

      template< typename T >
      static Mat4T<T> transformFromRollPitchYawToDisplayMatrix( const VectorT<T>& rollPitchYawDeg );

      /**
         Accumulates to the in passed 4x4 rotation matrix (row 4 and col 4 are identity) a rotation about the
         arbitrary in passed axis. It is assumed the in passed axis passes through the origin.

         This enables quick accumulation. For example, if one has a roll, pitch, and yaw values in degrees,
         and a 4x4 display matrix is desired, the following usage of this method will achieve that:

         float m[16];
         aftrSetIdentityMatrix( m );
         AftrCoordinateTransforms::rotateAboutArbitraryAxis( Vector(0,1,0), rollPitchYaw.y * -Aftr::DEGtoRAD, m ); //y component stores pitch
         AftrCoordinateTransforms::rotateAboutArbitraryAxis( Vector(0,0,1), rollPitchYaw.z * -Aftr::DEGtoRAD, m ); //z component stores yaw
         AftrCoordinateTransforms::rotateAboutArbitraryAxis( Vector(m[0],m[1],m[2]), rollPitchYaw.x * Aftr::DEGtoRAD, m ); //x component stores roll
         //m now stores the display matrix using euler angles x,y,z from the rollPitchYaw vector
      */
      template< typename T >
      static void rotateAboutArbitraryAxis( const VectorT<T>& axisOfRotNormalized, T rotAnangleRadian, T inOutAccumulatedMatrix[16] );
   };

} //namespace Aftr

