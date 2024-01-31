#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

class S21Matrix
{
private:
    int rows_, cols_;
    double **matrix_; // Pointer to the memory where the matrix is allocated

public:
    S21Matrix();
    S21Matrix(int rows, int cols);
   // S21Matrix(const S21Matrix &other);
   // S21Matrix(S21Matrix &&other) ;
    ~S21Matrix();
    
    int GetCols() const ;
    int GetRows() const;
/*
    void SumMatrix(const S21Matrix &other);
    bool EqMatrix(const S21Matrix &other);
    void SumMatrix(const S21Matrix &other);
    void SubMatrix(const S21Matrix &other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix &other);

    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();

    S21Matrix &operator+=(const S21Matrix &other);
    S21Matrix operator+(const S21Matrix &other) const;
    S21Matrix &operator-=(const S21Matrix &other);
    S21Matrix operator-(const S21Matrix &other) const;
    */
};

#endif // SRC_S21_MATRIX_H_