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
