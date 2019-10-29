#define CATCH_CONFIG_MAIN

#include "parser.h"
#include "catch2/catch.hpp"

#include <iostream>
#include <string>
#include <vector>

bool IsVecEqual(const std::vector<std::string>& lhs,
                const std::vector<std::string>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (size_t i = 0; i < lhs.size(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

struct Log {
  std::vector<std::string> args;
  bool is_started, is_ended;

  void Refresh() {
    args.resize(0);
    is_started = false;
    is_ended = false;
  }
};

namespace TestingSpace {
// Создаю лог для отслеживания вызовов функций
Log log;

void PrintStart() {
  log.is_started = true;
  std::cout << "Starting parsing" << '\n';
}

void PrintEnd() {
  log.is_ended = true;
  std::cout << "Ending parsing" << '\n';
}

void PrintNumber(int number) {
  std::cout << "Num was given: " << number << '\n';
  log.args.emplace_back(std::to_string(number));
}

void PrintString(const std::string& token) {
  std::cout << "Token was given: " << token << '\n';
  log.args.emplace_back(token);
}

TEST_CASE("Test token") {
  log.Refresh();
  std::stringstream strstream;
  strstream << "abc";
  ParseStream(&strstream, PrintNumber, PrintString, PrintStart, PrintEnd);
  REQUIRE(log.is_started);
  REQUIRE(log.is_ended);
  REQUIRE(IsVecEqual(log.args, std::vector<std::string>{"abc"}));
}

TEST_CASE("Test num") {
  log.Refresh();
  std::stringstream strstream;
  strstream << "12";
  ParseStream(&strstream, PrintNumber, PrintString, PrintStart, PrintEnd);
  REQUIRE(log.is_started);
  REQUIRE(log.is_ended);
  REQUIRE(IsVecEqual(log.args, std::vector<std::string>{"12"}));
}

TEST_CASE("Combine nums and tokens") {
  log.Refresh();
  std::stringstream strstream;
  strstream << "12 43 abc kl 9 hj 8";
  ParseStream(&strstream, PrintNumber, PrintString, PrintStart, PrintEnd);
  REQUIRE(log.is_started);
  REQUIRE(log.is_ended);
  REQUIRE(IsVecEqual(log.args, std::vector<std::string>{"12", "43", "abc", "kl",
                                                        "9", "hj", "8"}));
}

TEST_CASE("Mixed nums and chars") {
  log.Refresh();
  std::stringstream strstream;
  strstream << "12abc anc45,11";
  ParseStream(&strstream, PrintNumber, PrintString, PrintStart, PrintEnd);
  REQUIRE(log.is_started);
  REQUIRE(log.is_ended);
  REQUIRE(IsVecEqual(log.args, std::vector<std::string>{"12abc", "anc45,11"}));
}

TEST_CASE("Tabs, spaces and line break") {
  log.Refresh();
  std::stringstream strstream;
  strstream << "12      43kl       a2c \n       k l    9    \n hj 8\n";
  ParseStream(&strstream, PrintNumber, PrintString, PrintStart, PrintEnd);
  REQUIRE(log.is_started);
  REQUIRE(log.is_ended);
  REQUIRE(IsVecEqual(
      log.args,
      std::vector<std::string>{"12", "43kl", "a2c", "k", "l", "9", "hj", "8"}));
}
}  // namespace TestingSpace