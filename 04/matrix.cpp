#include "matrix.h"

#include <stdexcept>

Row::Row(std::vector<int> row) : proxy_row(std::move(row)) {}

int& Row::operator[](size_t column) {
  if (column >= proxy_row.size()) {
    throw std::out_of_range("Out of range! Matrix doesn't have column " +
                            std::to_string(column) + ".");
  }
  return proxy_row[column];
}

int Row::operator[](size_t column) const {
  if (column >= proxy_row.size()) {
    throw std::out_of_range("Out of range! Matrix doesn't have column " +
                            std::to_string(column) + ".");
  }
  return proxy_row[column];
}

Matrix::Matrix(size_t rows, size_t columns)
    : kRows_(rows),
      kColumns_(columns),
      data_(std::vector<Row>(rows, Row(std::vector<int>(columns)))) {}

size_t Matrix::GetRowsNum() const { return kRows_; }

size_t Matrix::GetColumnsNum() const { return kColumns_; }

Row& Matrix::operator[](size_t row) {
  if (row >= kRows_) {
    throw std::out_of_range("Out of range! Matrix doesn't have row " +
                            std::to_string(row) + ".");
  }
  return data_[row];
}

const Row& Matrix::operator[](size_t row) const {
  if (row >= kRows_) {
    throw std::out_of_range("Out of range! Matrix doesn't have row " +
                            std::to_string(row) + ".");
  }
  return data_[row];
}

Matrix& Matrix::operator*=(int num) {
  for (auto& row : data_) {
    for (auto& value : row.proxy_row) {
      value *= num;
    }
  }
  return *this;
}

bool Matrix::operator==(const Matrix& rhs) const {
  if (&rhs == this) {
    return true;
  }
  if (rhs.GetColumnsNum() != kColumns_ || rhs.GetRowsNum() != kRows_) {
    return false;
  }
  for (size_t row = 0; row < kRows_; ++row) {
    for (size_t column = 0; column < kColumns_; ++column) {
      if (data_[row][column] != rhs[row][column]) {
        return false;
      }
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix& rhs) const { return !(*this == rhs); }