//*****************************************************
//
// File: StaticShapelssModel
//
// This class inherits the Model class, but it is a 
// virtual and stripped down class. It doesn't use 
// any vrml, this eliminates out the use of the model face
// and model shape classes as well. This model class uses the 
// translates, rotates, ect built into it. 
//
// To use physics with any of these openGL models, you MUST
// define the bounding box surrounding each model yourself
// so if you want multiple objects with each their own collisions
// you have to create a class for each with their own specific
// Bounding boxes. You can attach this model to a WO,
// but the mass and bounding box must be set. If you don't want
// any interaction with this object you need to attach it with
// a WO or a class that inherits WO
// 
//*********************************************************

#pragma once

#include "Model.h"
#include "AftrOpenGLIncludes.h"
#include "ModelMeshSkin.h"

namespace Aftr
{
class WO;
class Texture;
class Camera;

class MGL : public Model
{
public:

   MGL( WO* parentWO );

   virtual ~MGL();

   /*purely virtual render functions, which are necessary to draw just a sphere to represent a vertex instead of a model
      these MUST be overridden in the child class if you want to create a openGL model that you create by drawing yourself*/
   virtual void render( const Camera& cam ) override = 0;
   virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue ) override;

   /**
      This function allows you to specify the lx,ly,lz of the bounding box of the object.
   */
   virtual void setBoundingBox( const Vector& lxlylz );
   virtual bool isInViewingFrustum( const AftrGeometryFrustum& viewportFrustum ) override { return true; }

   virtual BoundingBox& getBoundingBox() override;
   virtual const BoundingBox& getBoundingBox() const override;

   /// Returns a pointer to a list containing all verticies within this model.
   /// This list is indexed by the corresponding CompositeIndexList.
   virtual const std::vector< Vector >& getCompositeVertexList() const override;

   /// Returns a pointer to a list containing all indicies into the corresponding
   /// CompositeVertexList.
   virtual const std::vector< unsigned int >& getCompositeIndexList() const override;

   /**
      Convenience methods that can be used by MGL so each MGL doesn't necessarily
      need to use a ModelDataShared instance and all corresponding classes such as
      skins, ModelMeshs, ModelMeshDataShared, ModelMeshRenderDataGenerator, etc.

      These are virtual methods overloaded from the base Model class and have been
      implemented to suit MGLs and MGL subclasses that do not necessarily have
      ModelMeshes and ModelDataShared instances.
   */
   virtual ModelMeshSkin& getSkin( size_t modelMeshIdx = 0 ) override;
   virtual std::vector< ModelMeshSkin >& getSkins( size_t modelMeshIdx = 0 ) override;

   //virtual void addSkin( const ModelMeshSkin& skin ) override; //creates a copy of the in passed skin, be careful that the original may destroy shared texture resources when its destructor is called. Avoid this by using the addSkin( ModelMeshSkin&& ). IE,  m.addSkin( std::move( theSkin ) ) method.
   virtual void addSkin( ModelMeshSkin&& skinToOwn, size_t modelMeshIdx = 0 ) override; //moves the in passed skin into this MGL's skin list
   virtual void addSkin( const std::string& pathToTexture, size_t modelMeshIdx = 0 ) override; ///< Creates a Skin using the texture passed in
   virtual void addSkin( Texture* texThisMGLTakesOwnership, size_t modelMeshIdx = 0 ) override; ///< Creates a Skin using the texture. This MGL takes ownwership of the in passed texture
   virtual void useNextSkin( size_t modelMeshIdx = 0 ) override;
   virtual void usePreviousSkin( size_t modelMeshIdx = 0 ) override;
   virtual void useSkinAtIndex( size_t skinIndex, size_t modelMeshIdx = 0 ) override;
   virtual size_t getSkinIndex( size_t modelMeshIdx = 0 ) override { return skinIndex; }

protected:

   BoundingBox mglBBox;

   std::vector< ModelMeshSkin > skins;
   size_t skinIndex = 0;


   std::vector< Vector > compositeVertexList;
   std::vector< unsigned int > compositeIndexList;

   GLenum VBOIndicesMemoryType;
   GLuint VBOVertexListInterleavedData = 0;
   
   VertexListEntry* vertexList = nullptr;

   unsigned int indexListSize  = 0;//strictly positive, consider switching to size_t (since it has size in the name?)
   unsigned int vertexListSize = 0;//see above
   GLvoid* indexList = nullptr;
};

}  //namespace Aftr
