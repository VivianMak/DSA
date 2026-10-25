include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Test 1
add_executable(unit_tests
    test_matrix.cpp
    test_NW.cpp
)

target_link_libraries(unit_tests PRIVATE
    matrix_lib
    nw_lib
    GTest::gtest_main
)

gtest_discover_tests(unit_tests)
