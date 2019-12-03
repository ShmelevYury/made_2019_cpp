#ifndef VECTOR_08_VECTOR_H
#define VECTOR_08_VECTOR_H

#include "Allocator.h"
#include "Iterator.h"

#include <stdexcept>

template <class T, class Alloc = Allocator<T>>
class Vector {
 public:
  using iterator = Iterator<T>;
  using reversed_iterator = ReversedIterator<T>;
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  Vector()
      : begin_(nullptr), end_(nullptr), capacity_(nullptr), alloc_(Alloc()) {}

  ~Vector() { alloc_.deallocate(begin_, capacity()); }

  Vector(const Vector& other)
      : begin_(new T[other.capacity()]),
        end_(begin_ + other.size()),
        capacity_(begin_ + other.capacity()),
        alloc_(other.alloc_) {
    std::copy(other.begin_, other.end_, begin_);
  }

  Vector(Vector&& other) noexcept
      : begin_(other.begin_),
        end_(other.end_),
        capacity_(other.capacity_),
        alloc_(other.alloc_) {
    other.begin_ = nullptr;
    other.end_ = nullptr;
    other.capacity_ = nullptr;
  }

  Vector& operator=(const Vector& other) {
    if (this == &other) {
      return *this;
    }
    pointer ptr = alloc_.allocate(other.size());
    alloc_.deallocate(begin_, capacity());
    begin_ = ptr;
    end_ = other.begin_ + other.size();
    capacity_ = other.begin_ + other.capacity();
    alloc_ = other.alloc_;
    std::copy(other.begin_, other.end(), begin_);
    return *this;
  }

  Vector& operator=(Vector&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    alloc_.deallocate(begin_, capacity());
    begin_ = other.begin_;
    end_ = other.end_;
    capacity_ = other.capacity_;
    alloc_ = other.alloc_;
    other.begin_ = nullptr;
    other.end_ = nullptr;
    other.capacity_ = nullptr;
    return *this;
  }

  reference operator[](size_type pos) { return *(begin_ + pos); }

  const_reference operator[](size_type pos) const { return *(begin_ + pos); }

  void push_back(const_reference val) {
    if (end_ == capacity_) {
      size_t cap = empty() ? 1 : 2 * capacity();
      Reallocate(cap);
    }
    *end_ = val;
    ++end_;
  }

  void pop() {
    if (begin_ != end_) {
      --end_;
    }
  }

  bool empty() const { return !begin_ || (end_ == begin_); }

  void clear() { end_ = begin_; }

  iterator begin() { return iterator(begin_); }

  iterator end() { return iterator(end_); }

  reversed_iterator rbegin() { return reversed_iterator(end_ - 1); }

  reversed_iterator rend() { return reversed_iterator(begin_ - 1); }

  void resize(size_type new_size) {
    if (!begin_ || begin_ + new_size >= capacity_) {
      Reallocate(new_size);
    }
    end_ = begin_ + new_size;
  }

  void reserve(size_type new_capacity) {
    if (new_capacity > capacity()) {
      Reallocate(new_capacity);
    }
  }

  size_type size() const { return begin_ ? (end_ - begin_) : 0; }

  size_type capacity() const { return begin_ ? (capacity_ - begin_) : 0; }

 private:
  void Reallocate(size_type cap) {
    auto new_begin = alloc_.allocate(cap);
    for (size_t i = 0; i < size(); ++i) {
      *(new_begin + i) = std::move(*(begin_ + i));
    }
    size_t new_size = size();
    alloc_.deallocate(begin_, capacity());
    begin_ = new_begin;
    end_ = new_begin + new_size;
    capacity_ = new_begin + cap;
  }

  T* begin_;
  T* end_;
  T* capacity_;
  Alloc alloc_;
};

#endif  // VECTOR_08_VECTOR_H
