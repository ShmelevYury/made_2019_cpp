#define CATCH_CONFIG_MAIN

#include "allocator.h"
#include "catch2/catch.hpp"

TEST_CASE("Test alloc") {
  LinearAllocator allocator(4 * sizeof(char));
  char* first_array = allocator.alloc(2 * sizeof(char));
  REQUIRE(first_array);
  char* second_array = allocator.alloc(2 * sizeof(char));
  REQUIRE(second_array);
  first_array[0] = 'a';
  first_array[1] = 'b';
  second_array[0] = 'c';
  second_array[1] = 'd';
  REQUIRE(first_array[0] == 'a');
  REQUIRE(first_array[1] == 'b');
  REQUIRE(second_array[0] == 'c');
  REQUIRE(second_array[1] == 'd');
  char* third_array = allocator.alloc(sizeof(char));
  REQUIRE(!third_array);
}

TEST_CASE("Test 0 byte allocation") {
  LinearAllocator allocator(0);
  char* array = allocator.alloc(2 * sizeof(char));
  REQUIRE(!array);
  allocator.reset();
  array = allocator.alloc(2 * sizeof(char));
  REQUIRE(!array);
  array = allocator.alloc(0);
  REQUIRE(!array);
}

TEST_CASE("Test reset") {
  LinearAllocator allocator(10 * sizeof(char));
  char* first_array = allocator.alloc(10 * sizeof(char));
  REQUIRE(first_array);
  char* second_array = allocator.alloc(2 * sizeof(char));
  REQUIRE(!second_array);
  allocator.reset();
  second_array = allocator.alloc(5 * sizeof(char));
  REQUIRE(second_array);
  char* third_array = allocator.alloc(5 * sizeof(char));
  REQUIRE(third_array);
}

TEST_CASE("Assignment with move") {
  char* array1;
  LinearAllocator allocator1(1 * sizeof(char));
  {
    LinearAllocator allocator2(2 * sizeof(char));
    array1 = allocator2.alloc(2 * sizeof(char));
    array1[0] = 'a';
    array1[1] = 'b';
    allocator1 = std::move(allocator2);
  }
  REQUIRE(array1[0] == 'a');
  REQUIRE(array1[1] == 'b');
  char* array2 = allocator1.alloc(1 * sizeof(char));
  REQUIRE(!array2);
  allocator1.reset();
  array2 = allocator1.alloc(2 * sizeof(char));
  REQUIRE(array2);
  array2[0] = 'd';
  array2[1] = 'c';
  REQUIRE(array2[0] == 'd');
  REQUIRE(array2[1] == 'c');
}

TEST_CASE("Copy with move") {
  LinearAllocator allocator1(2 * sizeof(char));
  char* array1 = allocator1.alloc(2 * sizeof(char));
  array1[0] = 'a';
  array1[1] = 'b';
  LinearAllocator allocator2(std::move(allocator1));
  REQUIRE(array1[0] == 'a');
  REQUIRE(array1[1] == 'b');
  char* array2 = allocator2.alloc(1 * sizeof(char));
  REQUIRE(!array2);
  allocator2.reset();
  array2 = allocator2.alloc(2 * sizeof(char));
  REQUIRE(array2);
  array2[0] = 'd';
  array2[1] = 'c';
  REQUIRE(array2[0] == 'd');
  REQUIRE(array2[1] == 'c');
}