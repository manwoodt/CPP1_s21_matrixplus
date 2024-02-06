#include "s21_matrix.hpp"

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result(i, j) = (*this)(j, i);
    }
  }
  return result;
}

S21Matrix S21Matrix::find_minor(int row, int col) {
  if (rows_ != cols_) {
    throw std::logic_error(
        "Minor matrix could be computed only for square matrices");
  }
  if (rows_ < 2 || cols_ < 2)
    throw std::logic_error("Matrix is too small for finding minor");

  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Incorrect input, index of minor is out of range");

  S21Matrix Minor(rows_ - 1, cols_ - 1);

  for (int i = 0, minor_i = 0; i < rows_; ++i) {
    if (i == row) continue;
    for (int j = 0, minor_j = 0; j < cols_; ++j) {
      if (j == col) continue;
      Minor(minor_i, minor_j) = (*this)(i, j);
      ++minor_j;
    }
    ++minor_i;
  }

  return Minor;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::logic_error("Matrix is not square, determinant is unavailable");
  }

  if (rows_ == 1) return matrix_[0];

  double det = 0;
  int sign = 1;

  for (int j = 0; j < cols_; j++) {
    S21Matrix Minor = find_minor(0, j);
    det += sign * (*this)(0, j) * Minor.Determinant();
    sign *= -1;
  }
  return det;
}
