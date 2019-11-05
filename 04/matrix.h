#ifndef MATRIX_04_MATRIX_H
#define MATRIX_04_MATRIX_H

#include <vector>

class Row {
 public:
  explicit Row(std::vector<int> row);

  int& operator[](size_t column);

  int operator[](size_t column) const;

  std::vector<int> proxy_row;
};

class Matrix {
 public:
  Matrix() = delete;

  Matrix(size_t rows, size_t columns);

  Matrix(const Matrix& rhs) = default;

  Matrix(Matrix&& rhs) = default;

  size_t GetRowsNum() const;

  size_t GetColumnsNum() const;

  Row& operator[](size_t row);

  const Row& operator[](size_t row) const;

  Matrix& operator*=(int num);

  bool operator==(const Matrix& rhs) const;

  bool operator!=(const Matrix& rhs) const;

 private:
  std::vector<Row> data_;
  const size_t kRows_;
  const size_t kColumns_;
};

#endif  //  MATRIX_04_MATRIX_H
