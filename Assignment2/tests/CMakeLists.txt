include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Testing Structs
add_executable(test_structs
    test_structs.cpp
)

target_link_libraries(test_structs PRIVATE
    DoublyLinkedList_lib
    structs_lib
    GTest::gtest_main
)

gtest_discover_tests(test_structs)

# Testing Parentheses
add_executable(test_parentheses
    test_parentheses.cpp
)

target_link_libraries(test_parentheses PRIVATE
    valid_lib
    GTest::gtest_main
)

gtest_discover_tests(test_parentheses)
