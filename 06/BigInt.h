#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

#include "DynArr.h"

#include <exception>
#include <iostream>
#include <vector>

class BigInt {
 public:
  BigInt();

  BigInt(int num);

  BigInt(const BigInt& rhs) = default;

  BigInt(BigInt&& rhs) = default;

  BigInt& operator=(const BigInt& rhs) = default;

  BigInt& operator=(BigInt&& rhs) = default;

  BigInt operator+(const BigInt& rhs) const;

  BigInt operator-(const BigInt& rhs) const;

  BigInt operator-() const;

  bool operator<(const BigInt& rhs) const;

  bool operator>(const BigInt& rhs) const;

  bool operator==(const BigInt& rhs) const;

  bool operator<=(const BigInt& rhs) const;

  bool operator>=(const BigInt& rhs) const;

  friend std::ostream& operator<<(std::ostream& out, const BigInt& rhs);

  using NumArr = DynArr<short>;

 private:
  NumArr num_;
  bool is_positive_;
};

BigInt operator+(int num, const BigInt& rhs);

BigInt operator-(int num, const BigInt& rhs);

bool operator<(int num, const BigInt& rhs);

bool operator>(int num, const BigInt& rhs);

bool operator==(int num, const BigInt& rhs);

bool operator<=(int num, const BigInt& rhs);

bool operator>=(int num, const BigInt& rhs);

#endif  // BIGINT_BIGINT_H
