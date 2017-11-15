cmake_minimum_required(VERSION 3.8)
project(TypeList)

set(CMAKE_CXX_STANDARD 17)

# Tests section

# SETTING UP GOOGLE TEST BEGIN
# Instructions are taken from here <a href="http://kaizou.org/2014/11/gtest-cmake">Instructions link</a>}

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
        gtest
        URL https://github.com/google/googletest/archive/master.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        # Disable install step
        INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
        "${source_dir}/googlemock/include")

# SETTING UP GOOGLE TEST END


# Specify include directory
include_directories(include)

# Sources section

set(TYPELIST_SOURCES
        include/_typelist/_typelist.hpp
        include/_typelist/_typeat.hpp
        include/_typelist/_length.hpp
        include/typelist.h)
set(READER_SOURCES
        include/_reader/_allocsize.hpp
        include/_reader/_reader.hpp
        include/_reader/_printer.hpp)

set(ALL_SOURCES
        ${TYPELIST_SOURCES}
        ${READER_SOURCES})


# Tests itself
set(TYPELIST_TESTS
        tests/typelist/typelist.cpp)
set(READER_TESTS
        tests/reader/reader.cpp)
set(TEST_SOURCES
        ${TYPELIST_TESTS}
        ${READER_TESTS}
        tests/run_tests.cpp)

SET(SOURCES
        ${ALL_SOURCES}
        ${TEST_SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Specify executable
add_executable(TypeListTest ${SOURCES})
target_link_libraries(TypeListTest libgtest libgmock)

install(TARGETS TypeListTest DESTINATION bin)
