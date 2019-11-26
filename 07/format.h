#ifndef FORMAT_FORMAT_H
#define FORMAT_FORMAT_H

#include <cctype>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <tuple>

namespace {
template <size_t I, class... ArgsT>
struct TupleElemToStreamRecur {
  static void perform(const std::tuple<ArgsT...>& tuple, size_t index,
                      std::ostream& ostream) {
    if (I == index) {
      ostream << std::get<I>(tuple);
      return;
    }
    TupleElemToStreamRecur<I - 1, ArgsT...>::perform(tuple, index, ostream);
  }
};

template <class... ArgsT>
struct TupleElemToStreamRecur<0, ArgsT...> {
  static void perform(const std::tuple<ArgsT...>& tuple, size_t index,
                      std::ostream& ostream) {
    // Так как проверялось, что индекс не превышает размер кортежа, то до сюда
    // мы доберёмся, только при нулевом индексе
    ostream << std::get<0>(tuple);
  }
};
}  // Unnamed namespace

template <class... ArgsT>
void TupleElemToStream(const std::tuple<ArgsT...>& tuple, size_t index,
                       std::ostream& ostream) {
  constexpr size_t tuple_size = std::tuple_size<std::tuple<ArgsT...>>::value;
  if (index >= tuple_size) {
    throw std::runtime_error{"Index is too big"};
  }
  return TupleElemToStreamRecur<tuple_size - 1, ArgsT...>::perform(tuple, index,
                                                                   ostream);
}

template <class... ArgsT>
std::string Format(const std::string& text, ArgsT... args) {
  std::stringstream result;
  auto arguments = std::make_tuple(std::forward<ArgsT>(args)...);
  size_t arguments_num = std::tuple_size<std::tuple<ArgsT...>>::value;
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

      if (num >= arguments_num) {
        throw std::runtime_error{"Too big number at position " +
                                 std::to_string(pos)};
      }

      TupleElemToStream(arguments, num, result);
    } else if (text[pos] == '}') {
      throw std::runtime_error{"Bracket } before { at position " +
                               std::to_string(pos)};
    } else {
      result << text[pos];
    }
  }

  return result.str();
}

std::string Format(const std::string& text) {
  return text;
}
#endif  // FORMAT_FORMAT_H
