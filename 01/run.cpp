#include "calculator.h"

#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Error! Program expects 1 argument, " << argc - 1
              << " was given." << std::endl;
    return 1;
  }
  try {
    std::cout << Calculate(argv[1]) << std::endl;
  } catch (SyntaxError& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}