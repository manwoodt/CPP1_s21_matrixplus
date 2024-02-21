#include "s21_matrix.h"

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(const int new_rows) {
  if (new_rows <= 0) throw std::length_error("New rows are not suitable");
  if (new_rows != rows_) {
    S21Matrix tmp(new_rows, cols_);
    for (int i = 0; i < (rows_ < new_rows ? rows_ : new_rows); ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}

void S21Matrix::SetCols(const int new_cols) {
  if (new_cols <= 0) throw std::length_error("New cols are not suitable");

  S21Matrix tmp(rows_, new_cols);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < (cols_ < new_cols ? cols_ : new_cols); ++j)
      tmp(i, j) = (*this)(i, j);

  *this = std::move(tmp);
}

int S21Matrix::GetSize() const { return rows_ * cols_; }

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (int i = 0; i < GetSize(); i++) {
    if (fabs(matrix_[i] - other.matrix_[i]) > 1e-7) {
      return false;
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("The dimensions of the matrix are not equal");
  for (int i = 0; i < GetSize(); i++) {
    matrix_[i] += other.matrix_[i];
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("The dimensions of the matrix are not equal");
  for (int i = 0; i < GetSize(); i++) {
    matrix_[i] -= other.matrix_[i];
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < GetSize(); i++) {
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

void S21Matrix::PrintMatrix() const {
  std::cout << "Matrix " << rows_ << "x" << cols_ << ":\n";

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      // Используем std::setw для выравнивания элементов
      std::cout << std::setw(3) << (*this)(i, j) << " ";
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
}