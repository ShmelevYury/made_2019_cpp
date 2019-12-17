#define CATCH_CONFIG_MAIN

#include "ThreadPool.h"
#include "../catch2/catch.hpp"

#include <chrono>

struct A {};

void foo(const A&) {
}

TEST_CASE("Lesson example") {
  ThreadPool pool(8);

  auto task1 = pool.exec(foo, A());
  REQUIRE_NOTHROW(task1.get());

  auto task2 = pool.exec([]() { return 1; });
  REQUIRE(task2.get() == 1);
}

void func() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

TEST_CASE("Test parallelism") {
  ThreadPool pool(16);
  auto now = std::chrono::steady_clock::now();
  for (size_t i = 0; i < 16; ++i) {
    REQUIRE_NOTHROW(pool.exec(func));
  }
  auto end = std::chrono::steady_clock::now();
  REQUIRE((end - now) < std::chrono::seconds(15));
}

TEST_CASE("Stress test") {
  ThreadPool pool(20);
  for (size_t i = 0; i < 10000; ++i) {
    REQUIRE_NOTHROW(pool.exec([](){
      volatile size_t acc = 0;
      for (size_t j = 0; j < 10000; ++j) {
        acc += j;
      } }));
  }
}

bool IsLess (int lhs, int rhs) {
  return lhs < rhs;
}

TEST_CASE("Test get") {
  ThreadPool pool(3);
  auto res1 = pool.exec(IsLess, 1, 2);
  auto res2 = pool.exec(IsLess, 3, 2);
  auto res3 = pool.exec(IsLess, 15664, 47);
  auto res4 = pool.exec(IsLess, 47, 47);
  REQUIRE(res1.get());
  REQUIRE(!res2.get());
  REQUIRE(!res3.get());
  REQUIRE(!res4.get());
} 