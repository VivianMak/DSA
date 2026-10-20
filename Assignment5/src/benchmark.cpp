#include "matrix.hpp"

#include <random>
#include <chrono>
#include <numeric>
#include <print>
#include <numeric>
#include <algorithm>
#include <string>

// pointer to function
using CalcFn = Matrix::Matrix<int> (*)(const Matrix::Matrix<int>&, const Matrix::Matrix<int>&);
template <typename T>
using Mat = Matrix::Matrix<T>;

Mat<int> strassen_fn(const Mat<int>& a, const Mat<int>& b)
{
    return a.strassen_multiply(b);
}

Mat<int> default_fn(const Mat<int>& a, const Mat<int>& b)
{
    return a * b;
}


Mat<int> make_random_matrix(std::size_t size, std::mt19937& rng)
{
    std::uniform_int_distribution<int> dist(0, 9);

    // Mak a random matrix of M by M size
    Mat<int> M(size, size);

    // Random val for each element
    for (std::size_t r = 0; r < size; ++r)
        for (std::size_t c = 0; c < size; ++c)
            M(r, c) = dist(rng);

    return M;
}

double time_strassen(CalcFn multiply, Mat<int> matrix, Mat<int> other)
{
    auto start = std::chrono::steady_clock::now();
    Mat<int> result = multiply(matrix, other);
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
            Mat<int> other = make_random_matrix(size, rng);
            times.push_back(time_strassen(multiply, matrix, other));
        }

        // find the average
        double total = std::accumulate(times.begin(), times.end(), 0.0);
        std::println("{:<10} size={:<8} avg={:.6f} s", name, size, total / trials);
    }
}


int main()
{
    // List size factors
    const std::vector<std::size_t> sizes = {10, 2000}; //{10, 100, 1000}; //, 10000, 100000, 200000};
    const int trials = 5;

    // Benchmarking sorting algorithms
    // benchmark("strassen", strassen_fn, sizes, trials);
    benchmark("multiply", default_fn, sizes, trials);    
}