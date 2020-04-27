#pragma once
#include <string>
#include <tuple>
#include "Vector.h"

namespace Aftr
{

class WO;
class ModelMesh;

class SelectionQueryResult
{
public:
   SelectionQueryResult() = default;
   ~SelectionQueryResult() = default;

   /// Call this method to automatically set internal variables to null and free last selected coordinate.
   /// This prepares this result for a new render selection query to be performed and get populated with
   /// the latest results.
   void resetState();

   std::string toString() const;

   /**
      When the user crtl-clicks an object in the world, selection is enabled. If the user clicked on a WO or any child WO,
      this variable shall be set to point at the selected WO. For example, if the user clicks on the human's lower arm,
      this variable points at the human's lower arm. If the user only want the top most parent; ie, the pointer to the human,
      the user can simply call the wo->getParentWO() until nullptr is returned. At this point, the parent is selected.

      The lastSelectedWorldObject is owned and deleted by GLView. Therefore the user shall never need to call delete lastSelectedWorldObject.
   */
   WO* lastSelectedWO = nullptr;

   /**
      After a selection of a World Object is completed, this points at the global coordinate
      in three space where the selection actually took place. The user NEVER owns this vector
      and shall never call delete on it.
   */
   Vector* getLastSelectedCoordinate() const;

   void setLastSelectedCoordinate( const Vector& vec );

   /**
      When the user crtl-clicks an object in the world, selection is enabled. If the user clicked on a WO that has a valid
      ModelDataShared containing a std::vector< ModelMesh* > meshes. The selected mesh will be populated here.
      For example, if the user clicks on the a car made of 15 meshes, and selects the mesh comprising the windshield, at
      meshes[idx], a this variable will be set to meshes[idx].

      The lastSelectedModelMesh is owned and deleted by GLView. Therefore the user shall never need to call delete lastSelectedModelMesh.
   */
   ModelMesh* lastSelectedModelMesh = nullptr;
   int lastSelectedModelMeshIdx = -1; //only valid when lastSelectedModelMesh is not nullptr, otherwise, this will be -1

   unsigned int x = 0, y = 0; ///< X,Y pixel of selection query

private:

   std::tuple< bool, Vector > lastSelectedCoordinate; //bool indicates if this variable holds a valid Vector. 
                                                      //If false, no Vector was found on most recent query.
                                                      //If true, Vector contains most recent query world space coordinate.

};

} //namespace Aftr
