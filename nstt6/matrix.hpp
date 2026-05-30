#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class SquareMatrix {
  std::vector<double> data_;
  size_t size_ = 0;

 public:
  SquareMatrix();
  SquareMatrix(size_t size);
  SquareMatrix(std::vector<double> vec);
  SquareMatrix(const SquareMatrix& other) = default;
  SquareMatrix(SquareMatrix&& other) = default;

  SquareMatrix& operator=(SquareMatrix other);
  ~SquareMatrix() = default;

  double* operator[](size_t row);
  const double* operator[](size_t row) const;
  size_t size() const { return size_; }
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