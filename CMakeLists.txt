cmake_minimum_required(VERSION 3.10.2)

set(proj_name Doom-Engine)
project( ${proj_name}   VERSION 0.1
                        DESCRIPTION "Make Own 3D Engine"
                        LANGUAGES CXX 
)

# C++ settings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(extern/googletest)
