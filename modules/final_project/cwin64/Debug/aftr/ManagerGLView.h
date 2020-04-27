#pragma once
#include <cassert>

namespace Aftr
{

class GLView;

class ManagerGLView
{
public:
   static void init( GLView* currentGLView );

   template< typename T = GLView >
   static T* getGLView()
   {
      return ManagerGLView::getGLViewT<T>();
   }
   
   /// This method is similar to getGLView() but it explicitly casts the return type to the GLView subclass passed inside
   /// of the template parameter.
   template< typename T >
   static T* getGLViewT()
   {
      assert( ManagerGLView::glView != nullptr );
      return static_cast<T*>( ManagerGLView::glView );
   }
protected:
   static GLView* glView;
};

} //namespace Aftr

