#pragma once

#include "WO.h"
#include "MGLBoundingShell.h"


namespace Aftr
{
/**
   \author Scott Nykl
   \brief This is the base class for any fluid (gas or liquid) that shall interact with 
   WOForceBuoy objects to simulate buoyancy within the engine. For example, the WOOcean
   is a child of this, overloads the appropriate methods
*/


class WOBuoyancyFluid : public WO
{
public:
   /**
      Creates an invisible fluid (gas or liquid) that exerts a buoyant
      force on WOForceBuoy objects associated with this fluid object.

      \param liquidDensity, Desired liquid density of this fluid.
      \param treatAsInfinitePlane If true, the Z-value of the Model defines an
      infinite plane such that all associated WOForceBuoy below that Z-value
      shall exert a buoyant force. If false, the Model's bounding box defines the
      rectangular prism such that contained and assocated WOForceBuoy exert a buoyant force.
   */
   WOBuoyancyFluid( float liquidDensity = 1020, bool IsInfinitePlane = true );

   /**Destructor*/
   virtual ~WOBuoyancyFluid();
   
   /**
      Returns the liquid density of this BuoyancyFluid
      \return float The liquid density of this fluid (gas or liquid)
   */
   virtual float getLiquidDensity() { return this->liquidDensity; }

   /**
      Returns the height (Z-value) of the fluid at a given (X,Y)point.
      If the fluid is an infinite plane, the (x,y) params are ignored.
      \param x the x coordinate corresponding to the unknown Z-value.
      \param y the y coordinate corresponding to the unknown Z-value.
      \return float The height (Z-Value) of the fluid at (x,y).
   */
   virtual float findWaterHeight(float x, float y);

   virtual bool pointLiesWithinFluidBoundary( const Vector& point );

   bool isInfinitePlane() { return this->IsInfinitePlane; }

protected:
   /**
      The liquid Density of this buoyant fluid.
      Common Liquid Densities:
         Sea Water = 1020 kg/m^3
         Air = Density  Temp(C)
               1.341    -10
               1.316    -5
               1.293     0
               1.269     5
               1.247    10
               1.225    15
               1.204    20
               1.184    25
               1.164    30
   */
   float liquidDensity;

   bool IsInfinitePlane;
};

} //namespace Aftr

