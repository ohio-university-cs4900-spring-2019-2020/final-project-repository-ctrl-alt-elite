#pragma once

#ifdef STM_CONFIG_USE_GUICHAN

#include "guichan.hpp"
#include "ManagerFileBrowser.h"
#include "GUIBox.h"

#include <string>
#include <vector>

namespace Steamie
{

/**
   \class FBListModel
   \author Mitchell Leitch - derived from NyklListModel
   \brief an expanded upon gcn::ListModel with more functionality for adding and removing items from the list model
   \{
   */
class FBListModel : public gcn::ListModel
{
public:

   FBListModel() : gcn::ListModel()
   {
      list.clear();
   }

   ~FBListModel()
   {
   }

   void insert( std::string str )
   {
      list.push_back( str );
   }

   void clear() { list.clear(); }

	int getNumberOfElements()
	{
      return (int) list.size();
	}

	std::string getElementAt(int i)
	{
      if( i >=0 && i < (int)list.size() )
         return list.at(i);
      else
         return NULL;
	}

   /**clears out the list model, and then fills it with the updated directory info struct passed in*/
   void updateListModel( struct DirectoryInformation dirInfo)
   {
      clear();
      //populating the original file browser to start at the working directory ( can make it any directory just easier to start in the working directory )
      for (unsigned int i = 0; i < dirInfo.numOfDirs; ++i)
      {
         //adding a directory
         insert( dirInfo.dirName[i] );
      }
      for (unsigned int i = 0; i < dirInfo.numOfFiles; ++i )
      {
         //adding the files
         insert( dirInfo.fileName[i] );
      }
   }
   std::vector< std::string > list;

protected:
      std::vector < gcn::Icon* > icons;
};

/** \} */

/** 
   \class FBListBox
   \author Mitchell Leitch
   \brief A inherited ListBox class specific to the file browser.
   The major differences are the addition of the directory info struct, and the getListModel function returns a
   FBListModel instead of a gcn::ListModel
   \{
   */
class FBListBox : public gcn::ListBox, public gcn::ActionListener
{
   friend class GUIFileBrowser;

public:
   
   FBListBox( FBListModel* lModel ) : gcn::ListBox( lModel ), gcn::ActionListener() 
   {
      ManagerFileBrowser::initDirectoryInformation( dirInfo );
      update();
   }
   
   virtual ~FBListBox();

   /**accessor for the FBListModel*/
   FBListModel* getFBListModel() { return ((FBListModel*) getListModel()); } 

   /**accessor function for the directory information*/
   struct DirectoryInformation getDirInfo() { return dirInfo; }

   /**updates the list model and the list box so that everything will be properly drawn*/
   void update();

   virtual void draw(gcn::Graphics* graphics);

   virtual void action( const std::string& eventId, gcn::Widget* widget );

protected:

   /**the directory information related to this gui file browser pertaining to the current directory.*/
   struct DirectoryInformation dirInfo;
   std::vector < gcn::Image* > icons;

}; 

/** \} */


/**
   \class GUIFileBrowser
   \author Mitchell Leitch
   \brief a graphic user interface for browsing files on the local disk

   \{
   */
class GUIFileBrowser : public gcn::ActionListener, public GUIBox
{
   friend class FBListBox;

public:

   GUIFileBrowser( gcn::ImageFont* font );
   ~GUIFileBrowser();

   void action(const std::string& eventId, gcn::Widget* widget);

   /**Initializes the file browsers widgets*/
   void initWidgets();

   /**this should be called inside of your gui's action function when the filebrowser is the widget that had fired*/
   std::string getLastSelectedFile() { return selectedFile; }

   virtual void displayCurrentIndex();
protected:

   FBListBox* filesAndDirs;
   gcn::TextBox* TBCurrDir;
   gcn::Button* openBtn;
   gcn::Button* cancelBtn;
   gcn::Window* fileWindow;
   gcn::ScrollArea* scrollWin;
   std::string selectedFile;

};


/** \} */



} //namespace Steamie

#endif //STM_CONFIG_USE_GUICHAN
