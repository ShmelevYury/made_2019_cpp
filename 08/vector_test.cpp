#define CATCH_CONFIG_MAIN

#include "Vector.h"
#include "../catch2/catch.hpp"

namespace
{
template  <class T>
bool IsVecEq(const Vector<T>& lhs, const Vector<T>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (size_t i = 0; i < rhs.size(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}
}  // unnamed namespace

TEST_CASE("Test push_back") {
  auto vector = Vector<int>();
  REQUIRE(vector.empty());
  vector.push_back(5);
  REQUIRE(vector[0] == 5);
  vector.push_back(6);
  REQUIRE(vector[1] == 6);
  vector.push_back(7);
  REQUIRE(vector[2] == 7);
  REQUIRE(vector.size() == 3);
  REQUIRE(!vector.empty());
}

TEST_CASE("Test pop") {
  auto vector = Vector<int>();
  REQUIRE(vector.empty());
  vector.pop();
  vector.push_back(5);
  vector.push_back(6);
  vector.pop();
  REQUIRE(vector[0] == 5);
  REQUIRE(vector.size() == 1);
  vector.pop();
  REQUIRE(vector.empty());
}

TEST_CASE("Test size and resize, empty") {
  auto vector = Vector<int>();
  REQUIRE(vector.empty());
  vector.push_back(500);
  REQUIRE(vector.size() == 1);
  REQUIRE(!vector.empty());
  vector.push_back(600);
  REQUIRE(vector.size() == 2);
  REQUIRE(!vector.empty());
  vector.push_back(800);
  REQUIRE(vector.size() == 3);
  REQUIRE(!vector.empty());
  vector.pop();
  REQUIRE(vector.size() == 2);
  REQUIRE(!vector.empty());
  vector.pop();
  REQUIRE(vector.size() == 1);
  REQUIRE(!vector.empty());
  vector.pop();
  REQUIRE(vector.size() == 0);
  REQUIRE(vector.empty());
  vector.resize(55);
  REQUIRE(vector.size() == 55);
  REQUIRE(!vector.empty());
}

TEST_CASE("Test reserve and capacity") {
  Vector<int> vector;
  vector.reserve(100);
  REQUIRE(vector.capacity() >= 100);
  size_t capacity = vector.capacity();
  for (size_t i = 0; i < 100; ++i) {
    vector.push_back(i);
  }
  REQUIRE(capacity == vector.capacity());
  REQUIRE(vector.size() == 100);
}

TEST_CASE("Test empty") {
  auto vector = Vector<int>();
  REQUIRE(vector.empty());
  vector.push_back(5);
  REQUIRE(!vector.empty());
  vector.pop();
  REQUIRE(vector.empty());
}

TEST_CASE("Test deep copy") {
  auto vector = Vector<int>();
  vector.push_back(1);
  vector.push_back(2);
  vector.push_back(3);
  auto copy = Vector<int>(vector);
  REQUIRE(IsVecEq(copy, vector));
  copy.push_back(99);
  REQUIRE(!IsVecEq(copy, vector));
  REQUIRE(copy[3] == 99);
  vector.push_back(88);
  REQUIRE(!IsVecEq(copy, vector));
  REQUIRE(vector[3] == 88);
  REQUIRE(copy[3] == 99);
  vector.pop();
  copy.pop();
  REQUIRE(IsVecEq(copy, vector));
  vector.pop();
  copy.pop();
  REQUIRE(IsVecEq(copy, vector));
  vector.pop();
  copy.pop();
  REQUIRE(IsVecEq(copy, vector));
  REQUIRE_FALSE(vector.empty());
  REQUIRE_FALSE(copy.empty());
  vector.pop();
  copy.pop();
  vector.pop();
  copy.pop();
  REQUIRE(vector.empty());
  REQUIRE(copy.empty());
}

TEST_CASE("Deep assignment") {
  auto vector = Vector<int>();
  vector.push_back(1);
  vector.push_back(2);
  vector.push_back(3);
  Vector<int> copy;
  copy = Vector<int>(vector);
  REQUIRE(IsVecEq(copy, vector));
  copy.push_back(99);
  REQUIRE(!IsVecEq(copy, vector));
  REQUIRE(copy[3] == 99);
  vector.push_back(88);
  REQUIRE(!IsVecEq(copy, vector));
  REQUIRE(vector[3] == 88);
  REQUIRE(copy[3] == 99);
  vector.pop();
  copy.pop();
  REQUIRE(IsVecEq(copy, vector));
  vector.pop();
  copy.pop();
  REQUIRE(IsVecEq(copy, vector));
  vector.pop();
  copy.pop();
  REQUIRE(IsVecEq(copy, vector));
  REQUIRE_FALSE(vector.empty());
  REQUIRE_FALSE(copy.empty());
  vector.pop();
  copy.pop();
  vector.pop();
  copy.pop();
  REQUIRE(vector.empty());
  REQUIRE(copy.empty());
}

TEST_CASE("All in All out") {
  auto vector = Vector<int>();
  for (int i = 0; i < 100000; ++i) {
    vector.push_back(i);
    REQUIRE(vector[i] == i);
  }
    for (int i = 99999; i >= 0; --i) {
      REQUIRE(vector[i] == i);
      vector.pop();
    }
}

TEST_CASE("Test RandomAcseesItearator") {
  SECTION("Test in cycle") {
    Vector<int> vector;
    for (int i = 0; i < 100; ++i) {
      vector.push_back(i);
    }
    int i = 0;
    for (auto it = vector.begin(); it != vector.end(); ++it) {
      REQUIRE(*it == i);
      ++i;
    }
  }

  SECTION("Test compare") {
    Vector<int> vector;
    for (int i = 0; i < 100; ++i) {
      vector.push_back(i);
    }
    auto it1 = vector.begin();
    auto it2 = vector.begin() + 20;
    REQUIRE(it2 > it1);
    REQUIRE(it2 >= it1);
    REQUIRE(it2 != it1);
    REQUIRE(!(it2 == it1));
    REQUIRE(it1 < it2);
    REQUIRE(it1 <= it2);
    auto it3 = ++it1;
    --it1;
    REQUIRE(it1 == vector.begin());
    REQUIRE(it3 > it1);
    REQUIRE(it3 >= it1);
    REQUIRE(it3 != it1);
    REQUIRE(!(it3 == it1));
    REQUIRE(it1 < it3);
    REQUIRE(it1 <= it3);
  }

  SECTION("Test random access") {
    Vector<int> vector;
    for (int i = 0; i < 100; ++i) {
      vector.push_back(i);
    }
    auto it1 = vector.begin();
    auto it2 = vector.begin() + 20;
    auto it3 = 20 + vector.begin();
    REQUIRE(it2 - it1 == 20);
    REQUIRE(it3 == it2);
    auto it4 = it2 - 20;
    REQUIRE(it4 == vector.begin());
    it4 += 20;
    REQUIRE(it4 == it3);
    it4 -= 20;
    REQUIRE(it4 == it1);
  }
}

TEST_CASE("Test ReversedRandomAcseesItearator") {
  SECTION("Test in cycle") {
    Vector<int> vector;
    for (int i = 0; i < 100; ++i) {
      vector.push_back(i);
    }
    int i = 99;
    for (auto it = vector.rbegin(); it != vector.rend(); ++it) {
      REQUIRE(*it == i);
      --i;
    }
  }

  SECTION("Test compare") {
    Vector<int> vector;
    for (int i = 0; i < 100; ++i) {
      vector.push_back(i);
    }
    auto it1 = vector.rbegin();
    auto it2 = vector.rbegin() + 20;
    REQUIRE(it2 > it1);
    REQUIRE(it2 >= it1);
    REQUIRE(it2 != it1);
    REQUIRE(!(it2 == it1));
    REQUIRE(it1 < it2);
    REQUIRE(it1 <= it2);
    auto it3 = ++it1;
    --it1;
    REQUIRE(it1 == vector.rbegin());
    REQUIRE(it3 > it1);
    REQUIRE(it3 >= it1);
    REQUIRE(it3 != it1);
    REQUIRE(!(it3 == it1));
    REQUIRE(it1 < it3);
    REQUIRE(it1 <= it3);
  }

  SECTION("Test random access") {
    Vector<int> vector;
    for (int i = 0; i < 100; ++i) {
      vector.push_back(i);
    }
    auto it1 = vector.rbegin();
    auto it2 = vector.rbegin() + 20;
    auto it3 = 20 + vector.rbegin();
    REQUIRE(it2 - it1 == 20);
    REQUIRE(it3 == it2);
    auto it4 = it2 - 20;
    REQUIRE(it4 == vector.rbegin());
    it4 += 20;
    REQUIRE(it4 == it3);
    it4 -= 20;
    REQUIRE(it4 == it1);
  }
}

class IntWrapper {
 public:
  IntWrapper() = delete;

  explicit IntWrapper(int value) : value_(value) {}

 private:
  int value_;
};

TEST_CASE("Allocator don't call default constructor") {
  Allocator<IntWrapper> allocator;
  IntWrapper* ptr;
  REQUIRE_NOTHROW(ptr = allocator.allocate(8));
  REQUIRE_NOTHROW(allocator.deallocate(ptr, 8));
}
