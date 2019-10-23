#include "allocator.h"

#include <algorithm>
#include <cstddef>
#include <cstdlib>

LinearAllocator::LinearAllocator(size_t maxSize) {
  if (maxSize > 0) {
    begin_ = (char*)std::malloc(maxSize);
    end_ = begin_;
    size_ = maxSize;
  } else {
    begin_ = nullptr;
  }
}

LinearAllocator::LinearAllocator(LinearAllocator&& rhs)
    : begin_(rhs.begin_), end_(rhs.end_), size_(rhs.size_) {
  rhs.begin_ = nullptr;
}

LinearAllocator& LinearAllocator::operator=(LinearAllocator&& rhs) {
  free(begin_);
  begin_ = rhs.begin_;
  end_ = rhs.end_;
  size_ = rhs.size_;
  rhs.begin_ = nullptr;
  return *this;
}

char* LinearAllocator::alloc(size_t size) {
  if (!begin_ || (size + (end_ - begin_) > size_)) {
    return nullptr;
  }
  char* pointer = end_;
  end_ += size;
  return pointer;
}

void LinearAllocator::reset() { end_ = begin_; }

LinearAllocator::~LinearAllocator() { free(begin_); }