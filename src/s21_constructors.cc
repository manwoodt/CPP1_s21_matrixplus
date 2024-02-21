// & - lvalue, && - rvalue
#include "s21_matrix.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

// Параметризированный конструктор с количеством строк и столбцов
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  // Выделение памяти для матрицы
  matrix_ = new double[rows_ * cols_]{};
}

// конструктор копирования
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(new double[rows_ * cols_]) {
  std::memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
}
// конструктор перемещения
S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

// почему возвращает указатель,  если должен ссылку
// Оператор присваивания копированием
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  /*
  Cимвол & перед other используется для получения адреса объекта other. Таким
  образом, &other дает адрес объекта other в памяти. Проверка if (this !=
  &other) сравнивает адреса текущего объекта (указатель this) и объекта other.
  Если адреса не равны, это означает, что мы не пытаемся присвоить объект самому
  себе, и мы можем продолжить копирование данных. Если бы мы просто написали if
  (this != other), это бы означало сравнение значений указателей, что не
  является корректным для объектов C++, так как это сравнило бы содержимое
  адресов памяти, а не сами объекты.*/
  if (this != &other) {
    // Освобождаем старые ресурсы
    delete[] matrix_;
    // Копируем данные из other
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double[rows_ * cols_];
    std::copy(other.matrix_, other.matrix_ + (rows_ * cols_), matrix_);
  }
  return *this;
}

// Оператор присваивания перемещения
S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }

  return *this;
}

S21Matrix::~S21Matrix() {
  // Освобождение памяти, выделенной для матрицы
  if (matrix_ != nullptr) delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
}
