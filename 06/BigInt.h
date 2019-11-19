#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

#include <exception>
#include <iostream>
#include <vector>

template <class T>
class DynArr {
 public:
  DynArr() : begin_(nullptr), end_(nullptr), capacity_(nullptr) {}

  ~DynArr() { delete[] begin_; }

  DynArr(const DynArr &rhs)
      : begin_(new T[rhs.capacity_ - rhs.begin_]),
        end_(begin_ + (rhs.end_ - rhs.begin_)),
        capacity_(begin_ + (rhs.capacity_ - rhs.begin_)) {
    for (int i = 0; i < rhs.Size(); ++i) {
      begin_[i] = rhs.begin_[i];
    }
  }

  DynArr(DynArr&& rhs) noexcept
      : begin_(rhs.begin_), end_(rhs.end_), capacity_(rhs.capacity_) {
    rhs.begin_ = nullptr;
    rhs.end_ = nullptr;
    rhs.capacity_ = nullptr;
  }

  DynArr& operator=(const DynArr& rhs) {
    if (this == &rhs) {
      return *this;
    }
    T* ptr = new T[rhs.Size()];
    delete[] begin_;
    begin_ = ptr;
    end_ = rhs.begin_ + (rhs.end_ - rhs.begin_);
    capacity_ = rhs.begin_ + (rhs.capacity_ - rhs.begin_);
    std::copy(rhs.begin_, rhs.begin_ + rhs.Size(), begin_);
    return *this;
  }

  DynArr& operator=(DynArr&& rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }
    delete[] begin_;
    begin_ = rhs.begin_;
    end_ = rhs.end_;
    capacity_ = rhs.capacity_;
    rhs.begin_ = nullptr;
    rhs.end_ = nullptr;
    rhs.capacity_ = nullptr;
    return *this;
  }

  void Push(const T& val) {
    if (end_ == capacity_) {
      size_t cap = DynArr::IsEmpty() ? 1 : 2 * (capacity_ - begin_);
      DynArr::Reallocate(cap);
    }
    *end_ = val;
    ++end_;
  }

  void Pop() {
    if (begin_ == end_) {
      throw std::out_of_range{"Can't pop from empty array!"};
    }
    --end_;
  }

  T& operator[](size_t pos) {
    if (!begin_ || begin_ + pos >= end_) {
      throw std::out_of_range{"Out of range!"};
    }
    return *(begin_ + pos);
  }

  const T& operator[](size_t pos) const {
    if (!begin_ || begin_ + pos >= end_) {
      throw std::out_of_range{"Out of range!"};
    }
    return *(begin_ + pos);
  }

  T& Top() {
    if (DynArr::IsEmpty()) {
      throw std::out_of_range{"Out of range!"};
    }
    return *(end_ - 1);
  }

  [[nodiscard]] const T& Top() const {
    if (DynArr::IsEmpty()) {
      throw std::out_of_range{"Out of range!"};
    }
    return *(end_ - 1);
  }

  [[nodiscard]] size_t Size() const {
    return begin_ ? (end_ - begin_) : 0;
  }

  [[nodiscard]] bool IsEmpty() const { return !begin_ || (end_ == begin_); }

 private:
  void Reallocate(int cap) {
    auto new_begin = new T[cap];
    for (size_t i = 0; i < DynArr::Size(); ++i) {
      *(new_begin + i) = *(begin_ + i);
    }
    size_t size = DynArr::Size();
    delete[] begin_;
    begin_ = new_begin;
    end_ = new_begin + size;
    capacity_ = new_begin + cap;
  }

  T* begin_;
  T* end_;
  T* capacity_;
};

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

 private:
  DynArr<short> num_;
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
