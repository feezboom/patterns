cmake_minimum_required(VERSION 3.6)
project(game)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)

include_directories(include)

set(SOURCE_FILES main.cpp src/Game.cpp include/Game.h include/IObject.h src/ObjectImpl.h src/ObjectImpl.cpp include/Direction.h)
add_executable(game ${SOURCE_FILES})
target_link_libraries(game ${CURSES_LIBRARIES})
