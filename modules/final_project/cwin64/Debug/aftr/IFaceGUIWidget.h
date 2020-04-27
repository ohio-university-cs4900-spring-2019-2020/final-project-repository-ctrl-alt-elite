#pragma once

#include "IFace.h"
#include <vector>

namespace Aftr
{

class IFaceGUIWidget : public virtual IFace
{
public:
   IFaceGUIWidget( WO* woUsingThisInterface );
   virtual ~IFaceGUIWidget();

protected:
   static std::vector< IFaceGUIWidget* > IFaceGUIWidgetMemberList;


};

} //namespace Aftr

