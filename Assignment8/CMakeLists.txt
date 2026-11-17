cmake_minimum_required(VERSION 3.10)
project(Assignment8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to an optimized build so benchmark timings are realistic
# (override with -DCMAKE_BUILD_TYPE=Debug when debugging)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()


##### Build Libraries #####

# KD tree + quick select (header-only)
add_library(kdtree_lib INTERFACE)
target_include_directories(kdtree_lib INTERFACE include)

# enable_testing()
# add_subdirectory(tests)

# Main program executable
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE kdtree_lib)
