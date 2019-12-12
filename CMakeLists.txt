CMAKE_MINIMUM_REQUIRED (VERSION 3.15 )
# project setting
PROJECT ( Doom-Engine)
SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR} )

# C++ settings
SET(CMAKE_CXX_STANDARD 11)

# loading SDL2 package 
FIND_PACKAGE(SDL2 REQUIRED)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS}) 

# set source and headers
SET (SRC_FILES
    src/main.cpp 
    src/pch.cpp
    )
INCLUDE_DIRECTORIES( include ./include )

# build 
ADD_EXECUTABLE( Doom-Engine ${SRC_FILES} )
TARGET_LINK_LIBRARIES(Doom-Engine ${SDL2_LIBRARIES})
