cmake_minimum_required(VERSION 3.8)
project(TypeList)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp include/_typelist.hpp include/_typeat.hpp include/_length.hpp include/typelist.h)
add_executable(TypeList ${SOURCE_FILES})