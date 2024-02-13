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

S21Matrix S21Matrix::Find_minor(int row, int col) const {
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

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("Matrix is not square, determinant is unavailable");
  }

  if (rows_ == 1) return matrix_[0];
  // if (rows_ == 2) return matrix_[0] * matrix_[4] - matrix_[1] * matrix_[3];
  double det = 0;
  int sign = 1;

  for (int j = 0; j < cols_; j++) {
    S21Matrix Minor = Find_minor(0, j);
    det += sign * (*this)(0, j) * Minor.Determinant();
    sign *= -1;
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error(
        "Matrix is not square, CalcComplements is unavailable");
  }
  S21Matrix result(rows_, cols_);
  double det = 0.;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix Minor = Find_minor(0, j);
      det = Minor.Determinant();
      result(i, j) = det * pow(-1, (i + j));
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) throw std::invalid_argument("Matrix is not square");
  double determinant = Determinant();
  if (determinant == 0)
    throw std::invalid_argument(
        "Determinant is zero, InverseMatrix is unavailable");

  // Получаем транспонированную матрицу алгебраических дополнений
  S21Matrix adjoint(rows_, cols_);
  adjoint = CalcComplements();
  adjoint = adjoint.Transpose();

  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(i, j) = (1 / determinant) * adjoint(i, j);
    }
  }
  return result;
}
