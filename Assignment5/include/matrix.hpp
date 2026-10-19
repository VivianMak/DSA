#pragma once

#include <stdexcept>
#include <vector>

namespace Matrix{

template <typename T>
class Matrix{

    private:
        int rows_;
        int cols_;
        std::vector<std::vector<T>> data_;

    public:
        // Example matrix to pass in:
        // Matrix<int> M = {
        //  {1, 2, 3},
        //  {4, 5, 6}
        // };
        Matrix(std::initializer_list<std::initializer_list<T>> list)
        {
            rows_ = list.size();
            cols_ = list.begin->size();
            if (rows_ == 0 || cols_ == 0) {
                throw std::invalid_argument("Matrix dimensions must be greater than zero.");
            }
        }

        // // Get value from matrix
        // const T& get_val(int row, int col) const{
        //     return (*this)(row, col);
        // }
        // // Set value in matrix
        // void set_val(int row, int col, T val){
        //     (*this)(row, col) = val;
        // }

        // Using overloading operators () for element acces
        // ie M(1,2) = 2; to write
        // ie M(1,2); to read
        T& operator()(size_t row, size_t col) {
            if (row >= rows_ || col >= cols_) {
                throw std::out_of_range("Matrix index out of bounds.");
            }
            return data_[row][col];
        }

        // for const matricies
        const T& operator()(size_t row, size_t col) const {
            if (row >= rows_ || col >= cols_) {
                throw std::out_of_range("Matrix index out of bounds.");
            }
            return data_[row][col];
        }


        // Matrix multiplicatoin
        Matrix operator*(const Matrix& matrix) const {

            // Check matrix size if n = m
            if (cols_ != matrix.rows_) {
                throw std::invalid_argument("Matrix dimensions incompatible for multiplication.");
            }
            
            // Create empty result matrix
            Matrix result(rows_, matrix.cols_, 0);

            // Multiple other matrix column with this matrix row
            for (size_t i = 0; i < rows_; ++i) {
                for (size_t k = 0; k < cols_; ++k) {
                    for (size_t j = 0; j < matrix.cols_; ++j) {
                        result(i, j) += (*this)(i, k) * matrix(k, j);
                    }
                }
            }
            return result;
        }

        // Divide a n by n matrix into four n/2 by n/2 matricies
        Matix straussen_divide(){

        }

};

} // namespace Matrix