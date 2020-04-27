#pragma once

#include "AftrGlobals.h"
#include "AftrOpenGLIncludes.h"
#include "Vector.h"
#include "Mat4.h"
#include "BoundingBox.h"
#include "AftrUtilities.h"
#include <iostream>
#include <set>

#include "ModelDataShared.h"
#include "ModelMesh.h"
#include "ModelMeshDataShared.h"
#include "ModelMeshRenderDataGenerator.h"
#include "ModelMeshSkin.h"

namespace Aftr
{

class ModelDataShared;
class ModelOctreeOfVertices;
class ModelKDTreeOfVertices;
class AftrGeometryPlane;
class AftrGeometryFrustum;
class Texture;
class WO;
class ModelLODPolicy;
class AftrGeometryRayVsFace;

/**
   \class Model
   \brief This class represents a Model. Models are rendered via graphical 
   hardware acceleration (in this case via OpenGL) to a display.

   This model supports multiple  sets of Meshes, each Mesh containing 
   its own skin supporting multi-texturing, shaders,
   and Material properties.

   This class represents a Model. Models are rendered via graphical 
   hardware acceleration (in this case via OpenGL) to a display. This
   implementation is designed to be highly efficient in terms of 
   graphical hardware performance as well as host memory size. All data
   related to rendering Models (verticies, indicies, textures, shaders)
   is automatically divided into two parts - 1) sharable data and 2)
   per instance data. Sharable data is managed via Multiplicity Managers and
   resides in CPU memory and graphics memory exactly once. All Models
   utilizing the same underlying geometry share the one instance. Per
   instance data is modifiable data specific to each instance of a model;
   this data enables two models sharing the same geometry to be rendered 
   differently (different colors, textures, materials, positions,
   orientations, etc).
   
   For instance, if 25 cars were all loaded from 'ferrari2009.3ds'. The file
   would be parsed exactly once; the geometry information would be placed in
   graphics memory exactly once. However, each submesh of each car could 
   utilize a  different shader, different material properties, and different 
   sets  of multi-textures (bump-mapping, etc). From a user's perspective, 
   the user would percieve 25 individual copies of 'ferrari2009.3ds' 
   existing in the world; this mechanism reduces CPU-side RAM as well as 
   graphics-side RAM.

   All objects are rendered via OpenGL using indexed geometry objects; namely,
   Vertex Buffer Objects (VBOs) or Vertex Array Objects (VAs). If the current
   machine supports VBOs, all non-deformable geometry is placed in a VBO and
   rendered via the VBO handle; this sends all data to the graphics card exactly
   once at load time. Any rendering of these objects is then performed on graphics
   hardware limited only by the graphics hardware. If the current machine does not
   support VBOs, or if the geometry is deformable, then VAs are used to perform
   the rendering. VAs send the data to the graphics card each render; however
   optimized drivers cache the VA data on the graphics card and only need to
   update the deformed geometry.

   This implementation is OpenGL 3.0 forward compatible, if enabled, but also
   supports fixed functionality. Again, all rendering is done with indexed
   geometry; that is, no display lists, no immediate mode rendering.

   Model Hierachy:

   A Model is a collection of one or more
   submeshes (encapsulated within ModelDataShared).
   Each submesh (ModelMesh) contains a Skin (ModelMeshSkin) and
   rendering data (ModelMeshDataShared).

   Each Skin contains a Texture set (used for mult-texturing), 
   an OpenGL Shader (GLSLShader), Material properties (ambient, diffuse, specular,etc),
   and a shading type (flat or smooth).

   Each Texture can be manipulated, i.e., scaled, rotated, translated. OpenGL texture
   parameters can be set (1D, 2D, 3D, 4D textures, mipmapping, minFilter, magFilter,
   etc) can be set on a per Texture basis.

   Each Shader can use any vertex shader along with any fragment shader.

   Any Skin can be applied to any Mesh.

*/
class Model
{
public:
   static Model* New( WO* parentWO );
   static Model* New( WO* parentWO, const std::string& modelFileName, const Vector& scale, 
                          MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO );
   static Model* New( WO* parentWO, ModelDataShared* modelDataShared );

   virtual ~Model();
   virtual void render( const Camera& cam );
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );

   virtual ModelDataShared* getModelDataShared();

   virtual std::string getFileName();
   virtual Vector getInitialScaleFactor();

   /**
      This method restores the Model to its original position, size, and 
      orientation; that is, the position, size, and orientation the model had
      immediately after being loaded from file.
   */
   virtual void resetModel();

   /// Returns a pointer to a list containing all verticies within this model.
   /// This list is indexed by the corresponding CompositeIndexList.
   virtual const std::vector< Vector >& getCompositeVertexList() const;

   /// Returns a pointer to a list containing all indicies into the corresponding
   /// CompositeVertexList.
   virtual const std::vector< unsigned int >& getCompositeIndexList() const;

   /// Returns a pointer to a list containing all verticies within this model.
   /// This list is indexed by the corresponding CompositeIndexList.
   virtual std::vector< Vector* >* getCompositeTangentList();
   
   /// Returns a reference to this Model's current BoundingBox
   virtual BoundingBox& getBoundingBox();
   virtual const BoundingBox& getBoundingBox() const;

   /**
      Takes as input an array of 8 Aftr::Vectors. It populates each Vector
      with the 8 CURRENT points of the bounding box. That is, each of the original
      verticies of the bounding box are transformed by this model's current display
      matrix to properly orient each of the 8 verticies. The points are assigned
      as follows. The bounding box is always centered about the origin and 
      assume the viewer is located at the origin looking along the +x axis. The 
      +z-axis is 'up' and the +y-axis equal to the +x-axis rotated 90 degrees
      counter clockwise about the +z-axis.
      verts[0] is "front top left"
      verts[1] is "front bottom left"
      verts[2] is "front top right"
      verts[3] is "front bottom right"
      verts[4] is "back top left"
      verts[5] is "back bottom left"
      verts[6] is "back top right"
      verts[7] is "back bottom right"
      Remember that because this box is oriented via this model's display matrix,
      the box could be flipped around and/or upside down, so verts[0] may not appear
      to be the "front top left" anymore.
   */
   virtual void getCurrentBoundingBoxVerts( Vector* verts );

   /**
      Takes as input an array of 6 AftrPlanes. It populates each Plane
      with the 6 CURRENT faces of the bounding box. That is, each of the original
      planes of the bounding box are transformed by this model's current display
      matrix to properly orient each of the 6 faces. The faces are assigned
      as follows. The bounding box is always centered about the origin and 
      assume the viewer is located at the origin looking along the +x axis. The 
      +z-axis is 'up' and the +y-axis equal to the +x-axis rotated 90 degrees
      counter clockwise about the +z-axis. All face normals point away from the
      center of the bounding box.
      faces[0] is "front face"
      faces[1] is "right face"
      faces[2] is "back face"
      faces[3] is "left face"
      faces[4] is "bottom face"
      faces[5] is "top face"
      Remember that because this box is oriented via this model's display matrix,
      the box could be flipped around and/or upside down, so faces[0] may not appear
      to be the "front face" anymore.
   */
   virtual void getCurrentBoundingBoxFaces( AftrGeometryPlane* faces );

   /**
      This method uses the data collected from the BoundingBox to compute the
      "center point" of the Model.  This is the point around which scalings and
      rotations shall occur.
   */
   virtual void calculateFixedPointFromBBox();

   /**
      This method creates a AftrGeometryOBB (oriented bounding box) based off of the model's
      current orientation and current bounding box size. The lengths of the OBB are determined 
      by calling this instance's getBoundingBox() method. The OBB has a method called
      getCurrentTransformedVerts(...) which will produce the same results a this instances
      getCurrentBoundingBoxVerts(...). The OBB is preferred in cases where collision 
      detection / frustum culling is performed; hence both methods are provided as a convenience.
   */
   virtual AftrGeometryOBB getCurrentOBB();

      /**
      Given this model's current global position / orientation and the in passed 
      camera's current position / viewing properties, this method computes the
      lengths of a billboarded quad in world space (encompassing all of the meshes contained 
      in this model. This billboarded quad is the proper 
      size for rendering this mesh to an texture (from camera) and binding that 
      texture across the quad. The returned X is the billboards width, and the
      returned Y is the billboards height.

      This method is utilized by the LOD system.

      Returns the Lx and Ly lengths of the billboard's geometry when rendered
      from camera at this model's current global position. Lx and Ly are stored in
      the returned vector's .x and .y components, respectively. Lx and Ly are
      in world space.
   */
   Vector getBillboardLxLyInWorldSpace( Camera* cam, Vector* outBillboardCenterPosInWorldSpace = NULL );
   Vector getBillboardLxLyInWorldSpaceCachingIntermediateResults( Camera* cam, Vector* outBillboardCenterPosInWorldSpace = NULL );

   /**
      This method takes the current 8 vertices of the this model's current
      OBB, transforms them from world space to screen space, builds a tight axis-aligned
      bounding box, and transforms these new 4 screen space verts back to world space.
      Then the x and y lengths are computed and returned. No z values are returned as
      x represents the billboard's width and y represents the billboard's height.

      Optionally, if the user would also like to retrive the w (perspective divide scalar) of
      this mesh's current centerposition (in world space), an out only point may be passed in.
   */
   Vector getBillboardLxLyInScreenSpace( Camera* cam, Vector* outModelCenterPtInScreenSpace = NULL, 
                                         float* outModelCenterPtPerspectiveDivideScalar = NULL,
                                         Vector* outCenterOfSSBBox = NULL );
   Vector getBillboardLxLyInScreenSpaceCachingIntermediateResults( Camera* cam, Vector* outModelCenterPtInScreenSpace = NULL, 
                                         float* outModelCenterPtPerspectiveDivideScalar = NULL,
                                         Vector* outCenterOfSSBBox = NULL );
   

   /**
      This method moves the model's center (fixedPoint) to the new x, y ,z
      location.
      \param newLocation a vector containing the new x, y, z 
      coordinates where the model's fixedPoint shall reside.
   */
   void setPosition( const Vector& newLocation );
   void setPosition( float x, float y, float z );

   /**
      This method moves the model's center (fixedPoint) by delta dxdydz
      \param dxdydz: a vector containing the change in position of x, y, z 
      coordinates where the model's fixedPoint shall reside.
   */
   void moveRelative( const Vector& dxdydz );

   /**
      Returns the Global X,Y,Z coordinate at which this model is currently
      centered.
   */
   Vector getPosition();

   /**
      Computes a returns a normalized Vector which represents the direction 
      the "front" of the model is facing. For example, if this is a VRML model
      read in from Blender. Our convention assumes the front of the model
      points along the positive x-axis and the top of the model points along 
      the positive z-axis. The 'left' of the model will point along the y-axis.
      \return A Normalized Vector representing the direction the model is
      currently facing.
   */
   virtual Vector getLookDirection() const;

   /**
      Sets this model's look direction (relative x axis) to the in passed 
      Vector. The model's normal direction (relative z axis) will remain 
      in the same relative XZ plane as the new look direction.
   */
   virtual void setLookDirection( const Vector& newLookDir );

   /**
      Computes a returns a normalized Vector which represents the direction 
      perpendicular to the direction the model is facing. For example, 
      if this is a VRML model
      read in from Blender. Our convention assumes the front of the model
      points along the positive x-axis and the top of the model points along 
      the positive z-axis. Therefore, this method would return a vector 
      pointing along the +z-axis
      \return A Normalized Vector representing the direction the model is
      currently facing.
   */
   virtual Vector getNormalDirection() const;

   /**
      Sets this model's normal direction (relative z axis) to the in passed 
      Vector. The model's look direction (relative x axis) will remain
      in the same relative XZ plane as the new normal direction.
   */
   virtual void setNormalDirection( const Vector& newNormalDir );

   virtual Vector getRelXDir() const; ///< Returns local +x axis of this model's coordinate frame
   virtual Vector getRelYDir() const; ///< Returns local +y axis of this model's coordinate frame
   virtual Vector getRelZDir() const; ///< Returns local +z axis of this model's coordinate frame

   void rotateToIdentity();
   void rotateAboutRelX( float deltaRadianAngle );
   void rotateAboutRelY( float deltaRadianAngle );
   void rotateAboutRelZ( float deltaRadianAngle );
   void rotateAboutRelAribitraryAxis( const Vector& axisOfRot, float radianDistance );
   void rotateAboutGlobalX( float deltaRadianAngle );
   void rotateAboutGlobalY( float deltaRadianAngle );
   void rotateAboutGlobalZ( float deltaRadianAngle );
   /**
      Rotates the Model about the passed in axis of rotation by the specified
      number of radians.

      \param axisOfRotation The axis about which rotation shall take place.
      \param radianDistance The number of radians to rotation about the axis
             of rotation.
   */
   void rotateAboutGlobalAribitraryAxis( const Vector& axisOfRot, float radianDistance );

   /**
      Takes the Vector vec as input and transforms vec through this Model's
      current display matrix. The resulting Vector is returned. For example,
      if the in passed vec was 1,0,0 (+X-axis), and the Model was currently
      rotated PI/2 radians about its local Z-axis, then the resultant 
      vector returned would be 0,1,0 (+Y-axis). Of course, this assumes that
      the Model's initial orientation was facing along the +X-axis, as per the
      Aftr Engine convention for initial Model orientation.
      \param vec The Vector to be transformed (multiplied through the current
                 display matrix) of this Model.
      \return The resultant Vector that has been transformed by this Model's
              current display matrix. This resultant is NOT normalized; the
              resultant is only normalized for the case where the input vec
              was normalized prior to calling this method.
   */
   virtual Vector transformVecThroughCurrentDisplayMatrix( const Vector& vec );
   virtual Vector transformVecThroughCurrentDisplayMatrixAndThenAddCurrentPosition( const Vector& vec);
   virtual Vector transformVecThroughCurrentDisplayMatrixAfterSubtractingCurrentPosition( const Vector& vec);
   virtual Vector transformVecThroughInverseOfCurrentDisplayMatrix( const Vector& vec );
   virtual Vector transformVecThroughInverseOfCurrentDisplayMatrixAndThenAddCurrentPosition(const Vector& vec);
   virtual Vector transformVecThroughInverseOfCurrentDisplayMatrixAfterSubtractingCurrentPosition(const Vector& vec);

   /// Returns the inverse matrix of this models display matrix
   void calculateInverseOfMyDisplayMatrix( float* resultantInverseMatrix4x4 );

   /// Returns true iff any part of this model's bounding box intersects with the in passed viewing frustum.
   virtual bool isInViewingFrustum( const AftrGeometryFrustum& frustum );

   /// \return a Vector containing the scalings of the model in the X,Y, and Z directions, respectively.
   virtual Vector getScale() const;

   /**
      Sets this model's current scale. It is recommending that the user instead specify this vector
      in the model's constructor. Using this method does not directly change the model's bounding box;
      if the WO containing this model has an ODE physics body, this method will cause the graphical
      representation to become larger than the physical representation.

      If the WO containing this model has no corresponding physics body, then just the bounding box
      will become invalid.
   */
   virtual void setScale( const Vector& newScaleFactor );

   /**
      Scales a model's X, Y, and Z components.  EX: if scaleVect was (2, 1, .5)
      The models's X dimension would double, the models's Y dimension would
      remain unchanged, and the models's Z dimension would be reduced by one
      half.
      scaleVect: The X, Y, and Z components by which the Model
      will be scaled.
   */
   //void scaleModel( const Vector& scaleVect );

   /**
      This method returns a copy of the current model's display matrix. The
      caller owns this copy and is responsible for destroying it. 16 floats
      will be placed in the output param. Vectors are column major. The last
      column does NOT include the translate amount (this->translateAmt). Use
      getDisplayMatrixWithPos(...) to include the translate amount in the 
      last column, or manually populate it after this method returns.
      \param float[16] current model's display matrix.
   */
   void getDisplayMatrix( float* outParam4x4DispMat ) const;

   Mat4 getDisplayMatrix() const;
   Mat4 getModelMatrix() const; ///< Returns the full 4x4 model matrix used by a shader, including orientation, position, scale.
   Mat4 getNormalMatrix( const Camera& cam ) const; ///< Return a 4x4 normal matrix used by shader, same as the deprecated gl_NormalMatrix.

   /**
      This method returns a copy of the current model's display matrix. The
      caller owns this copy and is responsible for destroying it. 16 floats
      will be placed in the output param. Vectors are column major. The last
      column additionally includes the translate amount (this->translateAmt).
      Use getDisplayMatrix(...) to avoid the translate amount in the 
      last column.
      \param float[16] current model's display matrix. Last column additional
      contains the translateAmt of this model.
   */
   void getDisplayMatrixWithPos( float* outParam4x4DispMatWithPos ) const;

   /**
      This method returns a copy of the current model's upper 3x3 
      orientation matrix. The
      caller owns this copy and is responsible for destroying it. 9 floats
      will be placed in the output param. Vectors are column major.
      \param float[9] current model's display matrix.
   */
   void getDisplayMatrix33( float* outParam3x3DispMat ) const;

   /**
      This method sets the current model's display matrix. A copy of the matrix
      passed in by the caller is made; therefore, the caller still owns the 
      matrix he passes in and is responsible for destroying it.
      \param float[16] display matrix applied to this model.
   */
   void setDisplayMatrix( const float* dispMatrix4x4 );

   void setDisplayMatrix( const Mat4& dispMatrix );

   /**
      Sets the point about which all rotations of this model occur. The input is specified
      as an offset from this model's local coordinate system's center. This is typically
      (0,0,0), but may be different in cases where, for example, the verticies read from
      file are not centered about the origin. This method exists to enable a user to 
      explicitly set the model's fixed point if the default is not satisfactory.
   */
   void setFixedPoint( const Vector& fixedPoint );

   /**
      Gets the point about which all rotations of this model occur. This is typically
      (0,0,0), but may be different in cases where, for example, the verticies read from
      file are not centered about the origin. This method exists to enable a user to 
      explicitly get the model's fixed point if the default is not satisfactory.
   */
   Vector getFixedPoint() const;

   /**
      \returns number of faces in the model (may need to be overloaded for MGLs)
   */
   virtual size_t getFaceCount();

   /**
      If true, the Model's render will enable GL_BLEND; if false, the Model's render will disable
      GL_BLEND.
   */
   bool isUsingBlending() const { return this->useBlending; }
   void isUsingBlending( bool useBlending ) { this->useBlending = useBlending; }

   /**
      If true, the Model's render will invoke glDepthMask( GL_TRUE ); this will
      enable writing into the depth buffer.
      If false, the Model's render will invoke glDepthMask( GL_FALSE ); this
      will disable writing into the depth buffer.
   */
   bool isUsingDepthMask() const { return this->useDepthMask; }
   void isUsingDepthMask( bool enableDepthMasking ) { this->useDepthMask = enableDepthMasking; }

   /**
      Populates output with the nearest point where the line between from and to intersects the model, defined by
      Aftr conventions, i.e. uses composite index and vertex lists.

      This method assumes the Model is centered at the origin with the identity orientation.
      The user would typically call WO::getNearestPointWhereLineIntersectsMe(...) instead of
      this method if he wished to intersect a ray at an arbitrary location with a 
      WO(containing this model) at an arbitrary location and orientation.

      returns AftrGeometricTerm::geoSUCCESS if a point is found
      returns AftrGeometricTerm::geoERROR if no point is found
   */
   AftrGeometricTerm getNearestPointWhereLineIntersectsMe(const Vector& rayTail, 
      const Vector& rayHead, Vector& output, bool lineSegment = true, 
      bool useOctreeSearchIfAvailable = true, Vector* statistics = NULL, AftrGeometryRayVsFace* hitFace = NULL );

   /**
      This method is O(N) and is not intended to be used by larger models. For larger
      models, both Octree and KD-tree objects are supported by this model class. It is
      recommended to use the KD-tree to find the nearest point p to a set of points in
      set X. The KD-tree is O( log N ) and is more efficient on larger data sets.

      \return The Index into the Model:compositeVertexList corresponding to the
      vertex which is closest to the in passed vertex p. The corresponding float
      is the distance from p to the vector at the returned index.
   */
   std::pair< int, float > findNearestPointInThisModel( const Vector& p );

   /**
      \return An octree of this model's verticies sorted allowing logarithmic
      searching of closest point. User MUST invoke Model::generateOctreeOfVerticies()
      prior to a non-NULL octree being returned.
   */
   ModelOctreeOfVertices* getOctreeOfVertices();

   ModelKDTreeOfVertices* getKDTreeOfVerticies();

   /**
      Given a AftrGeometryRayVsFace with 3 valid compIndices and a model-space contact point,
      return the barycentric interpolated UV coordinate corresponding to the 3D model-space contact point.

      A simple way to properly generate the input face is to invoke 
      Model::getNearestPointWhereLineIntersectsMe( ... AftrGeometryRayVsFace* hitFace...)
      and pass in a non-NULL AftrGeometryRayVsFace. The resultant hitFace will be populated
      with this model's composite indices as well as the object-space (model-space) 3D contact point.

      This method will then compute the precise UV coordinate given the face. The returned vector outUVCoord.xy 
      components correspond to the .uv texture coordinates.

      Returns True if this model has texture coordinates and was able to properly interpolate (barycentric coords)
      the UV coordinate of the object-space contact point within the triangle specified by the 3 indices
      of the inputted AftrGeometryRayVsFace; false, otherwise.
   */
   bool getUVCoordInterpolatedAcrossFace( const AftrGeometryRayVsFace& face, Vector& outUVCoord ) const;

   /**
      Given a AftrGeometryRayVsFace with 3 valid compIndices and a model-space contact point,
      return the barycentric interpolated VertexAttributes corresponding to the 3D model-space contact point.

      \param face: the face with 3 valid compositeIndices into this model's composite index list as well
                   as a valid contact point. This is used to compute the barycentric coefficients in the
                   x,y,z directions of the face (in object / model space / local space).

      \param attributeName specifies the name of the vertex attribute (same as the variable within the shader, ie,
                  "tangent" or "quadric".

      \param atType specifies the type of the attribute to be retrieved; ie, 3 floats? 1 integer? etc.

      \param outBuf output from this method. This array must contain at least enough space to store the
             type specified in 'atType'. For example if atType was atVEC3, outBuf must be at least
             the size of 3*sizeof(GLfloat) (or GLfloat vals[3]).


   */
   bool getPerVertexAttributeInterpolatedAcrossFace( const AftrGeometryRayVsFace& face,
                  const std::string& attributeName, GLSLAttributeType atType, void* outBuf );

   /**
      Returns the WO that points to this Model instance. This value is valid after 
      the Model's constructor completes.
   */
   WO* getParentWO();

   /**
      This generates an octree of all the verticies contained by this model's
      composite vertex and composite index list. The user must invoke this to 
      generate and populate the octree. This is not done by default since an octree
      is not necessarily needed for normal circumstances.
   */
   void generateOctreeOfVerticies( unsigned int maxNumFacesPerSubnode, unsigned int maxNumSubdivisions );
   void generateKDTreeOfVerticies();

   /// Prints this models display matrix
   void printMyDisplayMatrix( std::ostream& os = std::cout, unsigned int decimalPrecision = 3 );
   /// Prints the composite vertex list
   void printMyCompositeVertexList( std::ostream& os = std::cout, unsigned int decimalPrecision = 3 );
   /// Prints the composite index list
   void printMyCompositeIndexList( std::ostream& os = std::cout );

   bool renderBBox = false;      ///< If true, this model's corresponding bounding box is visible; otherwise, it is not rendered
   bool renderWireframe = false; ///< If true, this model's wireframe is rendered; otherwise, its triangles are rendered.
   bool renderOctree = false;    ///< If true and this model's octreeVerts is not NULL, the octree is rendered.

   /**
      This set is used by the WorldContainer acceleration structure to determine which ModelMeshes fall within
      the current viewing frustum. This list is completely managed by the WorldContainer and generally does 
      not require any user manipulation. During each frame, visible meshes owned by this Model are inserted
      into the set. If no meshes are inserted, this model's render is not invoked. If some meshes are inserted,
      only those meshes are rendered when this model's render() method is invoked. The set is cleared after
      each render() and repopulated within the WorldContainer::update( Camera* cam ) during the next main
      iteration.
   */
   std::set< ModelMesh* >& getVisibleMeshesForThisFrame();

   /**
      True iff this instance's std::set< ModelMesh* > visibleMeshesForThisFrame has
      been populated by the WorldContainer::update() method.
      This bool is set true from within WorldContainer::update() iff the specific
      WorldContainer performed ModelMesh culling for accelerated rendering.
   */
   bool useVisibilityMeshesForThisFrame = false;

   /**
      This method sets the Model's level of detail (LOD) policy. This value defaults to NULL. In order for
      this policy to be used during rendering, the ModelLODPolicy::setEnabled( true ), must be invoked by
      the user.

      If an existing Policy has already been set, it will be destroyed and replaced by the new policy.
   */
   void setModelLODPolicy( ModelLODPolicy* lodPolicy );
   ModelLODPolicy* getModelLODPolicy();

   /**
      Convenience methods that can be used by Model so accessing skins and textures doesn't necessarily
      need to call:
      wo->getModel()->getModelDataShared()->getModelMeshes().at( meshIdx )->getSkins().at( skinIdx );
      The last param in each of these convenience methods is the meshIdx to access and it defaults to
      0. It is typically safe to assume an average model has a mesh at 0. MGLs and subclasses may treat
      the index in a manner they see fit, including ignoring it as many MGLs may not have internal notions
      of meshes.   
   */

   /**
      Returns the current skin in use with the modelMeshIdx'th ModelMesh contain within this Model.
      This is a convenience method and is the same as calling:
      wo->getModel()->getModelDataShared()->getModelMeshes().at( modelMeshIdx )->getSkin();

      For MGLs and MGL subclasses, this method also serves as a polymorphic method that lets a
      base Model pointer access the internal skin being used even when those MGLs don't have ModelDataShared 
      instances or mesh instances.
   */
   virtual ModelMeshSkin& getSkin( size_t modelMeshIdx = 0 );

   /**
      Returns the current set of skins associated with the modelMeshIdx'th ModelMesh contain within this Model.
      This is a convenience method and is the same as calling:
      wo->getModel()->getModelDataShared()->getModelMeshes().at( modelMeshIdx )->getSkins();

      For MGLs and MGL subclasses, this method also serves as a polymorphic method that lets a
      base Model pointer access the internal skins being used even when those MGLs don't have ModelDataShared
      instances or mesh instances.
   */
   virtual std::vector< ModelMeshSkin >& getSkins( size_t modelMeshIdx = 0 );

   virtual void addSkin( ModelMeshSkin&& skinToOwn, size_t modelMeshIdx = 0 ); ///< Moves the in passed skin into the specified ModelMesh's skin list
   virtual void addSkin( const std::string& pathToTexture, size_t modelMeshIdx = 0 ); ///< Creates a Skin using the texture passed in. Inserted into the specified ModelMesh.
   virtual void addSkin( Texture* texThisMGLTakesOwnership, size_t modelMeshIdx = 0 ); ///< Creates a Skin using the texture. This Model takes ownership of the in passed texture. Inserted into the specified ModelMesh.
   virtual void useNextSkin( size_t modelMeshIdx = 0 );
   virtual void usePreviousSkin( size_t modelMeshIdx = 0 );
   virtual void useSkinAtIndex( size_t skinIndex, size_t modelMeshIdx = 0 );
   virtual size_t getSkinIndex( size_t modelMeshIdx = 0 );

protected:
   Model( WO* parentWO );
   void onCreate();
   void onCreate( const std::string& modelFileName, const Vector& scale, const MESH_SHADING_TYPE& shadingType );
   void onCreate( ModelDataShared* modelDataShared );

   ModelDataShared* modelData = nullptr; ///< This data is managed by the ManagerModelMultiplicity
   WO* parentWO = nullptr; ///< This WO's model* points to this model. Not owned, do not delete.

   float dispMatrix[16]; ///< Aggregation of rotations. Does not include translations or scalings. Translations are access via get/setPosition(...).
   
   Vector fixedPoint;    ///< scalings and rotations are w.r.t this point (computed based on bBox)
   Vector translateAmt;  ///< current X,Y,Z location of this Model
   Vector scaleFactor;   ///< Scale factor of original size of this model. Only used for rendering, does not effect internal verticies/bounding boxes.
   bool useScaleFactor = false;  ///< True iff, the user has invoked setScaleFactor at least once.

   bool useBlending = true; ///< When true, the render will glEnable( GL_BLEND ), when false, it will disable GL_BLEND
   bool useDepthMask = true; ///< When true, the render will glDepthMask(GL_TRUE), when false, it will glDepthMask(GL_FALSE)

   ModelOctreeOfVertices* octreeVerts = nullptr; ///< Octree of sorted verticies (via indicies) contained in this model.
   ModelKDTreeOfVertices* kdTreeVerts = nullptr; ///< KD Tree of sorted verticies(via indicies) contained in this model.

   /**
      This set is used by the WorldContainer acceleration structure to determine which ModelMeshes fall within
      the current viewing frustum. This list is completely managed by the WorldContainer and generally does 
      not require any user manipulation. During each frame, visible meshes owned by this Model are inserted
      into the set. If no meshes are inserted, this model's render is not invoked. If some meshes are inserted,
      only those meshes are rendered when this model's render() method is invoked. The set is cleared after
      each render() and repopulated within the WorldContainer::update( Camera* cam ) during the next main
      iteration.
   */
   std::set< ModelMesh* > visibleMeshesForThisFrame;

   /**
      A model is composed of one or more meshes. Each mesh may have one or more associated level of detail (LOD)
      algorithms. However, each ModelMesh itself, does not have enough global information to make a good
      decision about how / when it should perform an update / modification to its LOD. 
      
      This object represents the policy defining when each of this model's mesh's LODs should be updated, and
      how they should be updated (only a subset of the mesh's LODs may be updated, for example, the LODs with
      the highest current error). This policy object has useful information, such as how many milliseconds (ms)
      are available for this model to perform any its LOD updates and render those LODs.

      This policy also specifies which error metric is used.

      If this object is not NULL and its setEnabled() is true, then the default behavior is to invoke this
      policy object's onApplyPolicy() method exactly once inside of this Model's render() method. If onApplyPolicy()
      is invoked, no other rendering of this model's data will occur (other than what onApplyPolicy() does as well
      as rendering the bbox or octree, if those are enabled).
   */
   ModelLODPolicy* lodPolicy = nullptr;
   
   /**
      When a Model changes its position, it notifies the WorldContainer instance. This is
      used by the WorldContainer subclasses, such as the WorldOctree, to identify when a mesh may have
      changed which node it resides in. This notification is used when the WorldContainer::update(...)
      method is invoked (immediately before WorldContainer::render( const Camera& cam ) is invoked).
      When invoked, the WorldContainer acceleration structure, such as the dynamic octree, can
      update the meshes (belonging to this model) to the proper node to ensure they are efficiently/properly
      culled during render.

      This method is invoked by any method in the Model class which manipulates Model::translateAmt.
   */
   virtual void notifyWorldContainerOfAChangeInPosition();

   /**
      When a Model changes its orientation, it notifies the WorldContainer instance. This is
      used by the WorldContainer subclasses, such as the WorldOctree, to identify when a mesh may have
      changed which node it resides in. This notification is used when the WorldContainer::update(...)
      method is invoked (immediately before WorldContainer::render( const Camera& cam ) is invoked).
      When invoked, the WorldContainer acceleration structure, such as the dynamic octree, can
      update the meshes (belonging to this model) to the proper node to ensure they are efficiently/properly
      culled during render.

      This method is invoked by any method in the Model class which manipulates Model::dispMatrix.
   */
   virtual void notifyWorldContainerOfAChangeInOrientation();
};

} //namespace Aftr

