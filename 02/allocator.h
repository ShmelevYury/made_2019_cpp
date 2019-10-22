#ifndef ALLOCATOR_ALLOCATOR_H
#define ALLOCATOR_ALLOCATOR_H

#include <cstddef>

class LinearAllocator {
 public:
  LinearAllocator() = delete;
  explicit LinearAllocator(size_t maxSize);
  LinearAllocator(const LinearAllocator& rhs) = delete;
  LinearAllocator(LinearAllocator&& rhs) = delete;
  LinearAllocator& operator=(const LinearAllocator& rhs) = delete;
  LinearAllocator& operator=(LinearAllocator&& rhs) = delete;
  char* alloc(size_t size);
  void reset();
  ~LinearAllocator();

 private:
  char* begin_;
  char* end_;
  char* capacity_;
};

#endif  // ALLOCATOR_ALLOCATOR_H
