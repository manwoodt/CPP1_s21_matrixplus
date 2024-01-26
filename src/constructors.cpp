#include "s21_matrix.hpp"
#include <stdexcept>

S21Matrix::S21Matrix() : rows_ = 0, cols_ = 0, matrix_ = nullptr{};

/*
S21Matrix(int rows, int cols);
S21Matrix(const S21Matrix &other);
S21Matrix(S21Matrix &&other);
~S21Matrix();
*/