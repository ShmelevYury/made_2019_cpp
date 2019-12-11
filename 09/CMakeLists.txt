cmake_minimum_required(VERSION 3.14)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(ThreadPool ThreadPool.cpp ThreadPool_test.cpp)