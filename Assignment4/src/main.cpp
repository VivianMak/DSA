#include <iostream>
#include <algorithm>
#include <cassert>
#include <print>
#include "sorting.hpp"

int main()
{
    std::vector<int> a = {23, 1, 10, 5, 2};
    auto expected = a;
    std::sort(expected.begin(), expected.end());

    // Testing sorting algorithms
    Sorting::insertion_sort(a);
    assert(a == expected && "Error: inserttion sort did not sort correctly.");

    Sorting::selection_sort(a);
    assert(a == expected && "Error: selection sort did not sort correctly.");

    Sorting::heap_sort(a);
    assert(a == expected && "Error: heap sort did not sort correctly.");

    Sorting::radix_sort(a);
    assert(a == expected && "Error: radix sort did not sort correctly.");

    // Show vector
    std::print("[");
    for (std::size_t i = 0; i < a.size(); ++i)
        std::print("{}{}", i ? ", " : "", a[i]);
    std::println("]");
    
    return 0;
}
