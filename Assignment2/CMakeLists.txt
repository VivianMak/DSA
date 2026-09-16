cmake_minimum_required(VERSION 3.10)
project(Assignment2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##### Build Libraries #####

# DoublyLinkedList
add_library(DoublyLinkedList_lib INTERFACE)
target_include_directories(DoublyLinkedList_lib INTERFACE include)

# Stack and Queue structs
add_library(structs_lib INTERFACE)
target_include_directories(structs_lib INTERFACE include)

# enable_testing()
# add_subdirectory(tests)

# Main program executable
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE
    DoublyLinkedList_lib
    structs_lib
)
