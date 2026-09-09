# cmake_minimum_required(VERSION 3.10)
# project(KalmanFilter LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17)

# find_package(Eigen3 3.3 REQUIRED NO_MODULE)   # or omit — see note below

# # Library: test_kf
# add_library(test_kf
#     test_kf.cpp
# )

# target_include_directories(test_kf PUBLIC include)
# target_link_libraries(test_kf Eigen3::Eigen)
# add_executable(tests test_kf.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(kf_tests
    test_kf.cpp
)

target_link_libraries(kf_tests PRIVATE
    kf_helper
    kf
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(kf_tests)