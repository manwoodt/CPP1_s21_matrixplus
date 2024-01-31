#include "s21_matrix.hpp"
int main() {
  S21Matrix A(2, 3);
  S21Matrix B(2, 3);
  A.matrix_[0][0] = -2.0;
  A.matrix_[0][1] = 2.0;
  A.matrix_[0][2] = 4.0;
  A.matrix_[1][0] = -4.0;
  A.matrix_[1][1] = -6.0;
  A.matrix_[1][2] = 7.0;
  B.matrix_[0][0] = -1.9999999425665;
  B.matrix_[0][1] = 2.00000009840676;
  B.matrix_[0][2] = 3.99999991639265;
  B.matrix_[1][0] = -4.0000000294291;
  B.matrix_[1][1] = -5.9999999675878;
  B.matrix_[1][2] = 6.9999999752287;
  int status = EqMatrix(A);
  return 0;
}
