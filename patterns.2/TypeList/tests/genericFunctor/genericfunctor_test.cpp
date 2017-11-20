//
// Created by avk on 16.11.17.
//

#include <gtest/gtest.h>
#include <genericfunctor.h>


auto f0 = []() -> int {
    return 2;
};
auto f1 = [](int x) -> int {
    return x + 1;
};
auto f2 = [](int x, double y) -> double {
    return x + y;
};
auto f3 = [](int x, double y, const std::string &z) -> std::string {
    std::stringstream sstream;
    sstream << x << y << z;
    return sstream.str();
};
auto f4 = [](char x, int y, int z, std::vector<int> &v) -> char {
    return x + (char) 1;
};
auto f5 = [](char x, int y, int z, std::vector<int> &v, std::vector<std::string> &v0) -> char {
    return x + (char) 2;
};


TEST(GenericFunctor, Main) {

    GenericFunctor<int, TypeList<>> F0(f0);
    GenericFunctor<int, TypeList<int>> F1(f1);
    GenericFunctor<double, TypeList<int, double>> F2(f2);
    GenericFunctor<std::string, TypeList<int, double, const std::string &>> F3(f3);
    GenericFunctor<char, TypeList<char, int, int, std::vector<int> &>> F4(f4);
    GenericFunctor<char, TypeList<char, int, int, std::vector<int> &, std::vector<std::string> &>> F5(f5);

    std::vector<int> vi;
    std::vector<std::string> vs;

    ASSERT_EQ(F0(), 2);
    ASSERT_EQ(F1(2), 3);
    ASSERT_EQ(F2(2, 2.5), 4.5);
    ASSERT_EQ(F3(1, 2, "3"), "123");
    ASSERT_EQ(F4('a', 1, 2, vi), 'b');
    ASSERT_EQ(F5('a', 1, 2, vi, vs), 'c');


    GenericFunctor<int, TypeList<>> FF0(F0);
    GenericFunctor<int, TypeList<int>> FF1(F1);
    GenericFunctor<double, TypeList<int, double>> FF2(F2);
    GenericFunctor<std::string, TypeList<int, double, const std::string &>> FF3(F3);
    GenericFunctor<char, TypeList<char, int, int, std::vector<int> &>> FF4(F4);
    GenericFunctor<char, TypeList<char, int, int, std::vector<int> &, std::vector<std::string> &>> FF5(F5);

    ASSERT_EQ(F0(), FF0());
    ASSERT_EQ(F1(2), FF1(2));
    ASSERT_EQ(F2(2, 2.5), FF2(2, 2.5));
    ASSERT_EQ(F3(1, 2, "3"), FF3(1, 2, "3"));
    ASSERT_EQ(F4('a', 1, 2, vi), FF4('a', 1, 2, vi));
    ASSERT_EQ(F5('a', 1, 2, vi, vs), FF5('a', 1, 2, vi, vs));

}
