#define CATCH_CONFIG_MAIN

#include "matrix.h"
#include "catch2/catch.hpp"

#include <stdexcept>

using MatrixVec = std::vector<std::vector<int>>;

void FillMatrixByVec(const MatrixVec& vector, Matrix& matrix) {
  if (vector.size() != matrix.GetRowsNum()) {
    throw std::runtime_error("Vector size and number of rows don't match.");
  }
  for (size_t row = 0; row < matrix.GetRowsNum(); ++row) {
    if (vector[row].size() != matrix.GetColumnsNum()) {
      throw std::runtime_error(
          "Vector size and number of columns don't match.");
    }
    for (size_t column = 0; column < matrix.GetColumnsNum(); ++column) {
      matrix[row][column] = vector[row][column];
    }
  }
}

bool CompareMatrixAndVec(const MatrixVec& vector, const Matrix& matrix) {
  if (vector.size() != matrix.GetRowsNum()) {
    return false;
  }
  for (size_t row = 0; row < matrix.GetRowsNum(); ++row) {
    if (vector[row].size() != matrix.GetColumnsNum()) {
      return false;
    }
    for (size_t column = 0; column < matrix.GetColumnsNum(); ++column) {
      if (matrix[row][column] != vector[row][column]) {
        return false;
      }
    }
  }
  return true;
}

TEST_CASE("Test GetRowsNum and GetColumnsNum") {
  Matrix matrix_5x6(5, 6);
  REQUIRE(matrix_5x6.GetRowsNum() == 5);
  REQUIRE(matrix_5x6.GetColumnsNum() == 6);
  Matrix matrix_3x3(3, 3);
  REQUIRE(matrix_3x3.GetRowsNum() == 3);
  REQUIRE(matrix_3x3.GetColumnsNum() == 3);
  Matrix matrix_100x15(105, 15);
  REQUIRE(matrix_100x15.GetRowsNum() == 105);
  REQUIRE(matrix_100x15.GetColumnsNum() == 15);
}

TEST_CASE("Create empty matrix") {
  Matrix empty(0, 0);
  REQUIRE(empty.GetRowsNum() == 0);
  REQUIRE(empty.GetColumnsNum() == 0);
  REQUIRE_THROWS(empty[0][0]);
}

TEST_CASE("Test operator[][]") {
  Matrix ones_matrix_3x3(3, 3);
  REQUIRE(ones_matrix_3x3.GetColumnsNum() == 3);
  REQUIRE(ones_matrix_3x3.GetRowsNum() == 3);
  MatrixVec ones_vec{std::vector<int>{1, 1, 1},
                     std::vector<int>{1, 1, 1},
                     std::vector<int>{1, 1, 1}};
  FillMatrixByVec(ones_vec, ones_matrix_3x3);
  REQUIRE(CompareMatrixAndVec(ones_vec, ones_matrix_3x3));
  ones_matrix_3x3[1][1] = 5;
  ones_vec[1][1] = 5;
  REQUIRE(CompareMatrixAndVec(ones_vec, ones_matrix_3x3));
  ones_matrix_3x3[0][1] = 5;
  ones_vec[0][1] = 5;
  REQUIRE(CompareMatrixAndVec(ones_vec, ones_matrix_3x3));
  REQUIRE_THROWS(ones_matrix_3x3[3][0]);
  REQUIRE_THROWS(ones_matrix_3x3[0][3]);
  REQUIRE_THROWS(ones_matrix_3x3[3][3]);
}

TEST_CASE("Test operator[][] for non-squared matrix") {
  Matrix ones_matrix_2x4(2, 4);
  REQUIRE(ones_matrix_2x4.GetColumnsNum() == 4);
  REQUIRE(ones_matrix_2x4.GetRowsNum() == 2);
  MatrixVec ones_vec{std::vector<int>{1, 1, 1, 1},
                     std::vector<int>{1, 1, 1, 1}};
  FillMatrixByVec(ones_vec, ones_matrix_2x4);
  REQUIRE(CompareMatrixAndVec(ones_vec, ones_matrix_2x4));
  ones_matrix_2x4[1][3] = 5;
  ones_vec[1][3] = 5;
  REQUIRE(CompareMatrixAndVec(ones_vec, ones_matrix_2x4));
  ones_matrix_2x4[0][2] = 5;
  ones_vec[0][2] = 5;
  REQUIRE(CompareMatrixAndVec(ones_vec, ones_matrix_2x4));
  REQUIRE_THROWS(ones_matrix_2x4[2][0]);
  REQUIRE_THROWS(ones_matrix_2x4[0][4]);
  REQUIRE_THROWS(ones_matrix_2x4[2][4]);
}

TEST_CASE("Test operators == and !=") {
  Matrix first_ones_matrix_2x2(2, 2);
  FillMatrixByVec(MatrixVec{std::vector<int>{1, 1},
                            std::vector<int>{1, 1}}, first_ones_matrix_2x2);
  Matrix second_ones_matrix_2x2(2, 2);
  FillMatrixByVec(MatrixVec{std::vector<int>{1, 1},
                            std::vector<int>{1, 1}}, second_ones_matrix_2x2);
  REQUIRE(first_ones_matrix_2x2 == second_ones_matrix_2x2);
  REQUIRE(first_ones_matrix_2x2 == first_ones_matrix_2x2);
  Matrix twos_matrix_2x2(2, 2);
  FillMatrixByVec(MatrixVec{std::vector<int>{2, 2},
                            std::vector<int>{2, 2}}, twos_matrix_2x2);
  REQUIRE(first_ones_matrix_2x2 != twos_matrix_2x2);
  Matrix ones_matrix_2x3(2, 3);
  FillMatrixByVec(MatrixVec{std::vector<int>{1, 1, 1},
                            std::vector<int>{1, 1, 1}}, ones_matrix_2x3);
  REQUIRE(first_ones_matrix_2x2 != ones_matrix_2x3);
  Matrix ones_matrix_3x2(3, 2);
  FillMatrixByVec(MatrixVec{std::vector<int>{1, 1},
                            std::vector<int>{1, 1},
                            std::vector<int>{1, 1}}, ones_matrix_3x2);
  REQUIRE(first_ones_matrix_2x2 != ones_matrix_3x2);
}

TEST_CASE("Test operator *= ") {
  Matrix matrix(2, 2);
  FillMatrixByVec(MatrixVec{std::vector<int>{1, 2},
                            std::vector<int>{3, 4}}, matrix);
  Matrix matrix_mul_by2(2, 2);
  FillMatrixByVec(MatrixVec{std::vector<int>{2, 4},
                            std::vector<int>{6, 8}}, matrix_mul_by2);
  matrix *= 2;
  REQUIRE(matrix == matrix_mul_by2);
  Matrix matrix_mul_by6(2, 2);
  FillMatrixByVec(MatrixVec{std::vector<int>{6,  12},
                            std::vector<int>{18, 24}}, matrix_mul_by6);
  Matrix copy = matrix *= 3;
  REQUIRE(matrix == matrix_mul_by6);
  REQUIRE(copy == matrix);
}