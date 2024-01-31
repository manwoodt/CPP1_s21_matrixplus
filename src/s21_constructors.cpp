#include "s21_matrix.hpp"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr){};

// Параметризированный конструктор с количеством строк и столбцов
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  // Выделение памяти для матрицы
  matrix_ = new double[rows_ * cols_];
};

// почему здесь тоже не можем matrix_(other.matrix_)
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(new double[rows_ * cols_]) {
  std::memcpy(matrix_, other.matrix_,
              other.rows_ * other.cols_ * sizeof(double));
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  // Освобождение памяти, выделенной для матрицы
  if (matrix_ != nullptr) delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
}
