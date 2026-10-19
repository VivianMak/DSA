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
add_executable(test_sorting
    test_sorting.cpp
)

target_link_libraries(test_sorting PRIVATE
    GTest::gtest_main
    sort_lib
)

gtest_discover_tests(test_sorting)
