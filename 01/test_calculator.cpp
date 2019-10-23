#define CATCH_CONFIG_MAIN

#include "calculator.h"
#include "catch2/catch.hpp"

TEST_CASE("Plus and Minus") {
  REQUIRE(5 == Calculate("5"));
  REQUIRE((1 + 5) == Calculate("1 + 5"));
  REQUIRE((6 - 5) == Calculate("6 - 5"));
  REQUIRE((6 - 5 + 7) == Calculate("6 - 5 + 7"));
  REQUIRE((7 + 7 + 7 - 8) == Calculate("7 + 7 + 7 - 8"));
  REQUIRE((95 + 1000 - 10000) == Calculate("95 + 1000 - 10000"));
}

TEST_CASE("Unary minus") {
  REQUIRE(-3 == Calculate("-3"));
  REQUIRE((1 - -1) == Calculate("1 - -1"));
  REQUIRE((-5 + -5) == Calculate("-5 + -5"));
  REQUIRE((-156 * 2) == Calculate("-156 * 2"));
}

TEST_CASE("Mul and Divide") {
  REQUIRE((5 / 6) == Calculate("5 / 6"));
  REQUIRE((2 * 2) == Calculate("2 * 2"));
  REQUIRE((95 * 37 / 52 * 3) == Calculate("95 * 37 / 52 * 3"));
  REQUIRE((357 * 2 / 39 * 3 * 5 / 7) == Calculate("357 * 2 / 39 * 3 * 5 / 7"));
}

TEST_CASE("Order of operations") {
  REQUIRE((1 + 5 / 6 + 2) == Calculate("1 + 5 / 6 + 2"));
  REQUIRE((5 * 6 / 2 * 3 - 1 + 2 - 3 * 5 + 6 / 3) ==
          Calculate("5 * 6 / 2 * 3 - 1 + 2 - 3 * 5 + 6 / 3"));
  REQUIRE((5 + 5 * 5) == Calculate("5 + 5 * 5"));
  REQUIRE((5 * 5 + 37) == Calculate("5 * 5 + 37"));
}

TEST_CASE("Work with spaces") {
  REQUIRE((2 + 5 - -3) == Calculate("2+5--3"));
  REQUIRE((2 + 5 - -3) ==
          Calculate("2             +            5        -      -3"));
  REQUIRE((2 + 5 - -3) == Calculate("2+     5        -      -3"));
}

TEST_CASE("Working with wrong syntax") {
  REQUIRE_THROWS(Calculate("11 +"));
  REQUIRE_THROWS(Calculate("11 + 11 /"));
  REQUIRE_THROWS(Calculate("11 ++ 3"));
  REQUIRE_THROWS(Calculate("11 - - -3"));
  REQUIRE_THROWS(Calculate("11 +* 3"));
  REQUIRE_THROWS(Calculate("11 + (59)"));
  REQUIRE_THROWS(Calculate("$11 + 12"));
  REQUIRE_THROWS(Calculate("11 + #12"));
  REQUIRE_THROWS(Calculate("1 / 0"));
}