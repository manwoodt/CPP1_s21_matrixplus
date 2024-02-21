#include <iostream>

#include "s21_matrix.h"
int main() {
  auto A = S21Matrix(3, 3);
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      A(i, j) = A.GetRows() * i + j + 1;
    }
  }
  A.PrintMatrix();
  A = A.Transpose();
  auto B = S21Matrix(3, 3);
  B(0, 0) = 1;
  B(0, 1) = 4;
  B(0, 2) = 7;
  B(1, 0) = 2;
  B(1, 1) = 5;
  B(1, 2) = 8;
  B(2, 0) = 3;
  B(2, 1) = 6;
  B(2, 2) = 9;
  A.PrintMatrix();
  B.PrintMatrix();
  /*
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
  std::cout << "1 тест :" << (check_matrix == matrix1) << std::endl;
  matrix1.PrintMatrix();
  check_matrix.PrintMatrix();
  std::cout << '\n';

  S21Matrix matrix3(2, 2);
  S21Matrix matrix4(2, 2);
  matrix3(0, 0) = 1;
  matrix3(0, 1) = 2;
  matrix3(1, 0) = 3;
  matrix3(1, 1) = 4;

  matrix4(0, 0) = 2;
  matrix4(0, 1) = 3;
  matrix4(1, 0) = 4;
  matrix4(1, 1) = 5;
  matrix3.MulMatrix(matrix4);

  S21Matrix check_matrix2(2, 2);
  check_matrix2(0, 0) = 10.;
  check_matrix2(0, 1) = 13.;
  check_matrix2(1, 0) = 22.;
  check_matrix2(1, 1) = 29.;
  std::cout << "2 тест :" << (check_matrix2 == matrix3) << std::endl;
  matrix3.PrintMatrix();
  check_matrix2.PrintMatrix();
  std::cout << '\n';

  auto test1 = S21Matrix(3, 3);
  auto test4 = S21Matrix(3, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 4;
  test1(1, 1) = 5;
  test1(1, 2) = 6;
  test1(2, 0) = 7;
  test1(2, 1) = 8;
  test1(2, 2) = 9;
  test4(0, 0) = 1;
  test4(0, 1) = 2;
  test4(0, 2) = 3;
  test4(1, 0) = 4;
  test4(1, 1) = 5;
  test4(1, 2) = 6;
  test4(2, 0) = 7;
  test4(2, 1) = 8;
  test4(2, 2) = 9;

  test1 *= test4;
  auto check_matrix3 = S21Matrix(3, 3);
  check_matrix3(0, 0) = 30;
  check_matrix3(0, 1) = 36;
  check_matrix3(0, 2) = 42;
  check_matrix3(1, 0) = 66;
  check_matrix3(1, 1) = 81;
  check_matrix3(1, 2) = 96;
  check_matrix3(2, 0) = 102;
  check_matrix3(2, 1) = 126;
  check_matrix3(2, 2) = 150;

  std::cout << "3 тест :" << (check_matrix3 == test1) << std::endl;
  test1.PrintMatrix();
  check_matrix3.PrintMatrix();
  std::cout << '\n';
  //  test2.PrintMatrix();
  //  B.Transpose();
  //  B.PrintMatrix();
  */
  return 0;
}
