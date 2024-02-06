#include <iomanip>

#include "s21_matrix.hpp"
int main() {
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 4;
  A(1, 0) = 2;
  A(1, 1) = 5;
  A(2, 0) = 3;
  A(2, 1) = 6;
  B(0, 0) = 1;
  B(0, 1) = -1;
  B(0, 2) = 1;
  B(1, 0) = 2;
  B(1, 1) = 3;
  B(1, 2) = 4;
  A.PrintMatrix();
  S21Matrix transposed = A.Transpose();
  transposed.PrintMatrix();
  // B.PrintMatrix();
  // B.Transpose();
  // B.PrintMatrix();
  return 0;
}

/*
  S21Matrix A(3, 2);
  S21Matrix B(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 4;
  A(1, 0) = 2;
  A(1, 1) = 5;
  A(2, 0) = 3;
  A(2, 1) = 6;
  B(0, 0) = 1;
  B(0, 1) = -1;
  B(0, 2) = 1;
  B(1, 0) = 2;
  B(1, 1) = 3;
  B(1, 2) = 4;
  A.PrintMatrix();
  A.Transpose();
  A.PrintMatrix();
  B.PrintMatrix();
  B.Transpose();
  B.PrintMatrix();*/

/*


    S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(1, 0) = 4;
  B(1, 1) = 5;
  B(1, 2) = 6;
  B(2, 0) = 7;
  B(2, 1) = 8;
  B(2, 2) = 9;

    test2(0, 0) = 30;
    test2(0, 1) = 36;
    test2(0, 2) = 42;
    test2(1, 0) = 66;
    test2(1, 1) = 81;
    test2(1, 2) = 96;
    test2(2, 0) = 102;
    test2(2, 1) = 126;
    test2(2, 2) = 150;

  A.PrintMatrix();
  B.PrintMatrix();
  A.MulMatrix(B);
  A.PrintMatrix();
*/

/*

            1 4    1 -1  1    9 11 17
C = A × B = 2 5  × 2  3  4 = 12 13 22
            3 6              15 15 27

B(0, 0) = -19999999425665;
B(0, 1) = 200000009840676;
B(0, 2) = 399999991639265;
B(1, 0) = -40000000294291;
B(1, 1) = -59999999675878;
B(1, 2) = 69999999752287;*/

void S21Matrix::PrintMatrix() const {
  std::cout << "Matrix " << rows_ << "x" << cols_ << ":\n";

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      // Используем std::setw для выравнивания элементов
      std::cout << std::setw(3) << (*this)(i, j) << " ";
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

/*
void S21Matrix::PrintMatrix() const {
  std::cout << "Matrix " << rows_ << "x" << cols_ << ":\n";

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      // Используем std::setw для выравнивания элементов
      std::cout << std::setw(8) << matrix_[i * cols_ + j] << " ";
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}
*/
