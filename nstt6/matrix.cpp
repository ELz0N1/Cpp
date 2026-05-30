#include "matrix.hpp"

#include <stdexcept>

SquareMatrix::SquareMatrix() : SquareMatrix(0) {}

SquareMatrix::SquareMatrix(size_t size)
    : size_(size), data_(size * size, 0.0) {}

SquareMatrix::SquareMatrix(std::vector<double> vec) : SquareMatrix(vec.size()) {
  for (size_t i = 0; i < vec.size(); ++i) {
    (*this)[i][i] = vec[i];
  }
}

SquareMatrix& SquareMatrix::operator=(SquareMatrix other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  return *this;
}

double* SquareMatrix::operator[](size_t row) {
  return data_.data() + (row * size_);
}

const double* SquareMatrix::operator[](size_t row) const {
  return data_.data() + (row * size_);
}

SquareMatrix::operator double() const {
  double sum = 0;
  for (size_t i = 0; i < data_.size(); ++i) {
    sum += (*this)[i][i];
  }
  return sum;
}

SquareMatrix SquareMatrix::operator+(const SquareMatrix& other) {
  SquareMatrix result = *this;
  result += other;
  return result;
}

SquareMatrix SquareMatrix::operator+=(const SquareMatrix& other) {
  if (size_ != other.size_) {
    throw std::invalid_argument("Matrices are not the same size!");
  }

  for (size_t i = 0; i < data_.size(); ++i) {
    data_[i] += other.data_[i];
  }

  return *this;
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix& other) {
  SquareMatrix result = *this;
  result *= other;
  return result;
}

SquareMatrix SquareMatrix::operator*(int scalar) {
  SquareMatrix result = *this;
  result *= scalar;
  return result;
}

SquareMatrix SquareMatrix::operator*=(const SquareMatrix& other) {
  if (size_ != other.size_) {
    throw std::invalid_argument("Matrices are not the same size!");
  }

  SquareMatrix tmp(size_);

  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      for (size_t k = 0; k < size_; ++k) {
        tmp[i][j] += (*this)[i][k] * other[k][j];
      }
    }
  }

  *this = tmp;
  return *this;
}

SquareMatrix SquareMatrix::operator*=(int scalar) {
  for (size_t i = 0; i < data_.size(); ++i) {
    data_[i] *= scalar;
  }

  return *this;
}

bool SquareMatrix::operator==(const SquareMatrix& other) {
  if (size_ != other.size_) {
    return false;
  }

  return data_ == other.data_;
}

bool SquareMatrix::operator!=(const SquareMatrix& other) {
  return !(*this == other);
}
