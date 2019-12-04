#ifndef ITERATOR_08_ITERATOR_H
#define ITERATOR_08_ITERATOR_H

#include <iterator>

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
 public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using size_type = size_t;

  friend Iterator<T> operator+(size_type n, const Iterator<T>& iterator) {
    return Iterator<T>(iterator.ptr_ + n);
  }

  explicit Iterator(pointer ptr) : ptr_(ptr) {}

  bool operator==(const Iterator<value_type>& other) const {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const Iterator<value_type>& other) const {
    return ptr_ != other.ptr_;
  }

  reference operator*() const { return *ptr_; }

  Iterator& operator++() {
    ++ptr_;
    return *this;
  }

  Iterator& operator--() {
    --ptr_;
    return *this;
  }

  Iterator& operator+=(size_type n) {
    ptr_ += n;
    return *this;
  }

  Iterator& operator-=(size_type n) {
    ptr_ -= n;
    return *this;
  }

  Iterator operator+(size_type n) const { return Iterator(ptr_ + n); }

  Iterator operator-(size_type n) const { return Iterator(ptr_ - n); }

  size_type operator-(const Iterator& other) const { return ptr_ - other.ptr_; }

  reference operator[](size_type n) const { return *(ptr_ + n); }

  bool operator<(const Iterator& rhs) const { return ptr_ < rhs.ptr_; }

  bool operator>(const Iterator& rhs) const { return ptr_ > rhs.ptr_; }

  bool operator<=(const Iterator& rhs) const { return ptr_ <= rhs.ptr_; }

  bool operator>=(const Iterator& rhs) const { return ptr_ >= rhs.ptr_; }

 private:
  pointer ptr_;
};

template <class T>
class ReversedIterator
    : public std::iterator<std::random_access_iterator_tag, T> {
 public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using size_type = size_t;

  template <class ST>
  friend ReversedIterator operator+(size_type n,
                                    const ReversedIterator<ST>& iterator) {
    return ReversedIterator<T>(iterator.ptr_ - n);
  }

  explicit ReversedIterator(pointer ptr) : ptr_(ptr) {}

  bool operator==(const ReversedIterator<value_type>& other) const {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const ReversedIterator<value_type>& other) const {
    return ptr_ != other.ptr_;
  }

  reference operator*() const { return *ptr_; }

  ReversedIterator& operator++() {
    --ptr_;
    return *this;
  }

  ReversedIterator& operator--() {
    ++ptr_;
    return *this;
  }

  ReversedIterator& operator+=(size_type n) {
    ptr_ -= n;
    return *this;
  }

  ReversedIterator& operator-=(size_type n) {
    ptr_ += n;
    return *this;
  }

  ReversedIterator operator+(size_type n) const {
    return ReversedIterator(ptr_ - n);
  }

  ReversedIterator operator-(size_type n) const {
    return ReversedIterator(ptr_ + n);
  }

  size_type operator-(const ReversedIterator& other) const {
    return other.ptr_ - ptr_;
  }

  reference operator[](size_type n) const { return *(ptr_ - n); }

  bool operator<(const ReversedIterator& rhs) const { return ptr_ > rhs.ptr_; }

  bool operator>(const ReversedIterator& rhs) const { return ptr_ < rhs.ptr_; }

  bool operator<=(const ReversedIterator& rhs) const {
    return ptr_ >= rhs.ptr_;
  }

  bool operator>=(const ReversedIterator& rhs) const {
    return ptr_ <= rhs.ptr_;
  }

 private:
  pointer ptr_;
};

#endif  // ITERATOR_08_ITERATOR_H
