//
// Created by avk on 20.11.17.
//

#include <sstream>
#include <gtest/gtest.h>

#include "_aux/_aux.h"

TEST(Reader, main) {

    using ResultTypeList = TypeList<double, int>; // To

    std::fstream test0("tests/reader/data/reader0.txt", std::ios_base::in);

    std::tuple<double, int> readLine = Reader<ResultTypeList>::readTypes(test0);
    ASSERT_EQ((std::get<0>(readLine)), 8.3);
    ASSERT_EQ((std::get<1>(readLine)), 5);

}
