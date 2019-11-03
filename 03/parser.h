#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <functional>

using TimimgCallback = std::function<void()>;
using NumberCallback = std::function<void(int)>;
using StringCallback = std::function<void(const std::string&)>;

void ParseStream(std::istream& stream, NumberCallback number_callback,
                 StringCallback string_callback,
                 TimimgCallback starting_parsing,
                 TimimgCallback ending_parsing);
#endif  // PARSER_PARSER_H
