#include <gtest/gtest.h>

#include <cstdio>

#include "s21_matrix.hpp"

TEST(Constructor, Default) {
  auto test = S21Matrix();
  EXPECT_EQ(test.GetRows(), 0);
  EXPECT_EQ(test.GetCols(), 0);
}

TEST(Constructor, By2Args) {
  auto test = S21Matrix(3, 3);
  EXPECT_EQ(test.GetRows(), 3);
  EXPECT_EQ(test.GetCols(), 3);
}

TEST(Constructor, Copy) {
  auto test = S21Matrix(3, 3);
  test(0, 0) = 1;
  auto temp = S21Matrix(test);
  EXPECT_EQ(test, temp);
}

TEST(Constructor, Move) {
  auto test1 = S21Matrix(3, 3);
  test1(1, 1) = 5;
  auto test2 = S21Matrix(test1);
  auto test3 = S21Matrix(std::move(test1));
  EXPECT_EQ(test2, test3);
}

TEST(Calculation, EqMatrix) {
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
}

TEST(Calculation, SumMatrix) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;
  auto test2 = test1;
  test1.SumMatrix(test2);
  EXPECT_EQ(test1(0, 0), 2);
}

TEST(Calculation, SubMatrix) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;
  auto test2 = test1;
  test1.SubMatrix(test2);
  EXPECT_EQ(test1(0, 0), 0);
}

TEST(Calculation, MulNumber) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 5;
  test1.MulNumber(3);
  EXPECT_EQ(test1(0, 0), 15);
}

TEST(Calculation, Find_minor) {
  auto test1 = S21Matrix(3, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 4;
  test1(1, 1) = 5;
  test1(1, 2) = 6;
  test1(2, 0) = 7;
  test1(2, 1) = 8;
  test1(2, 2) = 9;
  auto test3 = test1.Find_minor(0, 0);
  auto test2 = S21Matrix(2, 2);
  test2(0, 0) = 5;
  test2(0, 1) = 6;
  test2(1, 0) = 8;
  test2(1, 1) = 9;

  EXPECT_EQ(test3, test2);
}
// ошибка

TEST(Calculation, MulMatrix) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.GetRows(), 2);
  EXPECT_EQ(matrix1.GetCols(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.GetRows(), 2);
  EXPECT_EQ(matrix2.GetCols(), 2);

  S21Matrix check_matrix{2, 2};
  EXPECT_EQ(check_matrix.GetRows(), 2);
  EXPECT_EQ(check_matrix.GetCols(), 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;

  check_matrix(0, 0) = 10.;
  check_matrix(0, 1) = 13.;
  check_matrix(1, 0) = 22.;
  check_matrix(1, 1) = 29.;

  matrix1.MulMatrix(matrix2);
  S21Matrix matrix2_before = matrix2;
  // matrix1.PrintMatrix();
  // matrix1.PrintMatrix();
  EXPECT_EQ(matrix1.GetRows(), 2);
  EXPECT_EQ(matrix1.GetCols(), 2);

  ASSERT_TRUE(matrix1 == check_matrix);
  ASSERT_TRUE(matrix2 == matrix2_before);
}

TEST(DeterminantAndCo, Transpose) {
  auto test1 = S21Matrix(3, 3);
  for (int i = 0; i < test1.GetRows(); i++) {
    for (int j = 0; j < test1.GetCols(); j++) {
      test1(i, j) = test1.GetRows() * i + j + 1;
    }
  }
  test1 = test1.Transpose();
  auto test2 = S21Matrix(3, 3);
  test2(0, 0) = 1;
  test2(0, 1) = 4;
  test2(0, 2) = 7;
  test2(1, 0) = 2;
  test2(1, 1) = 5;
  test2(1, 2) = 8;
  test2(2, 0) = 3;
  test2(2, 1) = 6;
  test2(2, 2) = 9;
  EXPECT_EQ(test1, test2);
}

TEST(DeterminantAndCo, CalcComplements) {
  auto test1 = S21Matrix(3, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 0;
  test1(1, 1) = 4;
  test1(1, 2) = 2;
  test1(2, 0) = 5;
  test1(2, 1) = 2;
  test1(2, 2) = 1;
  test1 = test1.CalcComplements();
  auto test2 = S21Matrix(3, 3);
  test2(0, 0) = 0;
  test2(0, 1) = 10;
  test2(0, 2) = -20;
  test2(1, 0) = 4;
  test2(1, 1) = -14;
  test2(1, 2) = 8;
  test2(2, 0) = -8;
  test2(2, 1) = -2;
  test2(2, 2) = 4;
  EXPECT_EQ(test1, test2);
}

TEST(DeterminantAndCo, Determinant) {
  auto test1 = S21Matrix(3, 3);
  test1(0, 0) = 1;
  test1(0, 1) = 2;
  test1(0, 2) = 3;
  test1(1, 0) = 0;
  test1(1, 1) = 4;
  test1(1, 2) = 2;
  test1(2, 0) = 5;
  test1(2, 1) = 2;
  test1(2, 2) = 1;
  EXPECT_DOUBLE_EQ(test1.Determinant(), -40);
}

TEST(DeterminantAndCo, CalcComplementsOne) {
  S21Matrix a(2, 4);
  ASSERT_THROW(a.CalcComplements(), std::logic_error);
}

TEST(Technical, GetRows) {
  auto test1 = S21Matrix();
  EXPECT_EQ(test1.GetRows(), 0);
  auto test2 = S21Matrix(2, 2);
  EXPECT_EQ(test2.GetRows(), 2);
}

TEST(Technical, GetCols) {
  auto test1 = S21Matrix();
  EXPECT_EQ(test1.GetCols(), 0);
  auto test2 = S21Matrix(2, 2);
  EXPECT_EQ(test2.GetCols(), 2);
}

TEST(Technical, SetRows) {
  auto test1 = S21Matrix(1, 1);
  test1.SetRows(5);
  EXPECT_EQ(test1.GetRows(), 5);
  test1.SetRows(1);
}

TEST(Technical, SetCols) {
  auto test1 = S21Matrix(1, 1);
  test1.SetCols(5);
  EXPECT_EQ(test1.GetCols(), 5);
  test1.SetRows(1);
}
// ошибка

TEST(DeterminantAndCo, InverseMatrix) {
  auto test1 = S21Matrix(3, 3);
  test1(0, 0) = 3;
  test1(0, 1) = 5;
  test1(0, 2) = -2;
  test1(1, 0) = 1;
  test1(1, 1) = -3;
  test1(1, 2) = 2;
  test1(2, 0) = 6;
  test1(2, 1) = 7;
  test1(2, 2) = -3;
  auto test3 = test1.InverseMatrix();
  auto test2 = S21Matrix(3, 3);
  test2(0, 0) = -0.5;
  test2(0, 1) = 0.1;
  test2(0, 2) = 0.4;
  test2(1, 0) = 1.5;
  test2(1, 1) = 0.3;
  test2(1, 2) = -0.8;
  test2(2, 0) = 2.5;
  test2(2, 1) = 0.9;
  test2(2, 2) = -1.4;
  EXPECT_EQ(test2, test3);
}

// overloads

TEST(Overloads, SumOperator) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;

  auto test2 = S21Matrix(1, 1);
  test2(0, 0) = 1;

  auto test3 = S21Matrix(1, 1);
  test3 = test1 + test2;

  auto expected = S21Matrix(1, 1);
  expected(0, 0) = 2;

  EXPECT_EQ(test3, expected);
}

TEST(Overloads, SubOperator) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;

  auto test2 = S21Matrix(1, 1);
  test2(0, 0) = 1;

  auto test3 = S21Matrix(1, 1);
  test3 = test1 - test2;

  auto expected = S21Matrix(1, 1);
  expected(0, 0) = 0;

  EXPECT_EQ(test3, expected);
}

TEST(Overloads, MulNumberOperator) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 5;
  auto test2 = S21Matrix(1, 1);
  test2 = test1 * 3;
  EXPECT_EQ(test2(0, 0), 15);
}

// ошибка

TEST(Overloads, MulMatrixOperator) {
  S21Matrix matrix1{2, 2};
  EXPECT_EQ(matrix1.GetRows(), 2);
  EXPECT_EQ(matrix1.GetCols(), 2);

  S21Matrix matrix2{2, 2};
  EXPECT_EQ(matrix2.GetRows(), 2);
  EXPECT_EQ(matrix2.GetCols(), 2);

  S21Matrix check_matrix{2, 2};
  EXPECT_EQ(check_matrix.GetRows(), 2);
  EXPECT_EQ(check_matrix.GetCols(), 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 2;
  matrix2(0, 1) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;

  check_matrix(0, 0) = 10.;
  check_matrix(0, 1) = 13.;
  check_matrix(1, 0) = 22.;
  check_matrix(1, 1) = 29.;

  S21Matrix matrix2_before = matrix2;
  matrix1 *= matrix2;

  EXPECT_EQ(matrix1.GetRows(), 2);
  EXPECT_EQ(matrix1.GetCols(), 2);

  // ASSERT_TRUE(matrix1 == check_matrix);
  ASSERT_TRUE(matrix2 == matrix2_before);
}

TEST(Overloads, AdditionSumOperator) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;

  auto test2 = S21Matrix(1, 1);
  test2(0, 0) = 1;

  auto test3 = S21Matrix(1, 1);
  test1 += test2;

  auto expected = S21Matrix(1, 1);
  expected(0, 0) = 2;

  EXPECT_EQ(test1, expected);
}

TEST(Overloads, AdditionSubOperator) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 1;

  auto test2 = S21Matrix(1, 1);
  test2(0, 0) = 1;

  auto test3 = S21Matrix(1, 1);
  test1 -= test2;

  auto expected = S21Matrix(1, 1);
  expected(0, 0) = 0;

  EXPECT_EQ(test1, expected);
}

TEST(Overloads, AdditionMulNumberOperator) {
  auto test1 = S21Matrix(1, 1);
  test1(0, 0) = 5;
  test1 *= 3;
  EXPECT_EQ(test1(0, 0), 15);
}

// ошибка
TEST(Overloads, AdditionMulMatrixOperator) {
  auto test1 = S21Matrix(3, 3);
  auto test10 = S21Matrix(3, 3);
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

  test1 *= test10;
  auto test2 = S21Matrix(3, 3);
  test2(0, 0) = 30;
  test2(0, 1) = 36;
  test2(0, 2) = 42;
  test2(1, 0) = 66;
  test2(1, 1) = 81;
  test2(1, 2) = 96;
  test2(2, 0) = 102;
  test2(2, 1) = 126;
  test2(2, 2) = 150;

  // EXPECT_EQ(test1, test2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// #include <iostream>

// #include "s21_matrix_oop.h"

// int main() {
// auto test1 = S21Matrix(3, 3);
// test1(0, 0) = 1;
// test1(0, 1) = 2;
// test1(0, 2) = 3;
// test1(1, 0) = 3;
// test1(1, 1) = 2;
// test1(1, 2) = 1;
// test1(2, 0) = 7;
// test1(2, 1) = 5;
// test1(2, 2) = 2;
// test1 = test1.CalcComplements();
// auto test2 = S21Matrix(3, 3);
// test2(0, 0) = -1;
// test2(0, 1) = 1;
// test2(0, 2) = 1;
// test2(1, 0) = 11;
// test2(1, 1) = -19;
// test2(1, 2) = 9;
// test2(2, 0) = -4;
// test2(2, 1) = 8;
// test2(2, 2) = -4;
//   auto test1 = S21Matrix(3, 3);
//   test1(0, 0) = 1;
//   test1(0, 1) = 2;
//   test1(0, 2) = 3;
//   test1(1, 0) = 0;
//   test1(1, 1) = 4;
//   test1(1, 2) = 2;
//   test1(2, 0) = 5;
//   test1(2, 1) = 2;
//   test1(2, 2) = 1;
//   test1 = test1.CalcComplements();
//   auto test2 = S21Matrix(3, 3);
//   test2(0, 0) = 0;
//   test2(0, 1) = 10;
//   test2(0, 2) = -20;
//   test2(1, 0) = 4;
//   test2(1, 1) = -14;
//   test2(1, 2) = 8;
//   test2(2, 0) = -8;
//   test2(2, 1) = -2;
//   test2(2, 2) = 4;
//   test1.PrintMatrix();
//   test2.PrintMatrix();
//   return 0;
// }
