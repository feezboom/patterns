cmake_minimum_required(VERSION 3.8)
project(reader)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES tests_src/test.cpp include/typelist.h include/reader.hpp include/AllocSize.hpp include/printer.hpp)
add_executable(reader ${SOURCE_FILES})