#pragma once

#include "WOGUI.h"

namespace Aftr
{

class WOGUILabel;

class WOGUILabeledImage : public WOGUI
{
public:
   //static WOGUILabeledImage* New( float width, float height );
   static WOGUILabeledImage* New( WOGUI* parentWOGUI, WOGUILabel* label, WOGUI* image, std::string panelTex = std::string(""),
                                  std::string onPanelHasFocusTex = "",
                                  std::string onPanelSelectedTex = std::string(""), std::string onMouseDownTex = std::string("") );
   virtual ~WOGUILabeledImage();

   virtual void onResizeWindow( int newWidthInPixels, int newHeightInPixels );
   virtual WOGUI* getImage() { return this->image; }

protected:
   WOGUILabeledImage( WOGUI* parentWOGUI );
   //virtual void onCreate( float width, float height );
   virtual void onCreate( WOGUILabel* label, WOGUI* image, std::string panelTex = std::string(""), std::string onPanelHasFocusTex = "",
                          std::string onPanelSelectedTex = std::string(""), std::string onMouseDownTex = std::string("") );

   WOGUI* image; ///< Points to the image portion of this radio button (the radio dial)
};

} //namespace Aftr

