#ifndef FORMAT_FORMAT_H
#define FORMAT_FORMAT_H

#include <cctype>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

template <class T>
inline std::string to_string(T&& x) {
  std::ostringstream ss;
  ss << std::forward<T>(x);
  return ss.str();
}

template <class... ArgsT>
std::string Format(const std::string& text, ArgsT&&... args) {
  std::stringstream result;
  std::vector<std::string> arguments;
  arguments.reserve(sizeof...(args));
  (arguments.emplace_back(to_string<ArgsT>(std::forward<ArgsT>(args))), ...);
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

      result << arguments[num];
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
