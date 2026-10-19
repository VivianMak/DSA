#include <iostream>

#include "matrix.hpp"

int main()
{   
    // name
    using Matrix::Matrix;

    Matrix<int> M(2, 3, 7);

    std::cout << M;

    return 0;
}
