#pragma once

namespace Aftr
{

///Define IFace types implemented by WOs.
///This enables a bitmask check instead of using slower C++ RTTI and dynamic_cast<>()
//extern const unsigned int IFaceBitField_IFaceODECollisionSensor;
//extern const unsigned int IFaceBitField_IFaceODECollisionLoggerSink;
//extern const unsigned int IFaceBitField_IFaceODECollisionLoggerSource;
//extern const unsigned int IFaceBitField_IFaceODERayCast;
//extern const unsigned int IFaceBitField_IFaceWOODE;
//extern const unsigned int IFaceBitField_IFaceWONVPhysX;
//extern const unsigned int IFaceBitField_IFaceGUIWidget;

#define IFaceBitField_IFaceODECollisionSensor         (1)  /*rightmost bit         - 0000 0001b*/
#define IFaceBitField_IFaceODECollisionLoggerSink     (2)  /*second rightmost bit  - 0000 0010b*/
#define IFaceBitField_IFaceODECollisionLoggerSource   (4)  /*third ritghmost bit   - 0000 0100b*/
#define IFaceBitField_IFaceODERayCast                 (8)  /*                      - 0000 1000b*/
#define IFaceBitField_IFaceWOODE                      (16) /*                      - 0001 0000b*/
#define IFaceBitField_IFaceWONVPhysX                  (32) /*                      - 0010 0000b*/
#define IFaceBitField_IFaceGUIWidget                  (64) /*                      - 0100 0000b*/
//#define IFaceBitField_IFaceNVPhysXMesoCollider        (128)/*                      - 1000 0000b*/

class IFace;
class WO;

class IFace
{
public:
   IFace( WO* woUsingThisInterface );
   virtual ~IFace();
   /// Returns a pointer to the WO that implements this interface
   WO* getWO() { return this->woUsingThisInterface; }

   /**
      \return The bit field indiciating which IFaces this instance of a WOODE currently implements. '1's indicate
      an IFace is used; '0' indicates an IFace is not used. \see
   */
   unsigned int getIFacesUsedBitField();

   /**
      Instead of making each WOODE inherit from many different interfaces and polymorphically
      having to invoked dynamic_cast<>(), each WOODE has a 32-bit unsigned flag used to 
      store any Interfaces this WOODE may inherit from. During runtime, masking this flag
      is much faster than using the C-Runtime to determine polymorphism via dynamic_cast<>().
      IFaceODECollisionSensor and IFaceODERayCast are examples that use this flag.

   */
   void setIFaceUsedBitField( unsigned int newIFaceBitField );

   void setIFaceBitFieldBit( unsigned int IFaceBitField_Type );

   bool isSetIFaceBitFieldBit( unsigned int IFaceBitField_Type );

protected:
   WO* woUsingThisInterface; ///< A pointer to the WO which implements this interface
//private:
   //IFace(); ///< Protected default constructor enforcing user to pass in a WO*
   
   /**
      Bit mask containing a '1' for interfaces that are currently implemented by this WOODE instance. For example, if
      this WOODE instance also inherits from IFaceODECollisionSensor, then the corresponding bit shall
      be set. The default value is all zeros. The constructor of a specific IFace is required to set this bitfield
      appropriately. The user should not usually need to ever manipulate these.

      This functionality is essentially the same as using dynamic_cast< IFaceType* >( myWO ) != NULL. However,
      the run-time performance of dynamic_cast is too slow; hence, this field is maintained and read internally by the
      physics engine as a fast mechanism to determine which interface methods need to be invoked.
   */
   unsigned int IFacesUsedBitField;
};

} //namespace Aftr

