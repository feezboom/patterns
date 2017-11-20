#include <gtest/gtest.h>

#include <typelistio.h>


TEST(Reader, Main) {

    using GivenTypeList = TypeList<int, std::string, double>;

    std::ifstream is("tests/reader/data/hello.txt");

    std::shared_ptr<void> line0 = DumbReader<GivenTypeList>::nextLine(is);
    std::shared_ptr<void> line1 = DumbReader<GivenTypeList>::nextLine(is);

    std::stringstream stringstream;
    DumbPrinter<GivenTypeList>::printObjects(stringstream, line0.get(), " ");
    ASSERT_EQ("50 hello 1.5 ", stringstream.str());

    stringstream.str("");
    DumbPrinter<GivenTypeList>::printObjects(stringstream, line1.get(), " ");
    ASSERT_EQ("25 world 0.75 ", stringstream.str());
};
