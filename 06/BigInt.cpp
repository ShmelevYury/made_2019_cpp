#include "BigInt.h"

namespace {
BigInt::NumArr SumArr(const BigInt::NumArr& lhs, const BigInt::NumArr& rhs) {
  const BigInt::NumArr& short_arr = (lhs.Size() < rhs.Size()) ? lhs : rhs;
  const BigInt::NumArr& longest_arr = (lhs.Size() < rhs.Size()) ? rhs : lhs;
  BigInt::NumArr sum;
  short hyp = 0;
  for (size_t i = 0; i < short_arr.Size(); ++i) {
    short sum_num = lhs[i] + rhs[i] + hyp;
    hyp = (sum_num > 9) ? 1 : 0;
    sum_num %= 10;
    sum.Push(sum_num);
  }
  for (size_t i = short_arr.Size(); i < longest_arr.Size(); ++i) {
    short sum_num = longest_arr[i] + hyp;
    hyp = (sum_num > 9) ? 1 : 0;
    sum_num %= 10;
    sum.Push(sum_num);
  }
  if (hyp) {
    sum.Push(hyp);
  }
  return sum;
}

BigInt::NumArr DiffArr(const BigInt::NumArr& long_arr,
                       const BigInt::NumArr& short_arr) {
  if (long_arr.Size() < short_arr.Size()) {
    throw std::runtime_error{
        "Wrong parameters of func Diff! Left smaller than right!"};
  }
  BigInt::NumArr diff;
  short hyp = 0;
  for (size_t i = 0; i < short_arr.Size(); ++i) {
    short diff_num = long_arr[i] - short_arr[i] + hyp;
    hyp = (diff_num < 0) ? -1 : 0;
    diff_num = (diff_num + 10) % 10;
    diff.Push(diff_num);
  }
  for (size_t i = short_arr.Size(); i < long_arr.Size(); ++i) {
    short diff_num = long_arr[i] + hyp;
    hyp = (diff_num < 0) ? -1 : 0;
    diff_num = (diff_num + 10) % 10;
    diff.Push(diff_num);
  }
  if (hyp == -1) {
    throw std::runtime_error{
        "Wrong parameters of func Diff! Left smaller than right!"};
  }
  while (diff.Back() == 0 && diff.Size() > 1) {
    diff.Pop();
  }
  return diff;
}

bool IsSmaller(const BigInt::NumArr& lhs, const BigInt::NumArr& rhs) {
  if (lhs.Size() < rhs.Size()) {
    return true;
  } else if (lhs.Size() > rhs.Size()) {
    return false;
  }
  for (size_t i = lhs.Size() - 1; i != 0; --i) {
    if (lhs[i] < rhs[i]) {
      return true;
    } else if (lhs[i] > rhs[i]) {
      return false;
    }
  }
  return lhs[0] < rhs[0];
}

bool IsBigger(const BigInt::NumArr& lhs, const BigInt::NumArr& rhs) {
  if (lhs.Size() > rhs.Size()) {
    return true;
  } else if (lhs.Size() < rhs.Size()) {
    return false;
  }
  for (size_t i = lhs.Size() - 1; i != 0; --i) {
    if (lhs[i] > rhs[i]) {
      return true;
    } else if (lhs[i] < rhs[i]) {
      return false;
    }
  }
  return lhs[0] > rhs[0];
}
}  // unnamed namespace

BigInt::BigInt() : is_positive_(true) {}

BigInt::BigInt(int num) {
  if (num < 0) {
    is_positive_ = false;
    num *= -1;
  } else {
    is_positive_ = true;
  }
  if (num == 0) {
    num_.Push(0);
  }
  while (num) {
    num_.Push(num % 10);
    num /= 10;
  }
}

BigInt BigInt::operator+(const BigInt& rhs) const {
  BigInt sum(0);
  if (is_positive_ == rhs.is_positive_) {
    sum.num_ = SumArr(num_, rhs.num_);
    if (!(is_positive_ || rhs.is_positive_)) {
      sum.is_positive_ = false;
    }
  } else {
    if (IsSmaller(num_, rhs.num_)) {
      sum.num_ = DiffArr(rhs.num_, num_);
      sum.is_positive_ = !is_positive_;
    } else {
      sum.num_ = DiffArr(num_, rhs.num_);
      sum.is_positive_ = is_positive_;
    }
  }
  return sum;
}

BigInt BigInt::operator-() const {
  BigInt unary_minus(*this);
  unary_minus.is_positive_ = !is_positive_;
  return unary_minus;
}

BigInt BigInt::operator-(const BigInt& rhs) const {
  BigInt unary_minus_rhs(rhs);
  unary_minus_rhs.is_positive_ = !unary_minus_rhs.is_positive_;
  return *this + unary_minus_rhs;
}

bool BigInt::operator<(const BigInt& rhs) const {
  if (is_positive_ == rhs.is_positive_) {
    bool answ = IsSmaller(num_, rhs.num_);
    if (!(is_positive_ || rhs.is_positive_)) {
      answ = !answ;
    }
    return answ;
  }
  return !is_positive_;
}

bool BigInt::operator>(const BigInt& rhs) const {
  if (is_positive_ == rhs.is_positive_) {
    bool answ = IsBigger(num_, rhs.num_);
    if (!(is_positive_ || rhs.is_positive_)) {
      answ = !answ;
    }
    return answ;
  }
  return is_positive_;
}

bool BigInt::operator==(const BigInt& rhs) const {
  if (num_.Size() != rhs.num_.Size() || (is_positive_ != rhs.is_positive_)) {
    return false;
  }
  for (size_t i = num_.Size() - 1; i != 0; --i) {
    if (num_[i] != rhs.num_[i]) {
      return false;
    }
  }
  return num_[0] == rhs.num_[0];
}

bool BigInt::operator<=(const BigInt& rhs) const { return !(*this > rhs); }

bool BigInt::operator>=(const BigInt& rhs) const { return !(*this < rhs); }

std::ostream& operator<<(std::ostream& os, const BigInt& number) {
  if (!number.is_positive_) {
    os << '-';
  }
  for (size_t i = number.num_.Size() - 1; i != 0; --i) {
    os << number.num_[i];
  }
  os << number.num_[0];
  return os;
}

BigInt operator+(int num, const BigInt& rhs) { return BigInt(num) + rhs; }

BigInt operator-(int num, const BigInt& rhs) { return BigInt(num) - rhs; }

bool operator<(int num, const BigInt& rhs) { return BigInt(num) < rhs; }

bool operator>(int num, const BigInt& rhs) { return BigInt(num) > rhs; }

bool operator==(int num, const BigInt& rhs) { return BigInt(num) == rhs; }

bool operator<=(int num, const BigInt& rhs) { return BigInt(num) <= rhs; }

bool operator>=(int num, const BigInt& rhs) { return BigInt(num) >= rhs; }
