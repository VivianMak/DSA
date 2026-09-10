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