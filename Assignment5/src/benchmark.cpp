#include "matrix.hpp"

#include <random>
#include <chrono>
#include <numeric>
#include <print>
#include <numeric>
#include <algorithm>
#include <string>

// pointer to function
using CalcFn = void (*)(std::vector<int>&);
template <typename T>
using Mat = Matrix::Matrix<T>;

Mat<int> make_random_matrix(std::size_t size, std::mt19937& rng)
{
    std::uniform_int_distribution<int> dist(0, 99999);

    // Mak a random matrix of M by M size
    Mat<int> M(size, size);

    // Random val for each element
    for (std::size_t r = 0; r < size; ++r)
        for (std::size_t c = 0; c < size; ++c)
            M(r, c) = dist(rng);

    return M;
}

// Takes `data` by value so each call sorts its own copy
double time_strassen(CalcFn sort, std::vector<int> data)
{
    auto start = std::chrono::steady_clock::now();
    sort(data);
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(end - start).count();   // seconds
}

void benchmark(const std::string& name, CalcFn multiply,
               const std::vector<std::size_t>& sizes, int trials)
{
    std::mt19937 rng(12345);   // same seed per algorithm = same lists

    for (std::size_t size : sizes)
    {   
        // reset times list
        std::vector<double> times;

        for (int i = 0; i < trials; i++)
        {
            Mat<int> matrix = make_random_matrix(size, rng);
            times.push_back(time_sort(multiply, matrix));
        }

        // find the average
        double total = std::accumulate(times.begin(), times.end(), 0.0);
        std::println("{:<10} size={:<8} avg={:.6f} s", name, size, total / trials);
    }
}


int main()
{
    // List size factors
    const std::vector<std::size_t> sizes = {10, 100, 1000}; //, 10000, 100000, 200000};
    const int trials = 5;

    // Benchmarking sorting algorithms
    benchmark("strassen", Matrix::strassen_combine, sizes, trials);
    benchmark("multiply", Matrix::selection_sort, sizes, trials);    
}