#pragma once

#include "SteamieConfig.h"
#ifdef STM_CONFIG_USE_GUICHAN

#include "guichan.hpp"
#include <vector>

namespace Steamie
{

class GUIListModelSteamie : public gcn::ListModel
{
  public:
    GUIListModelSteamie() {}
    GUIListModelSteamie( const std::vector< std::string >& strings );
    virtual ~GUIListModelSteamie() {}
    virtual std::string getElementAt(int i);
    virtual int getNumberOfElements();
protected:
   std::vector<std::string> strings;
};

}

#endif
