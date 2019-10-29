#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <functional>

void ParseStream(std::istream* stream, std::function<void(int)> number_callback,
                 std::function<void(std::string)> string_callback,
                 std::function<void()> starting_parsing,
                 std::function<void()> ending_parsing);
#endif  // PARSER_PARSER_H
