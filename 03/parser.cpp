#include "parser.h"

#include <functional>
#include <istream>

inline bool IsNumber(const std::string& string) {
  for (auto letter : string) {
    if (!std::isdigit(letter)) {
      return false;
    }
  }
  return true;
}

// Тестировать удобнее, если передовать по ссылке, но возожно это неправильно
void ParseStream(std::istream* stream, std::function<void(int)> number_callback,
                 std::function<void(std::string)> string_callback,
                 std::function<void()> starting_parsing,
                 std::function<void()> ending_parsing) {
  starting_parsing();
  std::string token;
  while (!stream->eof()) {
    auto next_char = stream->get();
    if (next_char == ' ' || next_char == '\t' || next_char == '\n' ||
        stream->eof()) {
      if (!token.empty()) {
        if (IsNumber(token)) {
          number_callback(std::stoi(token));
        } else {
          string_callback(token);
        }
      }
      token = "";
    } else {
      token.append(1, next_char);
    }
  }
  ending_parsing();
}
