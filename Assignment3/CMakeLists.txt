cmake_minimum_required(VERSION 3.10)
project(Assignment3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##### Build Libraries #####

add_library(graph_lib INTERFACE)
target_include_directories(graph_lib INTERFACE include)

add_library(heap_lib INTERFACE)
target_include_directories(heap_lib INTERFACE include)

enable_testing()
add_subdirectory(tests)

# Main program executable
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE
    graph_lib
    heap_lib
)