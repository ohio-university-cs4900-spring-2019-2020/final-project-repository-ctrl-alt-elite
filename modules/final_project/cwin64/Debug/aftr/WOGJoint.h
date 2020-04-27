#pragma once

#include "Vector.h"
#include "Mat4.h"

namespace Aftr
{

class WO;
class IndexedGeometryAxes;

/**
   \class WOGJoint
   \author Scott Nykl 
   \brief A joint that can be used to attach any WO (or subclass) to any WO (or subclass).
   When the parent's position/orientation changes, the child's position/orientation shall
   be updated accordingly. Additionally, the joint itself can be transformed so the child's
   position/orientation changes w.r.t the parent, but the parent's position/orientation still
   modifies the child.  For example, imagine a human arm. The Upper arm could be the parent of
   the lower arm, and the WOGJoint would represent the elbow. When the upper arm moves, the lower
   arm moves relative to the upper arm, as it is attached to the upper arm; additionally, 
   the elbow can bend, allowing the lower arm to move independent of the upper arm.

   The WOGJoint class allows the user to specify many different parameters to define how the
   joint shall operate. Key features/notes of the joint include:   
      -# The joint's location is defined as an offset from the parent WO.
      -# The WOGJoint's jointLookDir defines the joint's relative +X-axis.
      -# The WOGJoint's jointNormal defines the joint's relative +Z-axis.
      -# The jointLookDir and jointNormal shall be orthognal, unless the user knows EXACTLY what he's doing.
      -# Iff orthogonal, the jointNormal (cross) jointLookDir shall yield the joint's relative +Y-axis.
      -# Modifying the joint's horizontal angle (yaw), vertical angle (pitch), and roll, correspond to the joint
         being rotated about its relative +Z-axis, +Y-axis, and +X-axis, respectively.

   To USE a joint, the user simply creates at least two WOs. One of these WOs MUST be of type WO (or a
   subclass). The code below shows an example of connecting a lower arm to an upper arm via a joint.

   //Create the upperArm (PARENT)
   WO* upperArm = new WO( ManagerEnvironmentConfiguration::getSMM() + "/models/roboArm2.wrl" );
   upperArm->setPosition( Vector( 9.0, 0, 15 ) );

   //Create the lowerArm (CHILD)
   WO* lowerArm = new WO( ManagerEnvironmentConfiguration::getSMM() + "/models/roboArm2.wrl" );
   lowerArm->setParentWorldObject( upperArm ); //Child NEEDS a set parent
   lowerArm->setPosition( Vector( 29.5, 0, 15 ) ); //20.5 Units along +X-axis from the PARENT (child's relative position from parent)
   upperArm->getChildren().push_back( lowerArm ); //Adds the lowerArm as a CHILD of the PARENT (now the PARENT knows that lowerArm is its child).
   joint = new WOGJoint( lowerArm, Vector(10.25,0,0) ); //creates a joint 1.25 Units along +X-axis from parent
   lowerArm->lockWRTparent( joint ); //Actually fixes the child to the parent via the joint

    \{
*/
class WOGJoint
{
public:

   /**
      Creates a joint between childWithSetParent and the corresponding Parent.
      Basic constructor assumes the child shall always pivot about the parent's
      center.
      
      \param childWitSetParent the WO* that has a WO (or subclass) set as the parent.
   */
   WOGJoint( WO* childWithSetParent );

   /**
      Creates a joint between childWithSetParent and the corresponding Parent.
      User defines the joint's normal as well as the joint's look direction. NOTE:
      In order for the Joint to behave as one would normally expect a joint, the
      Joint Normal and the Joint Look Direction MUST be Orthogonal (perpendicular).
      That is jointLookDir.dotProduct( jointNormal ) == 0.

      Also note that if orthogonal, then jointNormal.crossProduct( jointLookDir ) shall
      yield a vector pointing along the joint's relative +y-axis. These relative axes
      are used to perform joint rotations.

      \param childWitSetParent the WO* that has a WO (or subclass) set as the parent.
      \param jointNormal Normalized vector pointing along the joint's relative +z-axis
      \param jointLookDir Normalized vector pointing along the joint's relative +x-axis
   */
   WOGJoint( WO* childWithSetParent, const Vector& jointNormal, const Vector& jointLookDir );

   /**
      Creates a joint between childWithSetParent and the corresponding Parent.
      The jointNormal and jointLookDir default to (0,0,1) and (1,0,0), respectively.
      The child shall always pivot about the parent's position (plus) the in passed offset.
      Note that the joint will automatically account for the fact that the offset's direction
      changes as a result of the parent's orientation being changed. That is, if the parent
      rotates 35 degress about the +Z-axis, so does the joint attached to the parent; thus,
      the point/orientation about which the child rotates is updated as well.
      
      \param childWitSetParent the WO* that has a WO (or subclass) set as the parent.
      \param vecParentToJointInParentObjSpace The offset between the parent's current 
             position and the joint's current position. That is, the current Parent's 
             position (plus) vecParentToJointInParentObjSpace == current Absolute Joint Position.
   */
   WOGJoint( WO* childWithSetParent, const Vector& vecParentToJointInParentObjSpace );

   WOGJoint( const Vector& vecParentToJointInParentObjSpace, WO* childWithSetParent, const Vector& vecJointToChildInParentObjectSpace,
             const Vector& jointNormal = Vector(0,0,1), const Vector& jointLookDir = Vector( 1, 0, 0 ) );

   /**
      Creates a joint between childWithSetParent and the corresponding Parent.
      User defines the joint's normal as well as the joint's look direction. NOTE:
      In order for the Joint to behave as one would normally expect a joint, the
      Joint Normal and the Joint Look Direction MUST be Orthogonal (perpendicular).
      That is jointLookDir.dotProduct( jointNormal ) == 0.

      Also note that if orthogonal, then jointNormal.crossProduct( jointLookDir ) shall
      yeild a vector pointing along the joint's relative +y-axis. These relative axes
      are used to perform joint rotations.

      \param childWitSetParent the WO* that has a WO (or subclass) set as the parent.
      \param vecParentToJointInParentObjSpace The offset between the parent's current 
             position and the joint's current position. That is, the current Parent's 
             position (plus) vecParentToJointInParentObjSpace == current Absolute Joint Position.
      \param jointNormal Normalized vector pointing along the joint's relative +z-axis
      \param jointLookDir Normalized vector pointing along the joint's relative +x-axis
   */
   WOGJoint( WO* childWithSetParent, const Vector& vecParentToJointInParentObjSpace, const Vector& jointNormal, const Vector& jointLookDir );

   /**
      Destroys the WOGJoint and all internal memory is free-ed.
   */
   virtual ~WOGJoint();

   /**
      Returns Value (radians) indicating the radian offset from the Joint's relative +X-axis about the joint's relative +Z-axis (Yaw).
      \return Value (radians) indicating the radian offset from the Joint's relative +X-axis about the joint's relative +Z-axis (Yaw).
   */
   float getChildDeltaThetaWRTJoint() { return this->ChildDeltaThetaWRTJoint; }

   /**
      Returns Value (radians) indicating the radian offset from the Joint's relative +Z-axis about the joint's relative +Y-axis (Pitch).
      \return Value (radians) indicating the radian offset from the Joint's relative +Z-axis about the joint's relative +Y-axis (Pitch).
   */
   float getChildDeltaPhiWRTJoint()   { return this->ChildDeltaPhiWRTJoint; }

   /**
      Returns Value (radians) indicating the radian offset about the joint's relative +X-axis (Roll).
      \return Value (radians) indicating the radian offset about the joint's relative +X-axis (Roll).
   */
   float getChildDeltaRollWRTJoint()  { return this->ChildDeltaRollWRTJoint; }

   /**
      When a child is lockedWRTParent(), the child is set at a fixed distance from the joint.
      This distance can be scaled. For example if a child was 20 units from the joint and this
      scalar was set to 0.7, then the child would move closer to the joint and be (20*.7)=14 units
      from the joint. When a joint is created, its scalar is initialized to 1. Setting this larger
      than 1 moves the child farther from the joint. Setting this smaller than 1 moves the child closer
      to the joint. Setting this value to 1 restores the child's original distance to the joint.

      \return The current value of the scalar.
   */
   float getScalarFromJointToChild();

   /**
      When a child is lockedWRTParent(), the child is set at a fixed distance from the joint.
      This distance can be scaled. For example if a child was 20 units from the joint and this
      scalar was set to 0.7, then the child would move closer to the joint and be (20*.7)=14 units
      from the joint. When a joint is created, its scalar is initialized to 1. Setting this larger
      than 1 moves the child farther from the joint. Setting this smaller than 1 moves the child closer
      to the joint. Setting this value to 1 restores the child's original distance to the joint.

      \param scalar The new value to which the scalar shall be set.
   */
   void setScalarFromJointToChild( float scalar );

   /**
      This method resets the Joint's transform matrix to identity. It also
      resets the DeltaThetaWRTJoint, DeltaPhiWRTJoint, and DeltaRollWRTJoint
      to zero. The joint offset from parent and distance to the child remain
      constant.
   */
   void setJointTransformMatrixToIdentity();

   void setJointTransformMatrixTo( Mat4 newTransformMat );
   void getJointTransformMatrix( float* transMat ) const;
   const Mat4& getJointTransformMatrix() const;

   void changeChildDeltaThetaWRTJoint( float deltaThetaRads );
   void changeChildDeltaPhiWRTJoint  ( float deltaPhiRads );
   void changeChildDeltaRollWRTJoint ( float deltaRollRads );

   /// Moves the joint's anchor forward along the joints current look direction (relative X axis) by the in passed units.
   void moveAlongRelX( float deltaXAlongJointLookDir );

   /// Moves the joint's anchor upward along the joints current normal direction (relative Z axis) by the in passed units.
   void moveAlongRelZ( float deltaZAlongJointNormalDir );

   /// Moves the joint's anchor forward along the joints current look direction (relative Y axis) by the in passed units.
   void moveAlongRelY( float deltaYAlongJointRelY );

   Vector getJointLookDirWorldSpace() const;
   Vector getJointNormalDirWorldSpace() const;
   Vector getRelJointLookDir() const;
   Vector getRelJointNormalDir() const;

   void updateJoint();
   void resetJoint();

   Vector getVecFromJointToChildWorldSpace() const;
   Vector getVecFromParentToJointWorldSpace() const;
   Vector getJointPosition() const;

   void render( const Camera& cam );

   bool isVisible = false;

   /// Returns the Vector originating at the Parent's origin pointing to the Joint's origin.
   /// This vector is in the Parent's reference frame.
   const Vector& getVecFromParentToJointParentSpace() const;

   /// Replaces the Vector originating at the Parent's origin pointing to the Joint's origin.
   /// This vector will subsequently originate at the Parent's origin, but point to the new
   /// origin of the joint. This input vector is expected to be in the Parent's reference frame.
   void setVecFromParentToJointParentSpace( const Vector& vecParentToJointInParentSpace );


protected:
   WO* child = nullptr;
   WO* parent = nullptr;

   void verifyInput( WO* childWithSetParent, const Vector& normal, const Vector& lookDir );
   void initJointTransform();
   Vector transformFromWorldSpaceToParentObjSpace( const Vector& v );

   float ChildDeltaThetaWRTJoint; ///< Rotation about rel Z Axis (radians)
   float ChildDeltaPhiWRTJoint;   ///< Rotation about rel Y Axis (radians)
   float ChildDeltaRollWRTJoint;  ///< Rotations about rel X axis (radians)

   Vector jointToChildInParentObjSpace;
   Vector parentToJointInParentObjSpace;
   Vector initialJointNormal;
   Vector initialJointLookDir;

   float scaleMe = 1.0f;

   Mat4 jointTransform;

   void simpleConstructor( WO* childWithSetParent, const Vector& jointNormal, const Vector& jointLookDir );
   void complexConstructor( WO* childWithSetParent, const Vector& vecParentToJointInParentObjSpace,
                            const Vector& jointNormal, const Vector& jointLookDir, 
                            const Vector* vecJointToChildInParentObjectSpace );

   IndexedGeometryAxes* axes = nullptr;

};
/** \} */
} //namespace Aftr
