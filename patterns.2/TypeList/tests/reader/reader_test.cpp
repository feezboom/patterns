#include <gtest/gtest.h>

#include <typelistio.h>


TEST(Reader, Main) {

    using GivenTypeList = TypeList<int, std::string, double>;

    std::ifstream is("tests/reader/data/hello.txt");

    std::stringstream stringstream;

    void *line0 = DumbReader<GivenTypeList>::nextLine(is);
    void *line1 = DumbReader<GivenTypeList>::nextLine(is);

    std::cout << std::endl;
    DumbPrinter<GivenTypeList>::printObjects(stringstream, line0, " ");
    stringstream << std::endl;
    DumbPrinter<GivenTypeList>::printObjects(stringstream, line1, " ");
    std::cout << stringstream.str() << std::endl;
};
