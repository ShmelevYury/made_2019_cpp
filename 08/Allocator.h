#ifndef ALLOCATOR_08_ALLOCATOR_H
#define ALLOCATOR_08_ALLOCATOR_H

#include <cstddef>
#include <limits>
#include <cstdlib>
#include <algorithm>

template <class T>
class Allocator {
 public:
  using value_type = T;
  using const_reference = const T&;
  using r_value = T&&;
  using pointer = T*;
  using size_type = size_t;

  pointer allocate(size_type count) {
    return static_cast<pointer>(operator new(count * sizeof(value_type)));
  }

  void construct(pointer p, const_reference val ) {
    new (static_cast<void*>(p)) value_type(val);
  }

  void construct(pointer p, r_value val ) {
    new (static_cast<void*>(p)) value_type(std::move(val));
  }

  void deallocate(pointer ptr, size_type count) {
    operator delete(ptr);
  }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_t>::max();
  }
};

#endif  // ALLOCATOR_08_ALLOCATOR_H
