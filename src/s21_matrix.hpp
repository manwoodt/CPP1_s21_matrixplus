#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>

#include <cstring>   // memcpy
#include <iostream>  // cout
#include <stdexcept>
#include <utility>  // swap

class S21Matrix {
 private:
  int rows_, cols_;
  double *matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;

  int GetCols() const;
  int GetRows() const;
  int GetSize() const;
  void PrintMatrix() const;

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);

  double &operator()(int row, int col);
  double &operator()(int row, int col) const;
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  bool operator==(const S21Matrix &other) const;

  S21Matrix Transpose() const;

  S21Matrix Find_minor(int row, int col) const;
  double Determinant() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;
};

#endif  // SRC_S21_MATRIX_H_
