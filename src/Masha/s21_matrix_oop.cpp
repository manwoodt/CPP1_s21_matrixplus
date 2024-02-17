// & - lvalue, && - rvalue
#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

// Параметризированный конструктор с количеством строк и столбцов
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  // Выделение памяти для матрицы
  matrix_ = new double[rows_ * cols_];
}

// конструктор копирования
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(new double[rows_ * cols_]) {
  std::memcpy(matrix_, other.matrix_,
              other.rows_ * other.cols_ * sizeof(double));
}
// конструктор перемещения
S21Matrix::S21Matrix(S21Matrix &&other) noexcept : rows_(other.rows_),
                                                   cols_(other.cols_),
                                                   matrix_(other.matrix_) {
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
  if (this == &other) {
    return *this;
  }
  // Освобождаем старые ресурсы
  delete[] matrix_;
  // Копируем данные из other
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double[rows_ * cols_];
  std::copy(other.matrix_, other.matrix_ + (rows_ * cols_), matrix_);
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

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(const int new_rows) {
  if (new_rows <= 0) throw std::length_error("New rows are not suitable");
  if (new_rows != rows_) {
    S21Matrix tmp(new_rows, cols_);
    for (int i = 0; i < (rows_ < new_rows ? rows_ : new_rows); ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}

void S21Matrix::SetCols(const int new_cols) {
  if (new_cols <= 0) throw std::length_error("New cols are not suitable");

  S21Matrix tmp(rows_, new_cols);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < (cols_ < new_cols ? cols_ : new_cols); ++j)
      tmp(i, j) = (*this)(i, j);

  *this = std::move(tmp);
}

int S21Matrix::GetSize() const { return rows_ * cols_; }

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (int i = 0; i < GetSize(); i++) {
    if (fabs(matrix_[i] - other.matrix_[i]) > 1e-5) {
      return false;
    }
  }

  return true;
}

/*
bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::abs(other(i, j) - (*this)(i, j)) > 1e-7) {
        return false;
      }
    }
  }

  return true;
}
*/

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("The dimensions of the matrix are not equal");
  for (int i = 0; i < GetSize(); i++) {
    matrix_[i] += other.matrix_[i];
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("The dimensions of the matrix are not equal");
  for (int i = 0; i < GetSize(); i++) {
    matrix_[i] -= other.matrix_[i];
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < GetSize(); i++) {
    matrix_[i] *= num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (rows_ != other.cols_ || cols_ != other.rows_)
    throw std::out_of_range(
        "The dimensions of the matrix are not for multiplication");
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(result);
}

void S21Matrix::PrintMatrix() const {
  std::cout << "Matrix " << rows_ << "x" << cols_ << ":\n";

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      // Используем std::setw для выравнивания элементов
      std::cout << std::setw(3) << (*this)(i, j) << " ";
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Incorrect input, index is out of range");

  return matrix_[row * cols_ + col];
}

double &S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Incorrect input, index is out of range");

  return matrix_[row * cols_ + col];
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}
S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}
S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result(i, j) = (*this)(j, i);
    }
  }
  return result;
}

S21Matrix S21Matrix::Find_minor(int row, int col) const {
  if (rows_ != cols_) {
    throw std::logic_error(
        "Minor matrix could be computed only for square matrices");
  }
  if (rows_ < 2 || cols_ < 2)
    throw std::logic_error("Matrix is too small for finding minor");

  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Incorrect input, index of minor is out of range");

  S21Matrix Minor(rows_ - 1, cols_ - 1);

  for (int i = 0, minor_i = 0; i < rows_; ++i) {
    if (i == row) continue;
    int minor_j = 0;
    for (int j = 0; j < cols_; ++j) {
      if (j == col) continue;
      Minor(minor_i, minor_j) = (*this)(i, j);
      ++minor_j;
    }
    ++minor_i;
  }

  return Minor;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error("Matrix is not square, determinant is unavailable");
  }

  if (rows_ == 1) return matrix_[0];
  // if (rows_ == 2) return matrix_[0] * matrix_[4] - matrix_[1] * matrix_[3];
  double det = 0;
  int sign = 1;

  for (int j = 0; j < cols_; j++) {
    S21Matrix Minor = Find_minor(0, j);
    det += sign * (*this)(0, j) * Minor.Determinant();
    sign *= -1;
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error(
        "Matrix is not square, CalcComplements is unavailable");
  }

  S21Matrix result(rows_, cols_);
  double det = 0.;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix Minor = Find_minor(i, j);
      det = Minor.Determinant();
      result(i, j) = det * pow(-1, (i + j));
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) throw std::invalid_argument("Matrix is not square");
  double determinant = Determinant();
  if (determinant == 0)
    throw std::invalid_argument(
        "Determinant is zero, InverseMatrix is unavailable");

  // Получаем транспонированную матрицу алгебраических дополнений
  S21Matrix adjoint(rows_, cols_);
  adjoint = CalcComplements();
  adjoint = adjoint.Transpose();

  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(i, j) = (1 / determinant) * adjoint(i, j);
    }
  }
  return result;
}
