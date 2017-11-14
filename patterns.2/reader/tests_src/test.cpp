#include <string>
#include <iostream>

#include "../include/reader.hpp"
#include "../include/printer.hpp"


int main() {

    using GivenTypeList = Loki::TL::MakeTypelist<int, std::string, double>::Result;

    std::ifstream is("../tests/hello.txt");

    void* ptr = Reader<GivenTypeList>::nextLine(is);
    Printer<GivenTypeList>::printObjects(std::cout, ptr, " ");

    return 0;
};
