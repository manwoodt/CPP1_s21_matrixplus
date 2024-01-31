#include "s21_matrix.hpp"
int main() { S21Matrix matr1(2, 3, ) return 0; }

int rows1 = 2, cols1 = 3;
matrix_t A = {0}, B = {0};
s21_create_matrix(rows1, cols1, &A);
s21_create_matrix(rows1, cols1, &B);
A.matrix[0][0] = -2.0;
A.matrix[0][1] = 2.0;
A.matrix[0][2] = 4.0;
A.matrix[1][0] = -4.0;
A.matrix[1][1] = -6.0;
A.matrix[1][2] = 7.0;
B.matrix[0][0] = -1.9999999425665;
B.matrix[0][1] = 2.00000009840676;
B.matrix[0][2] = 3.99999991639265;
B.matrix[1][0] = -4.0000000294291;
B.matrix[1][1] = -5.9999999675878;
B.matrix[1][2] = 6.9999999752287;
int status = s21_eq_matrix(&A, &B);
ck_assert_int_eq(status, 1);
