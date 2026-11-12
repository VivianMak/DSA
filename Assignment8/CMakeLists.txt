cmake_minimum_required(VERSION 3.10)
project(Assignment8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##### Build Libraries #####

# KD tree + quick select (header-only)
add_library(kdtree_lib INTERFACE)
target_include_directories(kdtree_lib INTERFACE include)

# enable_testing()
# add_subdirectory(tests)

# Main program executable
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE kdtree_lib)
