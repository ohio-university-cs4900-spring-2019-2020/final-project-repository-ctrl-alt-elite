#pragma once

#include "SteamieConfig.h"
#ifdef STM_CONFIG_USE_GUICHAN

#include "guichan.hpp"
#include "guichan/opengl/openglsdlimageloader.hpp"

namespace Steamie
{

class GUIQuestionSetSelector : public gcn::Window
{
public:
   GUIQuestionSetSelector(gcn::ActionListener* al);
	virtual ~GUIQuestionSetSelector();
   std::string get_selected_qset();
private:
   gcn::DropDown *lb;
   gcn::Button* but;
};

}

#endif
