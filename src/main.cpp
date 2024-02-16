#include <iomanip>
#include <iostream>

#include "s21_matrix.hpp"
int main() {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix1.MulMatrix(matrix2);

  S21Matrix check_matrix(2, 2);
  check_matrix(0, 0) = 10.;
  check_matrix(0, 1) = 13.;
  check_matrix(1, 0) = 22.;
  check_matrix(1, 1) = 29.;
  std::cout << (check_matrix == matrix1) << std::endl;

  /*
  std::cout << "res1 " << test1.EqMatrix(test2);
  test2(1, 1) = 1;
  std::cout << "res2 " << test1.EqMatrix(test2);
  */
  //  ошибка
  /*
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;
  A.PrintMatrix();
  double a = A.Determinant();
  std::cout << "res" << a;
  B.PrintMatrix();
  */

  matrix1.PrintMatrix();
  check_matrix.PrintMatrix();
  //  test2.PrintMatrix();
  //  B.Transpose();
  //  B.PrintMatrix();
  return 0;
}

/*
  auto test1 = S21Matrix(3, 3);
  test1(1, 2) = 5;
  auto test2 = test1;

  EXPECT_TRUE(test1.EqMatrix(test2));
  EXPECT_TRUE(test1.EqMatrix(test2) == (test1 == test2));
  test2(1, 1) = 1;
  //  ошибка
  EXPECT_FALSE(test1.EqMatrix(test2));
  EXPECT_TRUE(test1.EqMatrix(test2) == (test1 == test2));
  auto test3 = S21Matrix(5, 5);
  EXPECT_FALSE(test1.EqMatrix(test3));
  EXPECT_TRUE(test1.EqMatrix(test3) == (test1 == test3));


  S21Matrix test10(3, 3);
  S21Matrix test1(3, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 4;
  test1(1, 1) = 5;
  test1(1, 2) = 6;
  test1(2, 0) = 7;
  test1(2, 1) = 8;
  test1(2, 2) = 9;
  test10(0, 0) = 1;
  test10(0, 1) = 2;
  test10(0, 2) = 3;
  test10(1, 0) = 4;
  test10(1, 1) = 5;
  test10(1, 2) = 6;
  test10(2, 0) = 7;
  test10(2, 1) = 8;
  test10(2, 2) = 9;
  test1.MulMatrix(test10);

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
