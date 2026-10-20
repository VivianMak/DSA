#include <gtest/gtest.h>

#include "matrix.hpp"

#include <random>
#include <stdexcept>
#include <vector>

// Namespace and class are both called Matrix, so alias it
template <typename T>
using Mat = Matrix::Matrix<T>;

// Matrix has no operator==, so compare element by element
template <typename T>
void expect_equal(const Mat<T>& a, const Mat<T>& b) {
    ASSERT_EQ(a.rows(), b.rows());
    ASSERT_EQ(a.cols(), b.cols());
    for (size_t r = 0; r < a.rows(); ++r)
        for (size_t c = 0; c < a.cols(); ++c)
            EXPECT_EQ(a(r, c), b(r, c)) << "mismatch at (" << r << ", " << c << ")";
}

Mat<int> random_matrix(size_t n, unsigned seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(0, 9);   // small range, no int overflow
    Mat<int> M(n, n);
    for (size_t r = 0; r < n; ++r)
        for (size_t c = 0; c < n; ++c)
            M(r, c) = dist(rng);
    return M;
}

TEST(MakeMatrix, initalization){

    // default with zeros
    Mat<int> Z(3, 4);
    EXPECT_EQ(Z.rows(), 3u);
    EXPECT_EQ(Z.cols(), 4u);
    for (size_t r = 0; r < 3; ++r)
        for (size_t c = 0; c < 4; ++c)
            EXPECT_EQ(Z(r, c), 0);

    // default with all value
    Mat<int> S(2, 2, 7);
    for (size_t r = 0; r < 2; ++r)
        for (size_t c = 0; c < 2; ++c)
            EXPECT_EQ(S(r, c), 7);

    // intialize with values
    Mat<int> M({{1, 2, 3}, {4, 5, 6}});
    EXPECT_EQ(M.rows(), 2u);
    EXPECT_EQ(M.cols(), 3u);
    EXPECT_EQ(M(0, 0), 1);


    // writing through operator()
    M(1, 2) = 99;
    EXPECT_EQ(M(1, 2), 99);

    // invalid sizes
    EXPECT_THROW(Mat<int>({{1, 2, 3}, {4, 5}}), std::invalid_argument);
    EXPECT_THROW(Mat<int>(0, 3), std::invalid_argument);

}

TEST(CheckValid, compatible_for_operations){
    // check_same_size function
    Mat<int> A(2, 3);
    Mat<int> B(3, 2);
    Mat<int> C(2, 3);

    // addition and subtraction operation
    EXPECT_THROW(A + B, std::invalid_argument);
    EXPECT_THROW(A - B, std::invalid_argument);
    EXPECT_NO_THROW(A + C);
    EXPECT_NO_THROW(A - C);

    // multiplication operation
    EXPECT_NO_THROW(A * B);                          // 2x3 * 3x2 is valid
    EXPECT_THROW(A * C, std::invalid_argument);      // 2x3 * 2x3 is not
}

TEST(AddMatrix, addition){

    // Test matricies
    Mat<int> A({{1, 2, 3}, {4, 5, 6}});
    Mat<int> B({{10, 20, 30}, {40, 50, 60}});

    Mat<int> sum = A + B;
    expect_equal(sum, Mat<int>({{11, 22, 33}, {44, 55, 66}}));

    Mat<int> diff = B - A;
    expect_equal(diff, Mat<int>({{9, 18, 27}, {36, 45, 54}}));

    // make sure origninal matrix is unchanged
    expect_equal(A, Mat<int>({{1, 2, 3}, {4, 5, 6}}));

}

TEST(MultiplyMatrix, multiplication){

    Mat<int> A({{1, 2, 3}, {4, 5, 6}});
    Mat<int> B({{7, 8}, {9, 10}, {11, 12}});
    expect_equal(A * B, Mat<int>({{58, 64}, {139, 154}}));

}

TEST(StrassenDivide, sub_matricies){
    Mat<int> A({{ 1,  2,  3,  4},
                { 5,  6,  7,  8},
                { 9, 10, 11, 12},
                {13, 14, 15, 16}});

    // order: top-left, top-right, bottom-left, bottom-right
    auto q = Mat<int>::strassen_divide(A);
    ASSERT_EQ(q.size(), 4u);
    expect_equal(q[0], Mat<int>({{1, 2}, {5, 6}}));
    expect_equal(q[1], Mat<int>({{3, 4}, {7, 8}}));
    expect_equal(q[2], Mat<int>({{9, 10}, {13, 14}}));
    expect_equal(q[3], Mat<int>({{11, 12}, {15, 16}}));
}

TEST(StrassenMultiply, block_multiplication){
    
    Mat<int> A({{1, 2}, {3, 4}});
    Mat<int> B({{5, 6}, {7, 8}});
    expect_equal(A.strassen_multiply(B), Mat<int>({{19, 22}, {43, 50}}));
    
}