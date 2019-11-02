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
void ParseStream(std::istream& stream, NumberCallback number_callback,
                 StringCallback string_callback,
                 TimimgCallback starting_parsing,
                 TimimgCallback ending_parsing) {
  if (starting_parsing) {
    starting_parsing();
  }
  std::string token;
  while (!stream.eof()) {
    auto next_char = stream.get();
    if (next_char == ' ' || next_char == '\t' || next_char == '\n' ||
        stream.eof()) {
      if (!token.empty()) {
        if (number_callback && IsNumber(token)) {
          number_callback(std::stoi(token));
        } else if (string_callback) {
          string_callback(token);
        }
      }
      token = "";
    } else {
      token.append(1, next_char);
    }
  }
  if (ending_parsing) {
    ending_parsing();
  }
}
