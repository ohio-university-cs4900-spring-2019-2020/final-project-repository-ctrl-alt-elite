# Locate SDL2 library
# This module defines
# SDL2_LIBRARY, the name of the library to link against
# SDL2_FOUND, if false, do not try to link to SDL2
# SDL2_INCLUDE_DIR, where to find SDL.h
#
# This module responds to the the flag:
# SDL2_BUILDING_LIBRARY
# If this is defined, then no SDL2_main will be linked in because
# only applications need main().
# Otherwise, it is assumed you are building an application and this
# module will attempt to locate and set the the proper link flags
# as part of the returned SDL2_LIBRARY variable.
#
# Don't forget to include SDL2main.h and SDL2main.m your project for the
# OS X framework based version. (Other versions link to -lSDL2main which
# this module will try to find on your behalf.) Also for OS X, this
# module will automatically add the -framework Cocoa on your behalf.
#
#
# Additional Note: If you see an empty SDL2_LIBRARY_TEMP in your configuration
# and no SDL2_LIBRARY, it means CMake did not find your SDL2 library
# (SDL2.dll, libsdl2.so, SDL2.framework, etc).
# Set SDL2_LIBRARY_TEMP to point to your SDL2 library, and configure again.
# Similarly, if you see an empty SDL2MAIN_LIBRARY, you should set this value
# as appropriate. These values are used to generate the final SDL2_LIBRARY
# variable, but when these values are unset, SDL2_LIBRARY does not get created.
#
#
# $SDL2DIR is an environment variable that would
# correspond to the ./configure --prefix=$SDL2DIR
# used in building SDL2.
# l.e.galup  9-20-02
#
# Modified by Eric Wing.
# Added code to assist with automated building by using environmental variables
# and providing a more controlled/consistent search behavior.
# Added new modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).
# Also corrected the header search path to follow "proper" SDL2 guidelines.
# Added a search for SDL2main which is needed by some platforms.
# Added a search for threads which is needed by some platforms.
# Added needed compile switches for MinGW.
#
# On OSX, this will prefer the Framework version (if found) over others.
# People will have to manually change the cache values of
# SDL2_LIBRARY to override this selection or set the CMake environment
# CMAKE_INCLUDE_PATH to modify the search paths.
#
# Note that the header path has changed from SDL2/SDL.h to just SDL.h
# This needed to change because "proper" SDL2 convention
# is #include "SDL.h", not <SDL2/SDL.h>. This is done for portability
# reasons because not all systems place things in SDL2/ (see FreeBSD).
#
# Ported by Johnny Patterson. This is a literal port for SDL2 of the FindSDL.cmake
# module with the minor edit of changing "SDL" to "SDL2" where necessary. This
# was not created for redistribution, and exists temporarily pending official
# SDL2 CMake modules.

#=============================================================================
# Copyright 2003-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

MESSAGE( STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
                 "Inside of FindSDL2.cmake... Searching for SDL2..." )
#MESSAGE( "PATH IS ${AFTR_3RD_PARTY_INCLUDE_ROOT}/../lib${AFTR_NBITS}" )
#get_property( test GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS )
#MESSAGE( "FIND_LIBRARY_USE_LIB64_PATHS is ${test}" )
#MESSAGE( "CMAKE_PREFIX_PATH  is ${CMAKE_PREFIX_PATH}" )
                 
FIND_PATH(SDL2_INCLUDE_DIR SDL.h
   HINTS
   $ENV{SDL2DIR}
   PATH_SUFFIXES include/SDL2 include
   PATHS
   ~/Library/Frameworks
   /Library/Frameworks
   /usr/local/include/SDL2
   /usr/include/SDL2
   /sw # Fink
   /opt/local # DarwinPorts
   /opt/csw # Blastwave
   /opt
   ${AFTR_3RD_PARTY_INCLUDE_ROOT}/SDL2-2.0.7
   ${AFTR_3RD_PARTY_INCLUDE_ROOT}/SDL2-2.0.5
   ${AFTR_3RD_PARTY_INCLUDE_ROOT}/SDL2-2.0.3
)

FIND_LIBRARY( SDL2_LIBRARY_TEMP
   NAMES SDL2 
   HINTS   
   $ENV{SDL2DIR}
   PATH_SUFFIXES lib64 lib32 lib 
   PATHS
   /sw
   /opt/local
   /opt/csw
   /opt
   ${AFTR_3RD_PARTY_INCLUDE_ROOT}/../lib${AFTR_NBITS}
)

FIND_LIBRARY( SDL2_LIBRARY_DEBUG_TEMP
   NAMES SDL2_debug
   HINTS
   $ENV{SDL2DIR}
   PATH_SUFFIXES lib64 lib32 lib
   PATHS
   /sw
   /opt/local
   /opt/csw
   /opt
   ${AFTR_3RD_PARTY_INCLUDE_ROOT}/../lib${AFTR_NBITS}
)

#MESSAGE( "FindSDL2.cmake thinks that AFTR_NBITS is ${AFTR_NBITS}." )
#MESSAGE( "The lib path should include: ${AFTR_3RD_PARTY_INCLUDE_ROOT}/../lib${AFTR_NBITS}" )
#MESSAGE( "SDL2_LIBRARY_TEMP is ${SDL2_LIBRARY_TEMP}" )
#MESSAGE( "SDL2_LIBRARY_DEBUG_TEMP is ${SDL2_LIBRARY_DEBUG_TEMP}" )

IF( NOT SDL2_BUILDING_LIBRARY )
   IF( NOT ${SDL2_INCLUDE_DIR} MATCHES ".framework" )
   # Non-OS X framework versions expect you to also dynamically link to
   # SDL2main. This is mainly for Windows and OS X. Other (Unix) platforms
   # seem to provide SDL2main for compatibility even though they don't
   # necessarily need it.
   FIND_LIBRARY( SDL2MAIN_LIBRARY
      NAMES SDL2main
      HINTS
      $ENV{SDL2DIR}
      PATH_SUFFIXES lib64 lib
      PATHS
      /sw
      /opt/local
      /opt/csw
      /opt
      ${AFTR_3RD_PARTY_INCLUDE_ROOT}/../lib${AFTR_NBITS}
    )
    
   FIND_LIBRARY( SDL2MAIN_LIBRARY_DEBUG
      NAMES SDL2main_debug
      HINTS
      $ENV{SDL2DIR}
      PATH_SUFFIXES lib64 lib
      PATHS
      /sw
      /opt/local
      /opt/csw
      /opt
      ${AFTR_3RD_PARTY_INCLUDE_ROOT}/../lib${AFTR_NBITS}
    )
  ENDIF()
ENDIF()

# SDL2 may require threads on your system.
# The Apple build may not need an explicit flag because one of the
# frameworks may already provide it.
# But for non-OSX systems, I will use the CMake Threads package.
IF(NOT APPLE)
   FIND_PACKAGE(Threads)
ENDIF()

# MinGW needs an additional library, mwindows
# It's total link flags should look like -lmingw32 -lSDL2main -lSDL2 -lmwindows
# (Actually on second look, I think it only needs one of the m* libraries.)
IF(MINGW)
  SET(MINGW32_LIBRARY mingw32 CACHE STRING "mwindows for MinGW")
ENDIF()

SET( SDL2_FOUND "NO" )
IF( SDL2_LIBRARY_TEMP )
   IF( NOT SDL2_BUILDING_LIBRARY ) # For SDL2main
      IF( SDL2MAIN_LIBRARY )
         SET( SDL2_LIBRARY_TEMP ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY_TEMP} )
      ENDIF()
   ENDIF()
   
   IF( NOT SDL2MAIN_LIBRARY_DEBUG )
      set( SDL2MAIN_LIBRARY_DEBUG "${SDL2MAIN_LIBRARY}" CACHE PATH "" FORCE ) #Set debug SDL2MAIN to release if debug isn't found
   endif()
  
   IF( SDL2_LIBRARY_DEBUG_TEMP )
      IF( SDL2MAIN_LIBRARY_DEBUG )
         SET( SDL2_LIBRARY_DEBUG_TEMP ${SDL2MAIN_LIBRARY_DEBUG} ${SDL2_LIBRARY_DEBUG_TEMP} )
      ENDIF()
   ENDIF()

  # For OS X, SDL2 uses Cocoa as a backend so it must link to Cocoa.
  # CMake doesn't display the -framework Cocoa string in the UI even
  # though it actually is there if I modify a pre-used variable.
  # I think it has something to do with the CACHE STRING.
  # So I use a temporary variable until the end so I can set the
  # "real" variable in one-shot.
  IF( APPLE )
    SET( SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} "-framework Cocoa" )
  ENDIF()

  # For threads, as mentioned Apple doesn't need this.
  # In fact, there seems to be a problem if I used the Threads package
  # and try using this line, so I'm just skipping it entirely for OS X.
  IF( NOT APPLE )
      SET( SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT} )
  ENDIF()

   # For MinGW library
   IF( MINGW )
      SET( SDL2_LIBRARY_TEMP ${MINGW32_LIBRARY} ${SDL2_LIBRARY_TEMP} )
   ENDIF()

   # Set the final string here so the GUI reflects the final state.
   SET(SDL2_LIBRARY ${SDL2_LIBRARY_TEMP} CACHE STRING "Where the SDL2 Library can be found")
   # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
   #SET(SDL2_LIBRARY_TEMP "${SDL2_LIBRARY_TEMP}" CACHE INTERNAL "")
  
  #Ensure Debug Libs are setup, if found
   IF( SDL2_LIBRARY_DEBUG_TEMP )
      SET( SDL2_LIBRARY_DEBUG ${SDL2_LIBRARY_DEBUG_TEMP} CACHE STRING "Where SDL2 Debug Lib is located" )
   ELSE()
      SET( SDL2_LIBRARY_DEBUG ${SDL2_LIBRARY_TEMP} CACHE STRING "Where SDL2 Debug Lib is located" )
   ENDIF()
   
   
   SET( SDL2_LIBRARY_DEBUG_TEMP ${SDL2_LIBRARY_DEBUG_TEMP} CACHE INTERNAL "" )
   SET( SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} CACHE INTERNAL "" )

   SET( SDL2_FOUND "YES" )
ENDIF()


#set( SDL2_LIBRARIES
#      optimized ${SDL2_LIBRARY}
#      optimized ${SDL2MAIN_LIBRARY}
#          debug ${SDL2_LIBRARY_DEBUG}
#          debug ${SDL2MAIN_LIBRARY_DEBUG}
#   )

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2 REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR)
