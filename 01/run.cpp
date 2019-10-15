#include "calculator.h"

#include <iostream>
#include <string>

// Запускает калькулятор в интерактивном режиме
int main() {
  while (true) {
    try {
      std::string expression;
      std::getline(std::cin, expression);
      std::cout << Calculate(expression.c_str()) << std::endl;
    } catch (SyntaxError& e) {
      std::cerr << e.what() << std::endl;
      return 1;
    }
  }
  return 0;
}