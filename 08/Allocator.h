#ifndef ALLOCATOR_08_ALLOCATOR_H
#define ALLOCATOR_08_ALLOCATOR_H

#include <cstddef>
#include <limits>
#include <cstdlib>

template <class T>
class Allocator {
 public:
  using value_type = T;
  using pointer = T*;
  using size_type = size_t;

  pointer allocate(size_type count) {
    return static_cast<pointer>(std::malloc(sizeof(value_type) * count));
  }

  void deallocate(pointer ptr, size_type count) {
    std::free(ptr);
  }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_t>::max();
  }
};

#endif  // ALLOCATOR_08_ALLOCATOR_H
