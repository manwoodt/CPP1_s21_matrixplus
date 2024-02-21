#include <gtest/gtest.h>

#include <cstdio>

#include "s21_matrix.h"

TEST(Constructor, Default) {
  auto A = S21Matrix();
  EXPECT_EQ(A.GetRows(), 0);
  EXPECT_EQ(A.GetCols(), 0);
}

TEST(Constructor, WithArgs) {
  auto A = S21Matrix(3, 3);
  EXPECT_EQ(A.GetRows(), 3);
  EXPECT_EQ(A.GetCols(), 3);
}

TEST(Constructor, Copy) {
  auto A = S21Matrix(3, 3);
  A(0, 0) = 1;
  A(2, 2) = 2;
  S21Matrix B(A);
  EXPECT_EQ(B.GetCols(), 3);
  EXPECT_EQ(B.GetRows(), 3);
}

TEST(Constructor, CopyAssignmentOperator) {
  auto A = S21Matrix(3, 3);
  A(0, 0) = 1;
  A(2, 2) = 2;
  auto B = S21Matrix(A);
  EXPECT_EQ(A, B);
}

TEST(Constructor, Move) {
  auto A = S21Matrix(3, 3);
  A(1, 1) = 5;
  A(2, 2) = 2;
  S21Matrix moved(std::move(A));
  EXPECT_EQ(A.GetRows(), 0);
  EXPECT_EQ(A.GetCols(), 0);
  EXPECT_EQ(moved.GetRows(), 3);
  EXPECT_EQ(moved.GetCols(), 3);
}

TEST(Constructor, MoveAssignmentOperator) {
  auto A = S21Matrix(3, 3);
  A(1, 1) = 5;
  A(2, 2) = 2;
  S21Matrix moved(1, 1);
  moved = std::move(A);
  EXPECT_EQ(moved.GetRows(), 3);
  EXPECT_EQ(moved.GetCols(), 3);
}

TEST(Calculation, EqMatrix) {
  auto A = S21Matrix(3, 3);
  A(1, 2) = 5;
  auto B = A;

  EXPECT_TRUE(A.EqMatrix(B));
  EXPECT_TRUE(A.EqMatrix(B) == (A == B));
  B(1, 1) = 1;
  EXPECT_FALSE(A.EqMatrix(B));
  EXPECT_TRUE(A.EqMatrix(B) == (A == B));
}

TEST(Calculation, SumMatrix) {
  auto A = S21Matrix(1, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  auto B = A;
  A.SumMatrix(B);
  EXPECT_EQ(A(0, 0), 2);
  EXPECT_EQ(A(0, 1), 4);
}

TEST(Calculation, SubMatrix) {
  auto A = S21Matrix(1, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  auto B = A;
  A.SubMatrix(B);
  EXPECT_EQ(A(0, 0), 0);
  EXPECT_EQ(A(0, 1), 0);
}

TEST(Calculation, MulNumber) {
  auto A = S21Matrix(1, 2);
  A(0, 0) = 5;
  A(0, 1) = 1;
  A.MulNumber(5);
  EXPECT_EQ(A(0, 0), 25);
  EXPECT_EQ(A(0, 1), 5);
}

TEST(Calculation, Find_minor) {
  auto A = S21Matrix(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;
  auto res = A.Find_minor(0, 0);
  auto check_matrix = S21Matrix(2, 2);
  check_matrix(0, 0) = 5;
  check_matrix(0, 1) = 6;
  check_matrix(1, 0) = 8;
  check_matrix(1, 1) = 9;

  EXPECT_EQ(res, check_matrix);
}

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
  EXPECT_EQ(matrix1.GetRows(), 2);
  EXPECT_EQ(matrix1.GetCols(), 2);

  ASSERT_TRUE(matrix1 == check_matrix);
  ASSERT_TRUE(matrix2 == matrix2_before);
}

TEST(DeterminantAndCo, Transpose) {
  auto A = S21Matrix(3, 3);
  // заполнение циклом от 1 до GetSize
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      A(i, j) = A.GetRows() * i + j + 1;
    }
  }
  auto res = A.Transpose();
  auto check_matrix = S21Matrix(3, 3);
  check_matrix(0, 0) = 1;
  check_matrix(0, 1) = 4;
  check_matrix(0, 2) = 7;
  check_matrix(1, 0) = 2;
  check_matrix(1, 1) = 5;
  check_matrix(1, 2) = 8;
  check_matrix(2, 0) = 3;
  check_matrix(2, 1) = 6;
  check_matrix(2, 2) = 9;
  EXPECT_EQ(res, check_matrix);
}

TEST(DeterminantAndCo, CalcComplements) {
  auto A = S21Matrix(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;
  auto res = A.CalcComplements();
  auto check_matrix = S21Matrix(3, 3);
  check_matrix(0, 0) = 0;
  check_matrix(0, 1) = 10;
  check_matrix(0, 2) = -20;
  check_matrix(1, 0) = 4;
  check_matrix(1, 1) = -14;
  check_matrix(1, 2) = 8;
  check_matrix(2, 0) = -8;
  check_matrix(2, 1) = -2;
  check_matrix(2, 2) = 4;
  EXPECT_EQ(res, check_matrix);
}

TEST(DeterminantAndCo, Determinant) {
  auto A = S21Matrix(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;
  EXPECT_DOUBLE_EQ(A.Determinant(), -40);
}

TEST(Technical, GetRows) {
  auto A = S21Matrix();
  EXPECT_EQ(A.GetRows(), 0);
  auto B = S21Matrix(2, 2);
  EXPECT_EQ(B.GetRows(), 2);
}

TEST(Technical, GetCols) {
  auto A = S21Matrix();
  EXPECT_EQ(A.GetCols(), 0);
  auto B = S21Matrix(2, 2);
  EXPECT_EQ(B.GetCols(), 2);
}

TEST(Technical, SetRows) {
  auto A = S21Matrix(1, 1);
  A.SetRows(5);
  EXPECT_EQ(A.GetRows(), 5);
}

TEST(Technical, SetCols) {
  auto A = S21Matrix(1, 1);
  A.SetCols(5);
  EXPECT_EQ(A.GetCols(), 5);
}

TEST(DeterminantAndCo, InverseMatrix) {
  auto A = S21Matrix(3, 3);
  A(0, 0) = 3;
  A(0, 1) = 5;
  A(0, 2) = -2;
  A(1, 0) = 1;
  A(1, 1) = -3;
  A(1, 2) = 2;
  A(2, 0) = 6;
  A(2, 1) = 7;
  A(2, 2) = -3;
  auto res = A.InverseMatrix();
  auto B = S21Matrix(3, 3);
  B(0, 0) = -0.5;
  B(0, 1) = 0.1;
  B(0, 2) = 0.4;
  B(1, 0) = 1.5;
  B(1, 1) = 0.3;
  B(1, 2) = -0.8;
  B(2, 0) = 2.5;
  B(2, 1) = 0.9;
  B(2, 2) = -1.4;
  EXPECT_EQ(B, res);
}

// overloads

TEST(Overloads, SumOperator) {
  auto A = S21Matrix(1, 1);
  A(0, 0) = 1;

  auto B = S21Matrix(1, 1);
  B(0, 0) = 1;

  auto res = S21Matrix(1, 1);
  res = A + B;

  auto expected = S21Matrix(1, 1);
  expected(0, 0) = 2;

  EXPECT_EQ(res, expected);
}

TEST(Overloads, SubOperator) {
  auto A = S21Matrix(1, 1);
  A(0, 0) = 1;

  auto B = S21Matrix(1, 1);
  B(0, 0) = 1;

  auto res = S21Matrix(1, 1);
  res = A - B;

  auto expected = S21Matrix(1, 1);
  expected(0, 0) = 0;

  EXPECT_EQ(res, expected);
}

TEST(Overloads, MulNumberOperator) {
  auto A = S21Matrix(1, 1);
  A(0, 0) = 5;
  auto B = S21Matrix(1, 1);
  B = A * 3;
  EXPECT_EQ(B(0, 0), 15);
}

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

  check_matrix(0, 0) = 10;
  check_matrix(0, 1) = 13;
  check_matrix(1, 0) = 22;
  check_matrix(1, 1) = 29;

  S21Matrix matrix2_before = matrix2;
  matrix1 *= matrix2;

  EXPECT_EQ(matrix1.GetRows(), 2);
  EXPECT_EQ(matrix1.GetCols(), 2);

  ASSERT_TRUE(matrix1 == check_matrix);
  ASSERT_TRUE(matrix2 == matrix2_before);
}

TEST(Overloads, AdditionSumOperator) {
  auto A = S21Matrix(1, 1);
  A(0, 0) = 1;

  auto B = S21Matrix(1, 1);
  B(0, 0) = 1;

  auto res = S21Matrix(1, 1);
  A += B;

  auto expected = S21Matrix(1, 1);
  expected(0, 0) = 2;

  EXPECT_EQ(A, expected);
}

TEST(Overloads, AdditionSubOperator) {
  auto A = S21Matrix(1, 1);
  A(0, 0) = 1;

  auto B = S21Matrix(1, 1);
  B(0, 0) = 1;

  auto res = S21Matrix(1, 1);
  A -= B;

  auto expected = S21Matrix(1, 1);
  expected(0, 0) = 0;

  EXPECT_EQ(A, expected);
}

TEST(Overloads, AdditionMulNumberOperator) {
  auto A = S21Matrix(1, 1);
  A(0, 0) = 5;
  A *= 3;
  EXPECT_EQ(A(0, 0), 15);
}

TEST(Overloads, AdditionMulMatrixOperator) {
  auto A = S21Matrix(3, 3);
  auto B = S21Matrix(3, 3);
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

  A *= B;
  auto check_matrix = S21Matrix(3, 3);
  check_matrix(0, 0) = 30;
  check_matrix(0, 1) = 36;
  check_matrix(0, 2) = 42;
  check_matrix(1, 0) = 66;
  check_matrix(1, 1) = 81;
  check_matrix(1, 2) = 96;
  check_matrix(2, 0) = 102;
  check_matrix(2, 1) = 126;
  check_matrix(2, 2) = 150;
  EXPECT_EQ(A, check_matrix);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
