cmake_minimum_required(VERSION 3.10)


project(clipperplus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include_directories(include/)

file(GLOB SOURCES "src/*.cpp")


list(APPEND SOURCES "src/pmc.cpp" "src/clipper.cpp")



find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})


set(SOURCES
    src/clipper.cpp
    src/pmc.cpp
)


add_executable(clipperplus clipperplus.cpp src/pmc.cpp src/clipper.cpp)
