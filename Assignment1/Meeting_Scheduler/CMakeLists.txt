cmake_minimum_required(VERSION 3.10)
project(Meeting_Scheduler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##### Build Libraries #####

add_library(simple_scheduler_lib
    src/simple_scheduler.cpp
)
target_include_directories(simple_scheduler_lib PUBLIC include)

add_library(sorted_scheduler_lib
    src/sorted_scheduler.cpp
)
target_include_directories(sorted_scheduler_lib PUBLIC include)

##### Build Executables #####

add_executable(simple_scheduler
    src/simple_main.cpp
)
target_link_libraries(simple_scheduler PRIVATE simple_scheduler_lib)

add_executable(sorted_scheduler
    src/sorted_main.cpp
)
target_link_libraries(sorted_scheduler PRIVATE sorted_scheduler_lib)

##### Testing #####

enable_testing()
add_subdirectory(tests)
