   #include "s21_matrix.hpp"

    int S21Matrix::GetRows() const{ return rows_;}
    int S21Matrix::GetCols() const { return cols_;}


/*

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = FAILURE;
  if (check_matrix(A) && check_matrix(B)) {
    if (A->columns == B->columns && A->rows == B->rows) {
      res = SUCCESS;
      eq_value(A, B, &res);
    }
  }
  return res;
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void eq_value(matrix_t *A, matrix_t *B, int *res) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1.e-7) {
        *res = FAILURE;
      }
    }
  }
}
*/