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

        // Check if the other matrix is compatible for matrix operations
        void check_valid(const Matrix& other) {
            if (rows_!=other.rows_ || cols_!=other.cols_) {
                throw std::invalid_argument("Matrix dimensions must match for addition.");
            }
        }

        // Matrix Addition
        Matrix operator+(const Matrix& other) const {

            check_valid(other);

            // Create empty result matrix
            Matrix result(rows_, other.cols_);

            // Perform element-wise addition
            for (size_t i = 0; i < data_.size(); ++i) {
                result.data_[i] = this->data_[i] + other.data_[i];
            }
            return result;

        }

        // Matrix Subtraction
        Matrix operator-(const Matrix& other) const {

            check_valid(other);

            // Create empty result matrix
            Matrix result(rows_, other.cols_);

            // Perform element-wise subtraction
            for (size_t i = 0; i < data_.size(); ++i) {
                result.data_[i] = this->data_[i] - other.data_[i];
            }
            return result;

        }


        // Matrix Multiplication
        Matrix operator*(const Matrix& other) const {

            check_valid(other);
            
            // Create empty result matrix
            Matrix result(rows_, other.cols_);

            // Multiple other matrix column with this matrix row
            for (size_t i = 0; i < rows_; ++i) {
                for (size_t k = 0; k < cols_; ++k) {
                    for (size_t j = 0; j < other.cols_; ++j) {
                        result(i, j) += (*this)(i, k) * other(k, j);
                    }
                }
            }
            return result;
        }

        // Divide a n by n matrix into four n/2 by n/2 matricies
        Matix straussen_divide(){

        }

        Matrix strassen_multiply(){

        }

};

} // namespace Matrix