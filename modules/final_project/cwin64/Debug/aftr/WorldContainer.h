#pragma once

#include <cstddef>
#include <vector>
#include "WO.h"
#include "WOGUI.h"
#include "WOGUIRoot.h"

namespace Aftr
{

class Camera;

class WorldContainer
{
public:
   WorldContainer();
   virtual ~WorldContainer();

   /**
      Called by GLView::render( const Camera& cam ) immediately before WorldContainer::renderWorld() is invoked.
      This method is responsible for preparing the scene based on the current camera/frustum
      info. The subclass will perform common operations like transparency sorting, 
      frustum culling. After this method completes, the renderWorld() method will have all
      necessary information to render the scene efficiently.
   */
   virtual void update( const Camera& cam ) = 0;

   ///returns the size of the world list
   virtual size_t size() const;
   virtual size_t sizeGUIList() const;
   //virtual size_t max_size() const;
   //virtual void resize( size_t newSize );
   //virtual size_t capacity() const;
   //virtual bool empty() const;
   //virtual void reserve( size_t n );

   ///returns the WO* at position i in the current incarnation of the world list
   virtual WO* at( size_t i ) const;
   std::vector<WO*>::iterator at_iter( size_t i );

   /// Searches the top level worldList for the in passed WO*. If found, its index is
   /// returned; if not found, -1 is returned.
   virtual int getIndexOfWO( WO* wo );

   /// Searches the top level worldList and recurses down the contains of all children
   /// for the in passed WO*. If found, its index is returned; if not found, -1 is returned.
   virtual int getIndexOfWORecursive( WO* wo );

   /**
      returns the WOGUI* at position i in the current incarnation of the gui list.
      The gui list is a sublist maintained within this WorldContainer (WOGUIs).
   */
   virtual WOGUI* atGUIList( size_t i ) const;

   virtual WOGUIRoot* getWOGUIRoot() const;

   /**
      Returns the index of the in passed widget. This index corresponds to the value used
      in atGUIList( size_t i ). Returns -1, if widget is not found.
   */
   virtual int getIndexOfWidgetInGUIList( WOGUI* widget );

   /**
      Returns the WOGUI* at pixel x,y. The ordering is identical to renderGUISelection, 
      but costs less than a double render. If no WOGUI* is at that pixel, NULL is 
      returned.
   */
   virtual WOGUI* getWOGUIAtPixel( unsigned int x, unsigned int y );

   /**
      \param wo The WO to add to the world lists.
      Add wo to the world list.
   */
   virtual void push_back( WO* wo );

   /**
      Removes WO* wo from the container. The wo is NOT deleted, it is just removed.
      Any WOs after this are shuffled down so no empty gap remains in the list.
   */
   virtual bool eraseViaWOptr( WO* wo );

   /**
      Removes WO* wo from the container at index. The wo is NOT deleted, it is just removed.
      Any WOs after this are shuffled down so no empty gap remains in the list.
   */
   virtual bool eraseViaWOIndex( size_t index );
   
   /**
      Clears the world list.
   */
   virtual void clear();
   
   ///toggles the bounding box of every object in the world list
   virtual void toggleBBox();

   ///toggles the bounding box of each ModelMesh within each model
   virtual void toggleModelMeshBBox();

   ///returns the current incarnation of the list of all World Objects
   //std::vector<WO*>* getListPtr() { return &this->woList; }
   //std::vector<WO*>& getListRef(){ return this->woList; }

   ///returns the total face count of every object in the list
   int worldFaceCount();
   void inspectForNullModel();

   virtual void renderWorld( const Camera& cam ) = 0;
   virtual void renderGUI( const Camera& cam );
   virtual void renderSelf( const Camera& cam ); ///< Used to visualize the WorldContainer, if applicable (ie, Octree visualization)

   virtual void renderWorldSelection( const Camera& cam );
   virtual void renderGUISelection();

   virtual std::string toString(); ///< Returns a string containing current info about the WorldContainer instance.

   virtual std::string toStringWOGUI(); ///< Returns a string listing the WOGUI WOs

   /**
      Returns true if the in passed WO* is a top-level WO; that is, if it is a WO* inserted into
      the WorldContainer that has no parent WO*. Otherwise, false is returned.
   */
   virtual bool isATopLevelWO( const WO* woToSearchFor );

   /**
      When a Model changes its position, it notifies the WorldContainer instance. This is
      used by the WorldContainer subclasses, such as the WorldOctree, to identify when a mesh may have
      changed which node it resides in. This notification is used when the WorldContainer::update(...)
      method is invoked (immediately before WorldContainer::render( const Camera& cam ) is invoked).
      When invoked, the WorldContainer acceleration structure, such as the dynamic octree, can
      update the meshes (belonging to this model) to the proper node to ensure they are efficiely/properly
      culled during render.

      This method is invoked by any method in the Model class which manipulates Model::translateAmt.

      The default behavior ignores this callback; however, decendents of WorldContainer may overload this
      to update internal data structures.
   */
   virtual void onModelChangeInPosition( Model* m ) {}

   /**
      When a Model changes its orientation, it notifies the WorldContainer instance. This is
      used by the WorldContainer subclasses, such as the WorldOctree, to identify when a mesh may have
      changed which node it resides in. This notification is used when the WorldContainer::update(...)
      method is invoked (immediately before WorldContainer::render( const Camera& cam ) is invoked).
      When invoked, the WorldContainer acceleration structure, such as the dynamic octree, can
      update the meshes (belonging to this model) to the proper node to ensure they are efficiely/properly
      culled during render.

      This method is invoked by any method in the Model class which manipulates Model::dispMatrix.

      The default behavior ignores this callback; however, decendents of WorldContainer may overload this
      to update internal data structures.
   */
   virtual void onModelChangeInOrientation( Model* m ) {}

   virtual void onWORemovedFromContainer( WO* wo ) {}

   virtual void onChildWOInsertedInATopLevelWO( WO* newlyInsertedchild, WO* topLevelWO ) {}

   /**
      if true, this WorldContainer will invoke WorldContainer::renderSelf() at the
      end of its invokation of WorldContianer::renderWorld().
      For example, if this WorldContain is an Octree, the octree's nodes 
      will be rendered. If the WorldContainer has not overloaded its renderSelf()
      method, no additional rendering occurs.
   */
   bool isVisible;

   /**
     Returns the WO with the given id, or NULL if no WO such WO exists.  
     Implementation in base class is O(n), but easily made O(lg n) by adding a map if the container size gets large enough
   */
   virtual WO* getWOByID( unsigned int id );

protected:

   bool eraseViaWOGUIptr( WOGUI* wo );

   /**
      \param The object whose bounding box should be toggled.
      Toggles the bounding box of an object.
   */
   void toggleBBox( WO* wo );
   void toggleModelMeshBBox( WO* wo );
   

   std::vector< WO* > woList; ///< List of WOs inside the current world (excluding WOGUI objects)
   
   /**
      List of all WOs implementing the IFaceGUI which are rendered as GUI objects.
      These are strictly hierachical. Each WOGUI in this list may contain children WOGUI's;
      only top level WOGUI objects may be in this list.
   */
   WOGUIRoot* rootGUI = nullptr;
   //std::vector< WOGUI* > guiList;

};


} //namespace Aftr

