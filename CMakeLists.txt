CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)

SET(proj_name Doom-Engine)
PROJECT( ${proj_name} )

# C++ settings
SET(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(extern/googletest)

add_dependencies(${CMAKE_PROJECT_NAME}_tst ${CMAKE_PROJECT_NAME}_lib )