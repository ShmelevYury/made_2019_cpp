cmake_minimum_required(VERSION 3.14)
project(allocator)
#
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
        CACHE STRING "Compiler flags in asan build"
        FORCE)

add_executable(allocator test_allocator.cpp allocator.cpp)