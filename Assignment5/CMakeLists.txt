cmake_minimum_required(VERSION 3.10)
project(Assignment5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##### Build Libraries #####

# MyModule
add_library(matrix_lib INTERFACE)
target_include_directories(matrix_lib INTERFACE include)


enable_testing()
add_subdirectory(tests)

# Main program executable
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE matrix_lib)

# Benchmark executable
add_executable(benchmark src/benchmark.cpp)
target_link_libraries(benchmark PRIVATE matrix_lib)
