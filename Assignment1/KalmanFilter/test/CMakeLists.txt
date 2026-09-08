cmake_minimum_required(VERSION 3.10)
project(KalmanFilter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)   # or omit — see note below

# Library: test_math
add_library(test_math
    test_math.cpp
)

target_include_directories(test_math PUBLIC include)
target_link_libraries(test_math Eigen3::Eigen)
add_executable(test test_math.cpp)