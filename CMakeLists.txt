CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

SET(proj_name Doom-Engine)
PROJECT( ${proj_name} )

# C++ settings
SET(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(extern/googletest)
