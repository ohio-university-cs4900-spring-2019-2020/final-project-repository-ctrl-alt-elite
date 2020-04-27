#pragma once

#include "MGL.h"

namespace Aftr
{
   class IndexedGeometry;

   class MGLIndexedGeometry : public MGL
   {
   public:
      static MGLIndexedGeometry* New( WO* parent );
      virtual ~MGLIndexedGeometry();
      virtual void render( const Camera& cam );
      virtual void renderSelection( const Camera& cam, GLubyte red, GLubyte green, GLubyte blue );
      virtual void setIndexedGeometry( IndexedGeometry* geom, bool deleteExistingGeomIfNotNull = true );
      virtual IndexedGeometry* getIndexedGeometry() { return this->geom; }

      /// Returns a pointer to a list containing all verticies within this model.
      /// This list is indexed by the corresponding CompositeIndexList.
      virtual const std::vector< Vector >& getCompositeVertexList() const override;

      /// Returns a pointer to a list containing all indicies into the corresponding
      /// CompositeVertexList.
      virtual const std::vector< unsigned int >& getCompositeIndexList() const override;

      /**
         Same as getModel(), but is templated so the user does not need to perform
         a static_cast<T> on the return type. This is simply a convenience method.
      */
      template< typename T, typename R = std::remove_pointer_t<T> > R* getIndexedGeometryT()
      {
         assert( this->geom != nullptr );
         if constexpr( std::is_pointer_v<T> )
            return static_cast<R*>(this->geom);//Lets mgl->getModelT<MGLQuad*>() work as expected.
         return static_cast<R*>(this->geom);   //Lets mgl->getModelT<MGLQuad>() work as expected.
      }

   protected:
      MGLIndexedGeometry( WO* parent );
      virtual void onCreate();

      IndexedGeometry* geom = nullptr;
   };

}

