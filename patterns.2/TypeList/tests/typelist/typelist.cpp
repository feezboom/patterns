//
// Created by avk on 15.11.17.
//

#include <gtest/gtest.h>

#include <typelist.h>

TEST(TypeList, Main) {

    using myTypeList = TypeList<int, double, float, char>;
    std::cout << typeid(TypeAt<0, myTypeList>::Result).name() << std::endl;
    std::cout << Length<myTypeList>::Result;
}