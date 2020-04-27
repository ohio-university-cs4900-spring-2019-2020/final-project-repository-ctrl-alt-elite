#pragma once

#ifdef STM_CONFIG_USE_GUICHAN

#include <list>

namespace gcn
{
   class Widget;
}

namespace Steamie
{

class GUIVisibilityStack
{
public:
   GUIVisibilityStack();
   virtual ~GUIVisibilityStack();
   gcn::Widget* top();
   void push(gcn::Widget* w);
   void pop();
   bool empty();
   size_t size();
   void clear();
protected:
   void purgeHidden();
   std::list<gcn::Widget*> myList;
};

}
#endif //STM_CONFIG_USE_GUICHAN
