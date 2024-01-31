#include "s21_matrix.hpp"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr){};

// Параметризированный конструктор с количеством строк и столбцов
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  // Выделение памяти для матрицы
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];


    // Заполняем матрицу нулями
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = 0.0;
    }
  }
};


S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_){

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }
}

/*
S21Matrix(S21Matrix &&other);S
*/
S21Matrix::~S21Matrix() {
  // Освобождение памяти, выделенной для матрицы
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}
