#include "matrix.hpp"

#include <stdexcept>

SquareMatrix::SquareMatrix() : SquareMatrix(0) {}

SquareMatrix::SquareMatrix(size_t size) : matrix_rows_(size, MatrixRow(size)) {}

SquareMatrix::SquareMatrix(std::vector<double> vec) : SquareMatrix(vec.size()) {
  for (size_t i = 0; i < vec.size(); ++i) {
    matrix_rows_[i][i] = vec[i];
  }
}

SquareMatrix& SquareMatrix::operator=(SquareMatrix other) {
  std::swap(matrix_rows_, other.matrix_rows_);
  return *this;
}

MatrixRow& SquareMatrix::operator[](size_t row) { return matrix_rows_[row]; }

SquareMatrix::operator double() const {
  double sum = 0;
  for (size_t i = 0; i < matrix_rows_.size(); ++i) {
    sum += matrix_rows_[i].row_[i];
  }
  return sum;
}

SquareMatrix SquareMatrix::operator+(const SquareMatrix& other) {
  if (matrix_rows_.size() != other.matrix_rows_.size()) {
    throw std::invalid_argument("Matrices are not the same size!");
  }
  size_t size = matrix_rows_.size();

  SquareMatrix result(size);
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      result[i].row_[j] =
          matrix_rows_[i].row_[j] + other.matrix_rows_[i].row_[j];
    }
  }

  return result;
}

SquareMatrix SquareMatrix::operator+=(const SquareMatrix& other) {
  if (matrix_rows_.size() != other.matrix_rows_.size()) {
    throw std::invalid_argument("Matrices are not the same size!");
  }

  size_t size = matrix_rows_.size();
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      matrix_rows_[i].row_[j] += other.matrix_rows_[i].row_[j];
    }
  }

  return *this;
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix& other) {
  if (matrix_rows_.size() != other.matrix_rows_.size()) {
    throw std::invalid_argument("Matrices are not the same size!");
  }

  size_t size = matrix_rows_.size();

  SquareMatrix result(size);
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      for (size_t k = 0; k < size; ++k) {
        result[i].row_[j] +=
            matrix_rows_[i].row_[k] * other.matrix_rows_[k].row_[j];
      }
    }
  }
  return result;
}

SquareMatrix SquareMatrix::operator*(int scalar) {
  size_t size = matrix_rows_.size();
  SquareMatrix result(size);

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      result[i].row_[j] = matrix_rows_[i].row_[j] * scalar;
    }
  }

  return result;
}

SquareMatrix SquareMatrix::operator*=(const SquareMatrix& other) {
  if (matrix_rows_.size() != other.matrix_rows_.size()) {
    throw std::invalid_argument("Matrices are not the same size!");
  }

  size_t size = matrix_rows_.size();
  SquareMatrix tmp(size);

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      for (size_t k = 0; k < size; ++k) {
        tmp[i].row_[j] +=
            matrix_rows_[i].row_[k] * other.matrix_rows_[k].row_[j];
      }
    }
  }

  *this = tmp;
  return *this;
}

SquareMatrix SquareMatrix::operator*=(int scalar) {
  size_t size = matrix_rows_.size();

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      matrix_rows_[i].row_[j] *= scalar;
    }
  }

  return *this;
}

bool SquareMatrix::operator==(const SquareMatrix& other) {
  if (matrix_rows_.size() != other.matrix_rows_.size()) {
    return false;
  }

  for (size_t row = 0; row < matrix_rows_.size(); ++row) {
    for (size_t column = 0; column < matrix_rows_.size(); ++column) {
      if (matrix_rows_[row].row_[column] !=
          other.matrix_rows_[row].row_[column]) {
        return false;
      }
    }
  }
  return true;
}

bool SquareMatrix::operator!=(const SquareMatrix& other) {
  return !(*this == other);
}
