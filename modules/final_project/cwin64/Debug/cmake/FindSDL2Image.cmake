#Written by SLN to find SDL2 Image library.
message( STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
                 "Inside of FindSDL2Image.cmake... Searching for SDL2 Image..." )

SET(SDL2IMAGE_SEARCH_PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
   /usr/local/include
	/usr
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
	${AFTR_3RD_PARTY_INCLUDE_ROOT}/SDL2_image-2.0.2
    ${AFTR_3RD_PARTY_INCLUDE_ROOT}/SDL2_image-2.0.0
)

FIND_PATH(SDL2Image_INCLUDE_DIR SDL_image.h
	HINTS
	$ENV{SDL2DIR}
	PATH_SUFFIXES SDL2 include
	PATHS ${SDL2IMAGE_SEARCH_PATHS}
)

FIND_LIBRARY(SDL2Image_LIBRARY
	NAMES SDL2_image
	HINTS
	$ENV{SDL2DIR}
	PATH_SUFFIXES lib64 lib
	PATHS ${SDL2IMAGE_SEARCH_PATHS}
   ${AFTR_3RD_PARTY_INCLUDE_ROOT}/../lib${AFTR_NBITS}
	DOC "SDL2 image Library Path"
)

FIND_LIBRARY( SDL2Image_LIBRARY_DEBUG
	NAMES SDL2_image_debug SDL2_imaged
	HINTS
	$ENV{SDL2DIR}
	PATH_SUFFIXES lib64 lib
	PATHS ${SDL2IMAGE_SEARCH_PATHS}
   ${AFTR_3RD_PARTY_INCLUDE_ROOT}/../lib${AFTR_NBITS}
	DOC "SDL2 image Library Path"
)


if( NOT SDL2Image_LIBRARY_DEBUG )
   set( SDL2Image_LIBRARY_DEBUG "${SDL2Image_LIBRARY}" CACHE PATH "" FORCE ) #Library Debug is NOT found, so just point at release
   set( SDL2Image_LIBRARIES ${SDL2Image_LIBRARY} )
endif()

set( SDL2Image_LIBRARIES
      optimized ${SDL2Image_LIBRARY}
          debug ${SDL2Image_LIBRARY_DEBUG}
   )

#MESSAGE( "SDL2Image_LIBRARY: ${SDL2Image_LIBRARY}..." )
#MESSAGE( "SDL2Image_LIBRARY_DEBUG: ${SDL2Image_LIBRARY_DEBUG}..."  )

INCLUDE( FindPackageHandleStandardArgs )

message( STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
                " Located SDL2Image_LIBRARY at: ${SDL2Image_LIBRARY}" )

FIND_PACKAGE_HANDLE_STANDARD_ARGS( SDL2_Image REQUIRED_VARS SDL2Image_LIBRARY SDL2Image_INCLUDE_DIR )

SET(SDL2Image_FOUND "NO")
IF(SDL2Image_LIBRARY AND SDL2Image_INCLUDE_DIR)
  SET(SDL2Image_FOUND "YES")
ENDIF()