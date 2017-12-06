cmake_minimum_required(VERSION 3.6)
project(TypeList)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE DEBUG)

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
        include/_typelist/_isempty.hpp
        include/_typelist/_contains.hpp
        include/typelist.h)
set(TYPELISTIO_SOURCES
        include/_typelistio/_allocsize.hpp
        include/_typelistio/_dumbreader.hpp
        include/_typelistio/_dumbprinter.hpp
        include/_typelistio/_reader.hpp
        include/_typelistio/_doubledecompressreader.hpp
        include/_typelistio/_nulltypes.hpp
        include/_typelistio/_readerutils.hpp
        include/_typelistio/_decompressreader.hpp
        include/typelistio.h )
set(GENERICFUNCTOR_SOURCES
        include/_genericfunctor/_genericfunctor.hpp
        include/genericfunctor.h)

set(ALL_SOURCES
        ${TYPELIST_SOURCES}
        ${TYPELISTIO_SOURCES}
        ${GENERICFUNCTOR_SOURCES})


# Tests itself
set(TESTS_AUX_SRC
        tests/reader/_aux/_aux.h
        tests/reader/_aux/_aux.cpp)
set(TYPELIST_TESTS
        tests/typelist/typelist_test.cpp)
set(READER_TESTS
        tests/reader/dumb_reader_test.cpp
        tests/reader/reader_test.cpp
        tests/reader/doubledecompressTest.cpp
        tests/reader/decompressTest.cpp)
set(GENERICFUNCTOR_TESTS
        tests/genericFunctor/genericfunctor_test.cpp)
set(TEST_SOURCES
        ${TESTS_AUX_SRC}
        ${TYPELIST_TESTS}
        ${READER_TESTS}
        ${GENERICFUNCTOR_TESTS}
        tests/run_tests.cpp)

SET(SOURCES
        ${ALL_SOURCES}
        ${TEST_SOURCES} include/_typelist/_equal.hpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Specify executable
add_executable(TypeListTest ${SOURCES})
target_link_libraries(TypeListTest libgtest libgmock)

install(TARGETS TypeListTest DESTINATION bin)
