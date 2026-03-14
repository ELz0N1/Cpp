#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class MatrixRow {
  friend class SquareMatrix;
  std::vector<double> row_;

 public:
  MatrixRow(size_t size) : row_(size) {}
  MatrixRow(const MatrixRow& other) = default;
  double& operator[](size_t index) { return row_[index]; }
  const double& operator[](size_t index) const { return row_[index]; }
};

class SquareMatrix {
  std::vector<MatrixRow> matrix_rows_;

 public:
  SquareMatrix();
  SquareMatrix(size_t size);
  SquareMatrix(std::vector<double> vec);
  SquareMatrix(const SquareMatrix& other) = default;
  SquareMatrix(SquareMatrix&& other) = default;

  SquareMatrix& operator=(SquareMatrix other);
  ~SquareMatrix() = default;

  MatrixRow& operator[](size_t row);
  operator double() const;

  SquareMatrix operator+(const SquareMatrix& other);
  SquareMatrix operator+=(const SquareMatrix& other);
  SquareMatrix operator*(const SquareMatrix& other);
  SquareMatrix operator*(int scalar);
  SquareMatrix operator*=(const SquareMatrix& other);
  SquareMatrix operator*=(int scalar);
  bool operator==(const SquareMatrix& other);
  bool operator!=(const SquareMatrix& other);
};

#endif