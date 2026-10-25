cmake_minimum_required(VERSION 3.10)
project(Assignment5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##### Build Libraries #####

# MyModule
add_library(matrix_lib INTERFACE)
target_include_directories(matrix_lib INTERFACE include)

add_library(nw_lib STATIC src/needleman_wunsch.cpp)
target_link_libraries(nw_lib PUBLIC matrix_lib)   # header includes matrix.hpp, so pass it on


enable_testing()
add_subdirectory(tests)

# Main program executable
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE nw_lib)   # matrix_lib comes along transitively

# Benchmark executable
add_executable(benchmark src/benchmark.cpp)
target_link_libraries(benchmark PRIVATE matrix_lib)
