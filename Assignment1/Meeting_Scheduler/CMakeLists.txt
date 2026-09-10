cmake_minimum_required(VERSION 3.10)
project(Meeting_Scheduler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

##### Build Libraries #####

# enable_testing()
# add_subdirectory(tests)

# Main program executable
add_executable(simple_scheduler
    src/simple_scheduler.cpp
)
target_include_directories(simple_scheduler PUBLIC include)


# Main program executable
add_executable(sorted_scheduler 
    src/sorted_scheduler.cpp
)
target_include_directories(sorted_scheduler PUBLIC include)