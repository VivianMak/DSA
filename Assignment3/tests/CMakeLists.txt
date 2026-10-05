include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Testing Graphs
add_executable(test_graph
    test_graph.cpp
)

target_link_libraries(test_graph PRIVATE
    graph_lib
    GTest::gtest_main
)

gtest_discover_tests(test_graph)

# Testing Min Heap
add_executable(test_heap
    test_min_heap.cpp
)

target_link_libraries(test_heap PRIVATE
    heap_lib
    GTest::gtest_main
)

gtest_discover_tests(test_heap)