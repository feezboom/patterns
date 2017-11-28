#include <gtest/gtest.h>
#include <memory>
#include <typelistio.h>


TEST(DumbReader, Main) {

    using GivenTypeList = TypeList<int, std::string, double>;

    std::ifstream is("tests/reader/data/dumb.txt");

    std::shared_ptr<void> line0 = DumbReader<GivenTypeList>::readTypes(is);
    std::shared_ptr<void> line1 = DumbReader<GivenTypeList>::readTypes(is);

    std::stringstream stringstream;
    DumbPrinter<GivenTypeList>::printObjects(stringstream, line0.get(), " ");
    ASSERT_EQ("50 hello 1.5 ", stringstream.str());

    stringstream.str("");
    DumbPrinter<GivenTypeList>::printObjects(stringstream, line1.get(), " ");
    ASSERT_EQ("25 world 0.75 ", stringstream.str());
}
