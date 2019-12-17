//#define CATCH_CONFIG_MAIN
//#include "../catch2/catch.hpp"


#include "ThreadPool.h"

#include <chrono>
#include <cassert>

struct A {};

void foo(const A&) {
}

void LessonTest() {
  ThreadPool pool(8);

  auto task1 = pool.exec(foo, A());
  task1.get();

  auto task2 = pool.exec([]() { return 1; });
  assert(task2.get() == 1);
}

void func() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

void TestParallelism() {
  ThreadPool pool(16);
  auto now = std::chrono::steady_clock::now();
  for (size_t i = 0; i < 16; ++i) {
    pool.exec(func);
  }
  auto end = std::chrono::steady_clock::now();
  assert((end - now) < std::chrono::seconds(15));
}

void StressTests() {
  ThreadPool pool(20);
  for (size_t i = 0; i < 10000; ++i) {
    pool.exec([](){
      volatile size_t acc = 0;
      for (size_t j = 0; j < 10000; ++j) {
        acc += j;
      } });
  }
}

bool IsLess (int lhs, int rhs) {
  return lhs < rhs;
}

void TetsSomTests() {
  ThreadPool pool(1);
  auto res1 = pool.exec(IsLess, 1, 2);
  auto res2 = pool.exec(IsLess, 3, 2);
  auto res3 = pool.exec(IsLess, 15664, 47);
  auto res4 = pool.exec(IsLess, 47, 47);
  assert(res1.get());
  assert(!res2.get());
  assert(!res3.get());
  assert(!res4.get());
}

int main() {
//  LessonTest();
//  TestParallelism();
//  StressTests();
  TetsSomTests();
  return 0;
}