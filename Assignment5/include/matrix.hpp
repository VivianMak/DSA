#pragma once

#include <stdexcept>
#include <vector>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace Matrix{

template <typename T>
class Matrix{

    private:
        int rows_;
        int cols_;
        std::vector<std::vector<T>> data_;

        // Check if the other matrix is compatible for matrix operations
        void check_valid(const Matrix& other) const{
            if (rows_!=other.rows_ || cols_!=other.cols_) {
                throw std::invalid_argument("Matrix dimensions must match.");
            }
        }

    public:
        // DEFAULT CONSTRUCTOR
        // rows x cols matrix filled with init (zero by default)
        Matrix(size_t rows, size_t cols, const T& init = T())
            : rows_(rows), cols_(cols), data_(rows, std::vector<T>(cols, init))
        {
            if (rows_ == 0 || cols_ == 0) {
                throw std::invalid_argument("Matrix dimensions must be greater than zero.");
            }
        }
    
        // Example matrix to pass in:
        // Matrix<int> M = ({{1, 2, 3}, {4, 5, 6}});
        Matrix(std::vector<std::vector<T>> list)
            :rows_(list.size()), cols_(0), data_(std::move(list))
        {
            if (rows_ == 0 || data_[0].empty()) {
                throw std::invalid_argument("Matrix dimensions must be greater than zero.");
            }
            cols_ = data_[0].size();
            for (const auto& row : data_) {
                if (row.size() != cols_) {
                    throw std::invalid_argument("All rows must have the same number of columns.");
                }
            }
        }

        size_t rows() const { return rows_; }
        size_t cols() const { return cols_; }

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
        static std::vector<Matrix> strassen_divide(const Matrix& other){ // adding static so doesn't need an object to be called on

            // Check n by n matrix
            if (other.rows_ != other.cols_) {
                throw std::invalid_argument("Matrix dimensions must match for strassen divide.");
            }
            // Check even-ness of size n
            if (other.rows_ % 2 != 0) {
                throw std::invalid_argument("Matrix size must be even for strassen divide.");
            }

            // Create empty vector to store matricies
            std::vector<Matrix> result;

            size_t half = other.rows_/2;

            for (size_t i = 0; i < 4; i++){
                // i = 0 -> (0,0)   i = 1 -> (0,half)
                // i = 2 -> (half,0)   i = 3 -> (half,half)
                const size_t row_off = (i / 2) * half;
                const size_t col_off = (i % 2) * half;

                // Create temporary matrix of zeros
                Matrix temp(half, half);

                // Element-wise reassignment
                for (size_t r = 0; r < half; ++r) {
                    for (size_t c = 0; c < half; ++c) {
                        temp.data_[r][c] = other.data_[r + row_off][c + col_off];
                    }
                }

                // Reassign pointer owner rather than copy
                result.push_back(std::move(temp)); 
            }

            return result;
        }

        /**
         * Multiply [this] matrix by [other].
         * Your code should use Strassen's algorithm
         * @return [this]*[other] if the dimensions are compatible and null otherwise
         */
        Matrix strassen_multiply(const Matrix& other){
            
            // Split the matricies first
            std::vector<Matrix> this_matricies = strassen_divide(*this);
            std::vector<Matrix> other_matricies = strassen_divide(other);

        }


        // Pretty print matrix (AI generated code)
        // Pretty-print with right-aligned columns.
        // precision >= 0 prints floating-point values with that many decimals.
        void print(std::ostream& os = std::cout, int precision = -1) const {

            // Format every element once and track the widest entry in each column
            std::vector<std::vector<std::string>> cells(rows_, std::vector<std::string>(cols_));
            std::vector<size_t> widths(cols_, 0);

            for (size_t r = 0; r < rows_; ++r) {
                for (size_t c = 0; c < cols_; ++c) {
                    std::ostringstream ss;
                    if (precision >= 0) ss << std::fixed << std::setprecision(precision);
                    ss << data_[r][c];
                    cells[r][c] = ss.str();
                    widths[c] = std::max(widths[c], cells[r][c].size());
                }
            }

            for (size_t r = 0; r < rows_; ++r) {
                os << "| ";
                for (size_t c = 0; c < cols_; ++c) {
                    os << std::setw(static_cast<int>(widths[c])) << cells[r][c];
                    if (c + 1 < cols_) os << "  ";
                }
                os << " |\n";
            }
        }

        // Lets you write: std::cout << M;
        friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
            m.print(os);
            return os;
        }

};

} // namespace Matrix