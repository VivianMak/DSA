cmake_minimum_required(VERSION 3.10)
project(KalmanFilter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

##### Build Libraries #####

# Library: kf_helper
add_library(kf_helper
    src/kf_helper.cpp
)

target_include_directories(kf_helper PUBLIC include)
target_link_libraries(kf_helper PUBLIC Eigen3::Eigen)

# Library: kf
add_library(kf
    src/kf.cpp
)
target_include_directories(kf PUBLIC include)
target_link_libraries(kf PUBLIC kf_helper Eigen3::Eigen)

enable_testing()
add_subdirectory(tests)

# Main program executable
add_executable(main src/main.cpp)
target_link_libraries(main
    kf_helper
    kf
)