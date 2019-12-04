#ifndef ALLOCATOR_08_ALLOCATOR_H
#define ALLOCATOR_08_ALLOCATOR_H

#include <cstddef>
#include <limits>

template <class T>
class Allocator {
 public:
  using value_type = T;
  using pointer = T*;
  using size_type = size_t;

  pointer allocate(size_type count) { return new T[count]; }

  void deallocate(pointer ptr, size_type count) { delete[] ptr; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_t>::max();
  }
};

#endif  // ALLOCATOR_08_ALLOCATOR_H
