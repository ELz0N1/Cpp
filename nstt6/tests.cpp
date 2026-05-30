#include <gtest/gtest.h>

#include "matrix.cpp"

TEST(MatrixTest, Test_Ctor_Vec) {
  std::vector<double> vec{1.0, 2.0, 3.0, 4.0};
  SquareMatrix matrix(vec);

  EXPECT_EQ(matrix[0][2], 0);

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(matrix[i][i], vec[i]);
  }
}

TEST(MatrixTest, Test_Ctor_Matrix) {
  SquareMatrix matrix1({1.0, 2.0, 3.0, 4.0});
  SquareMatrix matrix2 = matrix1;

  EXPECT_EQ(matrix1, matrix2);

  SquareMatrix matrix3(matrix2);

  EXPECT_EQ(matrix1, matrix3);
}

TEST(MatrixTest, Test_Sum) {
  SquareMatrix expected({3.0, 5.0, 7.0, 9.0});

  SquareMatrix matrix1({1.0, 2.0, 3.0, 4.0});
  SquareMatrix matrix2({2.0, 3.0, 4.0, 5.0});
  SquareMatrix result = matrix1 + matrix2;

  EXPECT_EQ(result, expected);
}

TEST(MatrixTest, Test_SumEq) {
  SquareMatrix expected({3.0, 5.0, 7.0, 9.0});

  SquareMatrix matrix1({1.0, 2.0, 3.0, 4.0});
  SquareMatrix matrix2({2.0, 3.0, 4.0, 5.0});
  SquareMatrix result = matrix1;

  result += matrix2;

  EXPECT_EQ(result, expected);
}
TEST(MatrixTest, Test_Prod) {
  SquareMatrix expected({2.0, 6.0, 12.0, 20.0});

  SquareMatrix matrix1({1.0, 2.0, 3.0, 4.0});
  SquareMatrix matrix2({2.0, 3.0, 4.0, 5.0});
  SquareMatrix result = matrix1 * matrix2;

  EXPECT_EQ(result, expected);
}

TEST(MatrixTest, Test_ProdEq) {
  SquareMatrix expected({2.0, 6.0, 12.0, 20.0});

  SquareMatrix matrix1({1.0, 2.0, 3.0, 4.0});
  SquareMatrix matrix2({2.0, 3.0, 4.0, 5.0});
  SquareMatrix result = matrix1;

  result *= matrix2;

  EXPECT_EQ(result, expected);
}

TEST(MatrixTest, Test_Prod_Scalar) {
  SquareMatrix expected({2.0, 4.0, 6.0, 8.0});

  SquareMatrix matrix1({1.0, 2.0, 3.0, 4.0});
  SquareMatrix result = matrix1 * 2;

  EXPECT_EQ(result, expected);
}

TEST(MatrixTest, Test_ProdEq_Scalar) {
  SquareMatrix expected({2.0, 4.0, 6.0, 8.0});

  SquareMatrix matrix1({1.0, 2.0, 3.0, 4.0});
  SquareMatrix result = matrix1;

  result *= 2;

  EXPECT_EQ(result, expected);
}

TEST(MatrixTest, Test_Eq) {
  SquareMatrix matrix1({1.0, 2.0, 3.0, 4.0});
  SquareMatrix matrix2({1.0, 2.0, 3.0, 4.0});
  SquareMatrix matrix3({4.0, 9.0, 2.0, 1.0});

  EXPECT_TRUE(matrix1 == matrix2);
  EXPECT_FALSE(matrix1 == matrix3);
}

TEST(MatrixTest, Test_NotEq) {
  SquareMatrix matrix1({1.0, 2.0, 3.0, 4.0});
  SquareMatrix matrix2({1.0, 2.0, 3.0, 4.0});
  SquareMatrix matrix3({4.0, 9.0, 2.0, 1.0});

  EXPECT_TRUE(matrix1 != matrix3);
  EXPECT_FALSE(matrix1 != matrix2);
}

TEST(MatrixTest, Test_Indexing1) {
  SquareMatrix matrix({1.0, 2.0, 3.0, 4.0});

  EXPECT_EQ(matrix[0][0], 1.0);
  EXPECT_EQ(matrix[1][1], 2.0);
  EXPECT_EQ(matrix[2][2], 3.0);
  EXPECT_EQ(matrix[3][3], 4.0);
}

TEST(MatrixTest, Test_Indexing2) {
  SquareMatrix matrix(9);

  double value = 1.0;
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      matrix[i][j] = value;
      value += 1.0;
    }
  }

  EXPECT_EQ(matrix[0][0], 1.0);
  EXPECT_EQ(matrix[0][1], 2.0);
  EXPECT_EQ(matrix[0][2], 3.0);

  EXPECT_EQ(matrix[1][0], 4.0);
  EXPECT_EQ(matrix[1][1], 5.0);
  EXPECT_EQ(matrix[1][2], 6.0);

  EXPECT_EQ(matrix[2][0], 7.0);
  EXPECT_EQ(matrix[2][1], 8.0);
  EXPECT_EQ(matrix[2][2], 9.0);

  matrix[1][0] = 6.7;
  EXPECT_EQ(matrix[1][0], 6.7);
}
