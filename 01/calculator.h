#ifndef CALCULATOR_CALCULATOR_H_
#define CALCULATOR_CALCULATOR_H_

#include <exception>
#include <string>

class SyntaxError : public std::exception {
 public:
  explicit SyntaxError(std::string msg);

  const char* what() const noexcept override;

 private:
  std::string msg_;
};

int Calculate(const char* expression);

#endif  // CALCULATOR_CALCULATOR_H_