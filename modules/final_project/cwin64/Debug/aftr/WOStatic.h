//----------------------------------------------------------------------------
//Description: The WOStatic is an immovable object with which moving 
//objects can collide.
//
//Author: Scott Nykl
//----------------------------------------------------------------------------
#pragma once

#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_ODE
#include "WOODE.h"

//----------------------------------------------------------------------------
//Description: The WOFourWheeled class 
//----------------------------------------------------------------------------
namespace Aftr
{

class WOStatic : public WOODE
{

public:
   WOMacroDeclaration( WOStatic, WOODE );
   static WOStatic* New( const std::string& modelFileName, Vector scale = Vector(1,1,1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );
   
   virtual ~WOStatic();

   /**
      Serializes this WO instance and its specific member properties to the output stream.
      This method serializes enough state such that when this WO's corresponding fromFile(...)
      is invoked, all attributes and state are preserved.
   */
   virtual void toFile( std::ostream& sout );

   /**
      Deserializes a WO from the input stream and returns an instance of that
      specific WO type whos member properties are restored to the same state when the WO
      was serialized.
   */
   static WO* fromFile( std::istream& sin );


   //Creates the ODE Geom of the static object
   virtual void ODEinitializeInODE();

   /**
      The user can overload this method to smoothly update
      the WO::odeGeomID's position/orientation each physics tick.
   */
   virtual void ODEupdateForcesAndJoints() {}

   virtual void ODEupdateToNewPositionOrientation() {}

   //Position methods overloaded to support moving the graphical model as well as
   //ODE's collision geometry.
   virtual void setPosition( const Vector& newXYZ );
   virtual void setPosition( float x, float y, float z );
   virtual void setPositionIgnoringAllChildren( const Vector& newXYZ );
   virtual void moveRelative( const Vector& dXdYdZ );
   virtual void moveRelativeIgnoringAllChildren( const Vector& dXdYdZ );

   //Orientation methods overloaded to support moving the graphical model as well as
   //ODE's collision geometry.
   virtual void rotateToIdentity();
   virtual void rotateAboutRelX( float deltaRadianAngle );
   virtual void rotateAboutRelY( float deltaRadianAngle );
   virtual void rotateAboutRelZ( float deltaRadianAngle );
   virtual void rotateAboutGlobalX( float deltaRadianAngle );
   virtual void rotateAboutGlobalY( float deltaRadianAngle );
   virtual void rotateAboutGlobalZ( float deltaRadianAngle );

protected:
   WOStatic();

   /**
      Used internally by the overloaded orientation methods to take
      the graphical model's orientation and override the ODE collision
      geometry's orientation.
   */
   virtual void syncGFXOrientationToODEGeom();

   /**
      Each WOStatic must enable certain surface properties so an object that collides
      against this WOStatic (when this WOStatic is moving/rotating) has friction with
      this WOStatic.
   */
   virtual void initODESurface();

   virtual void toFileConstructorParams( std::ostream& sout );
   virtual void toFileWOState( std::ostream& sout );
   static ThisClassType* fromFileConstructorParams( std::istream& sin );
   virtual bool fromFileWOState( std::istream& sin );
   bool fromFileWOStateHelper( std::istream& sin, std::string& lhs, std::string& rhs );
};

} //namespace Aftr
#endif
