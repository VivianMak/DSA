#include <gtest/gtest.h>
#include <vector>
#include "sorting.hpp"

TEST(InsertionSort, sort)
{
    std::vector<int> v = {23, 1, 10, 5, 2};
    Sorting::insertion_sort(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 5, 10, 23}));

    std::vector<int> empty = {};
    Sorting::insertion_sort(empty);
    EXPECT_EQ(empty, (std::vector<int>{}));

    std::vector<int> dup = {3, 1, 3, 2};
    Sorting::insertion_sort(dup);
    EXPECT_EQ(dup, (std::vector<int>{1, 2, 3, 3}));
}

TEST(SelectionSort, sort)
{
    std::vector<int> v = {23, 1, 10, 5, 2};
    Sorting::selection_sort(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 5, 10, 23}));

    std::vector<int> empty = {};
    Sorting::selection_sort(empty);
    EXPECT_EQ(empty, (std::vector<int>{}));

    std::vector<int> dup = {3, 1, 3, 2};
    Sorting::selection_sort(dup);
    EXPECT_EQ(dup, (std::vector<int>{1, 2, 3, 3}));
}

TEST(HeapSort, sort)
{
    std::vector<int> v = {23, 1, 10, 5, 2};
    Sorting::heap_sort(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 5, 10, 23}));

    std::vector<int> empty = {};
    Sorting::heap_sort(empty);
    EXPECT_EQ(empty, (std::vector<int>{}));

    std::vector<int> dup = {3, 1, 3, 2};
    Sorting::heap_sort(dup);
    EXPECT_EQ(dup, (std::vector<int>{1, 2, 3, 3}));
}

TEST(RadixSort, sort)
{
    std::vector<int> v = {23, 1, 10, 5, 2};
    Sorting::radix_sort(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 5, 10, 23}));

    std::vector<int> empty = {};
    Sorting::radix_sort(empty);
    EXPECT_EQ(empty, (std::vector<int>{}));

    std::vector<int> dup = {3, 1, 3, 2};
    Sorting::radix_sort(dup);
    EXPECT_EQ(dup, (std::vector<int>{1, 2, 3, 3}));
}