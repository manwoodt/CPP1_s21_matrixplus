#include "s21_matrix.hpp"

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

int S21Matrix::GetSize() const { return rows_ * cols_; }

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (int i = 0; i < rows_; i++) {
    if (fabs(matrix_[i] - other.matrix_[i]) > 1.e-7) {
      return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("The dimensions of the matrix are not equal");
  for (int i; i < GetSize(); i++) {
    matrix_[i] += other.matrix_[i];
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("The dimensions of the matrix are not equal");
  for (int i; i < GetSize(); i++) {
    matrix_[i] -= other.matrix_[i];
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i; i < GetSize(); i++) {
    matrix_[i] *= num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (rows_ != other.cols_ || cols_ != other.rows_)
    throw std::out_of_range(
        "The dimensions of the matrix are not for multiplication");
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(result);
}
