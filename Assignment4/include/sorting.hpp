#pragma once
#include <vector>

namespace Sorting 
{

void insertion_sort(std::vector<int>& a);

void selection_sort(std::vector<int>& a);

void heap_sort(std::vector<int>& a);

void radix_sort(std::vector<int>& a);  // non-negative ints

}