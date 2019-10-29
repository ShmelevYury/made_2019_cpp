cmake_minimum_required(VERSION 3.14)
project(parser_test)

add_library(Parser STATIC parser.cpp)
add_executable(parser_test parser_test.cpp)

target_link_libraries(parser_test Parser)
