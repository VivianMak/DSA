cmake_minimum_required(VERSION 3.10)
project(Meeting_Scheduler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##### Build Libraries #####

add_library(scheduler_lib
    src/scheduler.cpp
)
target_include_directories(scheduler_lib PUBLIC include)


##### Build Executables #####

add_executable(main
    src/main.cpp
)
target_link_libraries(main PRIVATE scheduler_lib)

##### Testing #####

enable_testing()
add_subdirectory(tests)
