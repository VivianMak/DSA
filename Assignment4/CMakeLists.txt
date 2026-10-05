cmake_minimum_required(VERSION 3.10)
project(Assignment4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


##### Build Libraries #####

# MyModule
add_library(mymodule_lib
    src/mymodule.cpp
)
target_include_directories(mymodule PUBLIC include)
# target_link_libraries(mymodule PUBLIC Eigen3::Eigen)


add_library(mymodule INTERFACE)
target_include_directories(mymodule INTERFACE include)

enable_testing()
add_subdirectory(tests)

# Main program executable
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE
    # link your libraries here, e.g.: mymodule
)
