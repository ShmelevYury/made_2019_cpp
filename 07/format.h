#ifndef FORMAT_FORMAT_H
#define FORMAT_FORMAT_H

#include <cctype>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Generic {
 public:
  virtual void WriteToStream(std::ostream& out) = 0;
};

template <class T>
class Specific : public Generic {
 public:
  explicit Specific(const T& item) : item_(item) {}

  void WriteToStream(std::ostream& out) override { out << item_; }

 private:
  const T& item_;
};

template <class... ArgsT>
std::string Format(const std::string& text, ArgsT&&... args) {
  std::stringstream result;
  //  К сожалению список инициализации копирует аргументы, а другого более
  //  изящного способа я не нашёл, так что пользуюсь shared_ptr.
  std::vector<std::shared_ptr<Generic>> arguments{
      std::make_shared<Specific<ArgsT>>(args)...};
  for (size_t pos = 0; pos < text.size(); ++pos) {
    if (text[pos] == '{') {
      ++pos;
      if (pos == text.size() || text[pos] == '}') {
        throw std::runtime_error{"Missing number in the bracket at position " +
                                 std::to_string(pos)};
      }

      constexpr size_t max_size_t = std::numeric_limits<size_t>::max();
      size_t num = 0;
      while (pos < text.size() && std::isdigit(text[pos])) {
        size_t digit = text[pos] - '0';
        if (num > (max_size_t - digit) / 10) {
          throw std::runtime_error{"Too big number at position " +
                                   std::to_string(pos)};
        }
        num = num * 10 + digit;
        ++pos;
      }

      if (pos == text.size() || text[pos] != '}') {
        throw std::runtime_error{"Unclosed bracket at position " +
                                 std::to_string(pos)};
      }

      if (num >= arguments.size()) {
        throw std::runtime_error{"Too big number at position " +
                                 std::to_string(pos)};
      }

      arguments[num]->WriteToStream(result);
    } else if (text[pos] == '}') {
      throw std::runtime_error{"Bracket } before { at position " +
                               std::to_string(pos)};
    } else {
      result << text[pos];
    }
  }

  return result.str();
}

std::string Format(const std::string& text);

#endif  // FORMAT_FORMAT_H
