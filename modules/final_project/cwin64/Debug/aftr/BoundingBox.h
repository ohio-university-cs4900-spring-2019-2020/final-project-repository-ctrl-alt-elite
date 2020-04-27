//----------------------------------------------------------------------------
//Description: The BoundingBox class is a helper class for the Model class.
//The BoundingBox is used to find the two extreme verticies contained within
//a Model.  The midpoint between these two points represents the "center" of
//the Model.  This "center" is also know as the Model's fixedPoint.  This is
//the point about which all scalings and rotations occur.
//
//Author: Scott Nykl
//----------------------------------------------------------------------------

#pragma once

#include "Vector.h"
#include "AftrOpenGLIncludes.h"
#include "Mat4Fwd.h"

//----------------------------------------------------------------------------
//Description: The BoundingBox class is a helper class for the Model class.
//The BoundingBox is used to find the two extreme verticies contained within
//a Model.  The midpoint between these two points represents the "center" of
//the Model.  This "center" is also know as the Model's fixedPoint.  This is
//the point about which all scalings and rotations occur.  The smallest X, Y,
//and Z components are found and create a min Vector.  The largest X, Y, and 
//Z components are also found and create a max Vector.
//----------------------------------------------------------------------------
namespace Aftr
{

class IndexedGeometryRectangularPrism;

class BoundingBox
{
public:
   /**
      Constructor that instantiates a new BoundingBox.
   */
   BoundingBox();
   BoundingBox( const BoundingBox& toCopy );
   BoundingBox( BoundingBox&& toMove );

   /**
      Destructor that deletes and NULL-ifys all pointers owned by this 
      instance.
   */
   virtual ~BoundingBox();

   BoundingBox& operator=( const BoundingBox& box );
   BoundingBox& operator=( BoundingBox&& box );

   friend std::ostream& operator <<( std::ostream& out, const BoundingBox& b );

   virtual void render( const Camera& cam, const Mat4& modelMatrix );
   virtual void render( const Mat4& MVPMatrix );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );

   /**
      This method takes in a vertex and checks to see if any of its X, Y, or Z
      components are an extreme min or extreme max.
   */
   void updateBBox( const Vector* p );
   void updateBBox( const Vector& p );
   void updateBBox( const float* const xyzVertArray, const size_t numVerts );
   void updateBBox();

   std::string toString() const;

   /**
      This method returns the current minimum of all components of each Vector
      that has been processed; that is, the smallest X, Y, and Z found are 
      returned.
      \return Vector* : A Vector pointer to the minimum.
   */
   Vector getMin() const { return this->min; }

   /**
      This method returns the current maximum of all components of each Vector
      that has been processed; that is, the largest X, Y, and Z found are 
      returned.
      RETURN: Vector* : A Vector pointer to the maximum.
   */
   Vector getMax() const { return this->max; }

   Vector getCenterPoint() const { return( (this->max + this->min) / 2.0f ); }

   /**
      This method returns a Vector containing the dimensions of the model.
      \return Vector: x component: lx( max.x - min.x )
      Vector: y component: ly( max.y - min.y )
      Vector: z component: lz( max.z - min.z )
   */
   Vector getlxlylz() const;

   /**
      This method allows the user to specify his own dimension of the bounding
      box for this model. This is useful when a user wants only part of a model
      or wants a larger part of a model to be taken into account when ODE
      initializes the collision volumes for each WO.
      Note, this does NOT modify the actual size of the model object, it
      only changes the dimensions of the stored bounding box. Thus when the 
      WO in created in ODE, the collision volume will be the size 
      specified within the bounding box.
      PARAM: Vector& v The new length of this model's bounding box.
      v.x = new length of x component
      v.y = new length of y component
      v.z = new length of z component
   */
   void setlxlylz( const Vector& v, Vector centerPoint = Vector(0,0,0) );

   /** 
      Takes as input an array of 8 Aftr::Vectors. It populates each Vector
      with the 8 original points of the bounding box. The points are assigned
      as follows. The bounding box is always centered about the origin and 
      assume the viewer is located at the origin looking along the +x axis.
      verts[0] is "front top left" +++
      verts[1] is "front bottom left" ++-
      verts[2] is "front top right" +-+
      verts[3] is "front bottom right"  +--
      verts[4] is "back top left" -++
      verts[5] is "back bottom left" -+-
      verts[6] is "back top right" --+
      verts[7] is "back bottom right" ---
   */
   void getBoundingBoxVerts( Vector* verts );
   static const int XYZ = 0;
   static const int XY_Z = 1;
   static const int X_YZ = 2;
   static const int X_Y_Z = 3;
   static const int _XYZ = 4;
   static const int _XY_Z = 5;
   static const int _X_YZ = 6;
   static const int _X_Y_Z = 7;

   /**
   The following functions allow you to retrieve specific edges of the bounding box
   */
   //X edges
   void getTopLeftXEdge( GLfloat* verts );
   void getBottomLeftXEdge( GLfloat* verts );
   void getTopRightXEdge( GLfloat* verts );
   void getBottomRightXEdge( GLfloat* verts );
   //Y edges
   void getTopFrontYEdge( GLfloat* verts );
   void getBottomFrontYEdge( GLfloat* verts );
   void getTopBackYEdge( GLfloat* verts );
   void getBottomBackYEdge( GLfloat* verts );
   //Z edges
   void getFrontLeftZEdge( GLfloat* verts );
   void getRearLeftZEdge( GLfloat* verts );
   void getFrontRightZEdge( GLfloat* verts );
   void getRearRightZEdge( GLfloat* verts );


protected:

   void initMemberData();

   struct VLE_3VF_3CUB
   {
      GLfloat x, y, z;
      GLubyte r, g, b;
   };

   void generateVerts();
   bool OnFirstRender;

   void generateVertexArrayData();

   GLuint vao = 0; // Vertex Array Object handle (core)
   GLuint vertBO = 0; // Vertex Buffer Object (core)
   GLuint idxBO = 0; // Index Buffer Object (core)
   GLubyte vertexListSize = 0;
   GLubyte indexListSize = 0;
   VLE_3VF_3CUB* vertexList = nullptr;
   GLubyte* indexList = nullptr;

   Vector min;   //< The smallest X, Y, and Z components found thus far.
   Vector max;   //< The largest X, Y, and Z components found thus far.

   IndexedGeometryRectangularPrism* prism = nullptr;
};
} //namespace Aftr
