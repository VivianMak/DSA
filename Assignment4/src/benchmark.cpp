#include "sorting.hpp"

#include <random>
#include <chrono>
#include <numeric>
#include <print>
#include <numeric>
#include <algorithm>
#include <string>

// pointer to function
using SortFn = void (*)(std::vector<int>&);

std::vector<int> make_random_list(std::size_t size, std::mt19937& rng)
{
    std::uniform_int_distribution<int> dist(0, 99999);
    std::vector<int> v(size);
    for (int& x : v) x = dist(rng);
    return v;
}

// Takes `data` by value so each call sorts its own copy
double time_sort(SortFn sort, std::vector<int> data)
{
    auto start = std::chrono::steady_clock::now();
    sort(data);
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(end - start).count();   // seconds
}

void benchmark(const std::string& name, SortFn sort,
               const std::vector<std::size_t>& sizes, int trials)
{
    std::mt19937 rng(12345);   // same seed per algorithm = same lists

    for (std::size_t size : sizes)
    {   
        // reset times list
        std::vector<double> times;

        for (int i = 0; i < trials; i++)
        {
            std::vector<int> list = make_random_list(size, rng);
            times.push_back(time_sort(sort, list));
        }

        // find the average
        double total = std::accumulate(times.begin(), times.end(), 0.0);
        std::println("{:<10} size={:<8} avg={:.6f} s", name, size, total / trials);
    }
}


int main()
{
    // List size factors
    const std::vector<std::size_t> sizes = {10, 100, 1000, 10000, 100000, 200000}; //{1000000}
    const int trials = 5;

    // Benchmarking sorting algorithms
    benchmark("insertion", Sorting::insertion_sort, sizes, trials);
    benchmark("selection", Sorting::selection_sort, sizes, trials);
    benchmark("heap", Sorting::heap_sort, sizes, trials);
    benchmark("radix", Sorting::radix_sort, sizes, trials);
    
}