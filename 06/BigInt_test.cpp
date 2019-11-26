#define CATCH_CONFIG_MAIN

#include "BigInt.h"
#include "../catch2/catch.hpp"

#include <limits>
#include <string>

constexpr int max_int = std::numeric_limits<int>::max();

TEST_CASE("Small nums") {
  BigInt a = 5;
  BigInt b(6);
  BigInt c(11);
  REQUIRE(a + b == c);
  REQUIRE(a == 5);
  REQUIRE(b == 6);
}

TEST_CASE("Test work with int") {
  BigInt a;
  a = 5;
  REQUIRE(a == 5);
  a = a + 3;
  REQUIRE(a == 8);
  a = a - 3;
  REQUIRE(a == 5);
  a = 3 - a + 6 - a;
  REQUIRE(a == -1);
  a = 3 + a;
  REQUIRE(a == 2);
}

TEST_CASE("Sum, diff and unary minus") {
  BigInt a = 5;
  BigInt b = -60;
  REQUIRE(a + b == -55);
  REQUIRE(b + a == -55);
  b = -60 + a - 25 - 95 + a - 60;
  REQUIRE(b == -230);
  b = -b;
  REQUIRE(b == 230);
  BigInt c = 250;
  a = c - b;
  REQUIRE(a == 20);
  a = b - c;
  REQUIRE(a == -20);
  BigInt d = -30;
  REQUIRE(a + d == -50);
  REQUIRE(a - d == 10);
  REQUIRE(d - a == -10);
  REQUIRE(-d - a == 50);
}

TEST_CASE("Big nums") {
  BigInt a = max_int;
  BigInt b = -max_int;
  a = a + a;
  REQUIRE(max_int == a + b);
  a = a + b;
  REQUIRE(a == max_int);
  a = a + b;
  REQUIRE(a == 0);
}

TEST_CASE("Big math and output") {
  std::stringstream ss1;
  std::string check_string;
  BigInt a = max_int;
  ss1 << a + a;
  ss1 >> check_string;
  REQUIRE(check_string == "4294967294");
  std::stringstream ss2;
  a = a + a;
  a = -a;
  ss2 << a;
  ss2 >> check_string;
  REQUIRE(check_string == "-4294967294");
  std::stringstream ss3;
  a = -a - 25698;
  ss3 << a;
  ss3 >> check_string;
  REQUIRE(check_string == "4294941596");
}

TEST_CASE("Compare BigInt") {
  BigInt a = 5;
  BigInt b = 6;
  BigInt c = 7;
  BigInt d = 6;
  REQUIRE(a == 5);
  REQUIRE(5 == a);
  REQUIRE(a < b);
  REQUIRE(b > a);
  REQUIRE(a <= b);
  REQUIRE(b >= a);
  REQUIRE(5 < b);
  REQUIRE(5 <= b);
  REQUIRE(c > b);
  REQUIRE(-15 <= b);
  REQUIRE(-15 < b);
  REQUIRE(b >= -15);
  REQUIRE(b > -15);
  REQUIRE(125 > c);
  REQUIRE(125 >= c);
  REQUIRE(d == b);
  REQUIRE(b == d);
  REQUIRE(d <= b);
  REQUIRE(d >= b);
}