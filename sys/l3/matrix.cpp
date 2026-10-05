#include "matrix.h"
#include <iostream>
#include <cstring>

Matrix::Matrix(int rows, int cols)
    : rows_(rows), cols_(cols) {
    data_ = new int[rows * cols];
    std::memset(data_, 0, rows * cols * sizeof(int));
}

void Matrix::clear() {
    std::memset(data_, 0, rows_ * cols_ * sizeof(int));
}

void color(const int value);

void Matrix::print() const {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            color(data_[i * cols_ + j]);
            std::cout << "#" << " ";
        }
        std::cout << std::endl;
    }
    color(0); // Reset color after printing the matrix
}

Matrix::~Matrix() {
    delete[] data_;
}

int Matrix::get(int row, int col) const {
    return data_[row * cols_ + col];
}

void Matrix::set(int row, int col, int value) {
    data_[row * cols_ + col] = value;
}


void color(const int value){
    switch(value) {
        case 0:
            std::cout << "\033[0m"; // Reset color
            break;
        case 1:
            std::cout << "\033[31m"; // Red
            break;
        case 2:
            std::cout << "\033[32m"; // Green
            break;
        case 3:
            std::cout << "\033[34m"; // Blue
            break;
        default:
            std::cout << "\033[0m"; // Reset color for unknown values
            break;
    }
}