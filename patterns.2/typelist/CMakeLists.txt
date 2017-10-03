cmake_minimum_required(VERSION 3.6)
project(typelist)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
set(SOURCE_FILES tests/test.cpp include/ObjectList.hpp)
add_executable(typelist ${SOURCE_FILES})