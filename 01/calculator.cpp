#include "calculator.h"

#include <cctype>
#include <cstring>
#include <exception>
#include <string>

SyntaxError::SyntaxError(std::string msg) : msg_(std::move(msg)) {}

const char* SyntaxError::what() const noexcept { return msg_.c_str(); }

struct Expression {
  const char* input;
  size_t pos;
  size_t length;
};

void SkipSpaces(Expression* expr) {
  while ((expr->pos < expr->length) && (expr->input[expr->pos] == ' ')) {
    ++expr->pos;
  }
}

int NumFromString(Expression* expr) {
  int num = 0;
  while (std::isdigit(expr->input[expr->pos])) {
    num *= 10;
    num += static_cast<int>(expr->input[expr->pos] - '0');
    ++expr->pos;
  }
  return num;
}

int GetNum(Expression* expr) {
  SkipSpaces(expr);
  if (expr->pos >= expr->length) {
    throw SyntaxError("Error! Last argument must be a number!");
  }
  if (((expr->pos + 1 < expr->length) && (expr->input[expr->pos] == '-') &&
       !std::isdigit(expr->input[expr->pos + 1])) ||
      ((expr->input[expr->pos] != '-') &&
       !std::isdigit(expr->input[expr->pos]))) {
    throw SyntaxError("Error! Number is expected at position " +
                      std::to_string(expr->pos) + ".");
  }
  if (expr->input[expr->pos] == '-') {
    ++expr->pos;
    return -NumFromString(expr);
  }
  return NumFromString(expr);
}

void GetNextOperation(Expression* expr) {
  SkipSpaces(expr);
  if (expr->pos < expr->length && expr->input[expr->pos] != '+' &&
      expr->input[expr->pos] != '-' && expr->input[expr->pos] != '*' &&
      expr->input[expr->pos] != '/') {
    throw SyntaxError("Unknown operation at position " +
                      std::to_string(expr->pos) + ".");
  }
}

int MulDivide(Expression* expr) {
  int cumulative = GetNum(expr);
  GetNextOperation(expr);
  while (expr->pos < expr->length &&
         (expr->input[expr->pos] == '*' || expr->input[expr->pos] == '/')) {
    char operation = expr->input[expr->pos];
    ++expr->pos;
    int next = GetNum(expr);
    if (operation == '*') {
      cumulative *= next;
    } else if (next == 0) {
      throw SyntaxError("Attemption to divide by zero at pos " +
                        std::to_string(expr->pos) + ".");
    } else {
      cumulative /= next;
    }
    GetNextOperation(expr);
  }
  return cumulative;
}

int MinusPlus(Expression* expr) {
  int cumulative = MulDivide(expr);
  GetNextOperation(expr);
  while (expr->pos < expr->length) {
    char operation = expr->input[expr->pos];
    ++expr->pos;
    int next = MulDivide(expr);
    if (operation == '+') {
      cumulative += next;
    } else {
      cumulative -= next;
    }
    GetNextOperation(expr);
  }
  return cumulative;
}


// Изначально функция обрабатывала аргументы комадной строки, так что она работает с cstring
int Calculate(const char* expression) {
  Expression expr{expression, 0, std::strlen(expression)};
  int result = MinusPlus(&expr);
  if (expr.pos < expr.length) {
    throw SyntaxError("Parser error after position " +
                      std::to_string(expr.pos) + ".");
  }
  return result;
}