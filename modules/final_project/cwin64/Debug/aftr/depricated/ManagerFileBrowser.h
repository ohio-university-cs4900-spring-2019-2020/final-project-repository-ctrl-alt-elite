#pragma once

#ifdef STM_CONFIG_USE_GUICHAN

#include <string>
#include <vector>

namespace Steamie
{

/**The working directory of this module*/
static std::string workingDirectory;

/**
   \struct directoryInformation
   \author Mitchell Leitch
   \brief A struct that describes the directory structure.
   File size will be 0 for directories.
   The indices of the vectors will correspond to the same file in all three vectors.
   The indices of the vectors are (numOfFiles + numOfDirs - 1).
   */
struct DirectoryInformation
{
public:

   std::string currDirectory;
   unsigned int numOfFiles;
   unsigned int numOfDirs;

   std::vector < std::string > dateLastModified;
   std::vector < std::string > fileSize;
   //only the files (not dirs)
   std::vector < std::string > fileName;
   //only the directories
   std::vector < std::string > dirName;
};

/**the working directory of this module*/


/**
   \class ManagerFileBrowser
   \author Mitchell Leitch
   \brief An interface into the file system. Currently Win32 only supported.
   This is a static class, there will be no instantiation. An interface into the file and folder system, 
   this will only handle the manipulation, it will not display any data or be a user interface. 
   There must be a user layer above this to work in (ie a gui).
   setWorkingDirectory() MUST be called at start of use of ManagerFileBrowser for proper functioning.
     * if glview::init is called this is taken care of
   \{
*/

   
class ManagerFileBrowser
{

public:

   /**gets the current working directory*/
   static std::string pwd();
   /**gets the current working directory*/
   static std::string printWorkingDirectory()   { return pwd(); }

   /**gets the contents of the directory passed in.
      if the string passed in is an empty string then it will get the contents of the current directory.
      This will list the folders first.
      \param DirectoryInformation& a struct which contains the information of the directory.*/
   static void ls( struct DirectoryInformation& dirInfo, std::string dir = "" );
   /**a copy of the ls function so people can identify with one or the other.
      * dir = windows based
      * ls = linux, mac      
      this is used for familiarity
      \param DirectoryInformation& a struct which contains the information of the directory.*/
   static void dir( struct DirectoryInformation& dirInfo, std::string dir = "" ) { return ls( dirInfo, dir ); }

   /**sets the working directory for the current module*/
   static void setWorkingDirectory() { workingDirectory = pwd(); }

   /**gets the working directory of this module*/
   static std::string getWorkingDirectory() { return workingDirectory; }

   /**converts the absolute path of the string absPath to a relative path that is relative to the path relativeTo.
      the default value of relativeTo is the current working directory, this will be the normal use of this function.*/
   static std::string convertAbsolutePathToRelative( std::string absPath, std::string relativeTo );
   
   /**converts the relative path to an absolute path based on the the absolute path given.
      the default value of absoluteTo is the current working directory, you will normally use it with the default*/
   static std::string convertRelativePathToAbsolute( std::string relPath, std::string absoluteTo );

   /**Changes the directory to the directory passed in.
      These can be either relative or absolute paths.
      The default value is empty string so cd will not do anything.*/
   static void cd( struct DirectoryInformation& dirInfo, std::string newDir = "" );

   /**initializes a directory information struct, this needs to be called when it is instantiated so it is pointing at the proper location*/
   static void initDirectoryInformation( struct DirectoryInformation& dirInfo );

   /**Cleans up the path passed so it is readable by the file system to get proper information back*/
   static std::string cleanUpPath( std::string path );

protected:

   /**Pulls apart the strings describing the files and puts them into a directoryInformation struct.
      _WIN32 expects the structure information to be in the format (Date Time, if it's a dir <DIR>, file size, file name.*/
   static void extractDirectoryInformation( struct DirectoryInformation& dirInfo, std::vector < std::string > files );

};


/** \} */

} //namespace Steamie

#endif //workingDirectory
