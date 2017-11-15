#include <gtest/gtest.h>

#include <_reader/_reader.hpp>


TEST(Reader, Main) {

    using GivenTypeList = TypeList<int, std::string, double>;

    std::ifstream is("tests/reader/data/hello.txt");

    void* ptr = Reader<GivenTypeList>::nextLine(is);
//    Printer<GivenTypeList>::printObjects(std::cout, ptr, " ");

};
