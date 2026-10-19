cmake_minimum_required(VERSION 3.23)
project(Assignment4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##### Build Libraries #####

# MyModule
add_library(sort_lib
    src/sorting.cpp
)
target_include_directories(sort_lib PUBLIC include)

# add_library(mymodule INTERFACE)
# target_include_directories(mymodule INTERFACE include)

enable_testing()
add_subdirectory(tests)

# Main program executable
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE
    sort_lib
)

add_executable(benchmark src/benchmark.cpp)
target_link_libraries(benchmark PRIVATE sort_lib)