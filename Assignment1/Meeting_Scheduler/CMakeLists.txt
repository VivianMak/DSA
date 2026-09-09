cmake_minimum_required(VERSION 3.10)
project(Meeting_Scheduler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

##### Build Libraries #####

# Add one add_library() block per module, e.g.:
# add_library(mymodule
#     src/mymodule.cpp
# )
# target_include_directories(mymodule PUBLIC include)
# target_link_libraries(mymodule PUBLIC Eigen3::Eigen)

enable_testing()
add_subdirectory(tests)

# Main program executable
add_executable(main src/main.cpp)
target_link_libraries(main
    # link your libraries here, e.g.: mymodule
)
