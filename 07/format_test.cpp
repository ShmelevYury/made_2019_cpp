#define CATCH_CONFIG_MAIN

#include "format.h"
#include "../catch2/catch.hpp"

TEST_CASE("Lesson example") {
  std::string text = Format("{1}+{1} = {0}", 2, "one");
  REQUIRE(text == "one+one = 2");
}

TEST_CASE("Without brackets") {
  std::string text = Format("abcvgd..@<>387");
  REQUIRE(text == "abcvgd..@<>387");
  text = Format("abcvgd..@<>387", 2, "two");
  REQUIRE(text == "abcvgd..@<>387");
}

TEST_CASE("Skipping some args") {
  std::string text = Format("{2} * {3} == {4}", 1, 2, 3, 4, 5);
  REQUIRE(text == "3 * 4 == 5");
  text = Format("Yesterday was {0}", "Monday", "Tuesday", "Wednesday",
                "Thursday", "Friday", "Saturday", "Sunday");
  REQUIRE(text == "Yesterday was Monday");
  text = Format("I bought it at {4}", "Monday", "Tuesday", "Wednesday",
                "Thursday", "Friday", "Saturday", "Sunday");
  REQUIRE(text == "I bought it at Friday");
}

//  В catch2 встроен интерфейс работы с ошибками, но в учебных целях я им
//  пользоваться не буду
TEST_CASE("Too big numbers") {
  try {
    std::string text = Format("i don't like {2}", "potato");
    REQUIRE(false);
  } catch (std::runtime_error& e) {
    REQUIRE(std::string(e.what()) == "Too big number at position 15");
  } catch (...) {
    REQUIRE(false);
  }

  try {
    std::string text = Format(
        "i don't like {1000000000000000000000000000000"
        "00000000000000000000000000000000000000000000}",
        1, 25, "chebureck");
    REQUIRE(false);
  } catch (std::runtime_error& e) {
    REQUIRE(std::string(e.what()) == "Too big number at position 34");
  } catch (...) {
    REQUIRE(false);
  }
}

TEST_CASE("Wrong brackets") {
  try {
    std::string text = Format("{1}, {0}, {1", "potato", 123, 56);
    REQUIRE(false);
  } catch (std::runtime_error& e) {
    REQUIRE(std::string(e.what()) == "Unclosed bracket at position 12");
  } catch (...) {
    REQUIRE(false);
  }

  try {
    std::string text = Format("{1}, {0}, {1, hi", "potato", 123, 56);
    REQUIRE(false);
  } catch (std::runtime_error& e) {
    REQUIRE(std::string(e.what()) == "Unclosed bracket at position 12");
  } catch (...) {
    REQUIRE(false);
  }

  try {
    std::string text = Format("I would like to buy 1}", "potato", 123, 56);
    REQUIRE(false);
  } catch (std::runtime_error& e) {
    REQUIRE(std::string(e.what()) == "Bracket } before { at position 21");
  } catch (...) {
    REQUIRE(false);
  }

  try {
    std::string text = Format("I would like to buy {}", "potato", 123, 56);
    REQUIRE(false);
  } catch (std::runtime_error& e) {
    REQUIRE(std::string(e.what()) ==
            "Missing number in the bracket at position 21");
  } catch (...) {
    REQUIRE(false);
  }
}

TEST_CASE("Some random tests") {
  std::string text = Format("I would like to buy {0}", "potato", 123, 56);
  REQUIRE(text == "I would like to buy potato");
  text = Format("I would like to buy {1} {0}", "potatoes", 123, 56);
  REQUIRE(text == "I would like to buy 123 potatoes");
  text = Format("I would like to buy {2} {0} and {1} {3}", "potatoes", 123, 56,
                "carrots");
  REQUIRE(text == "I would like to buy 56 potatoes and 123 carrots");
  text = Format("I would like to buy {1} {0} and {2} {3}", "potatoes", 123, 56,
                "carrots");
  REQUIRE(text == "I would like to buy 123 potatoes and 56 carrots");
  text = Format("I would like to buy {0} {0} and {0} {0}", "potatoes", 123, 56,
                "carrots");
  REQUIRE(text ==
          "I would like to buy potatoes potatoes and potatoes potatoes");
}

TEST_CASE("Test rvalues") {
  std::string original = "I would like to buy {1} {0} and {2} {3}";
  std::string arg1 = "potatoes";
  int arg2 = 123;
  int arg3 = 56;
  std::string arg4 = "carrots";
  std::string formated = Format(original, arg1, arg2, arg3, arg4);
  REQUIRE(formated == "I would like to buy 123 potatoes and 56 carrots");
}