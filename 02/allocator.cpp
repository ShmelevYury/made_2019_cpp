#include "allocator.h"

#include <cstddef>
#include <cstdlib>

LinearAllocator::LinearAllocator(size_t maxSize)
    : begin_((char*)std::malloc(maxSize)),
      end_(begin_),
      capacity_(begin_ + maxSize) {}

char* LinearAllocator::alloc(size_t size) {
  if (end_ + size > capacity_) {
    return nullptr;
  }
  char* pointer = end_;
  end_ += size;
  return pointer;
}

void LinearAllocator::reset() { end_ = begin_; }

LinearAllocator::~LinearAllocator() { free(begin_); }