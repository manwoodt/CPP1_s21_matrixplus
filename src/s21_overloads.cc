#include "s21_matrix.h"

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Incorrect input, index is out of range");

  return matrix_[row * cols_ + col];
}

double &S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Incorrect input, index is out of range");

  return matrix_[row * cols_ + col];
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}
S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}
S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}
