//
// Created by Karyamin_A on 06.12.2017.
//

#include <gtest/gtest.h>

#include "_aux/_aux.h"


TEST(DoubleDecompressReader, main0) {
    // final result types
    using TL1 = TypeList<int, double, std::string>; // Get finally
    // reads (int, double, int) gives (double, int, int)
    using TL2 = TypeList<SuperIntDouble, SuperDoubleInt, SuperIntInt>;
    // takes (double, int, int) gives (int, double, string)
    using TL3 = TypeList<DoubleIntFunctor, IntDoubleFunctor, IntStringFunctor>; // get from tl2 -> transform

    auto f0 = DoubleIntFunctor(doubleInt);
    auto f1 = IntDoubleFunctor(intDouble);
    auto f2 = IntStringFunctor(intString);

    using DDR = DoubleDecompressReader<TL1, TL2, TL3>;

    // test with (int, double, int) needed

    std::fstream ddr0("tests/reader/data/ddr0.txt", std::ios_base::in);
    auto r = DDR::readTypes(ddr0, f0, f1, f2);

    ASSERT_EQ(std::get<0>(r), 8);
    ASSERT_EQ(std::get<1>(r), 10);
    ASSERT_EQ(std::get<2>(r), "12");

}



TEST(DoubleDecompressReader, FunctorNull) {
    // final result types
    using TL1 = TypeList<int, double, std::string>; // Get finally
    using TL2 = TypeList<SuperIntDouble, SuperDoubleInt, SuperIntString>;
    using TL3 = TypeList<DoubleIntFunctor, IntDoubleFunctor, NullFunctor>; // get from tl2 -> transform

    auto f0 = DoubleIntFunctor(doubleInt);
    auto f1 = IntDoubleFunctor(intDouble);
    auto f2 = NullFunctor();

    using DDR = DoubleDecompressReader<TL1, TL2, TL3>;

    // test with (int, double, int) needed

    std::fstream ddr0("tests/reader/data/ddr0.txt", std::ios_base::in);
    auto r = DDR::readTypes(ddr0, f0, f1, f2);

    ASSERT_EQ(std::get<0>(r), 8);
    ASSERT_EQ(std::get<1>(r), 10);
    ASSERT_EQ(std::get<2>(r), "6");

}


TEST(DoubleDecompressReader, DecompressTypeNull) {
    // final result types
    using TL1 = TypeList<int, double, int>; // Get finally
    using TL2 = TypeList<SuperIntDouble, SuperDoubleInt, NullType>;
    using TL3 = TypeList<DoubleIntFunctor, IntDoubleFunctor, IntIntFunctor>; // get from tl2 -> transform

    auto f0 = DoubleIntFunctor(doubleInt);
    auto f1 = IntDoubleFunctor(intDouble);
    auto f2 = IntIntFunctor(intInt);

    using DDR = DoubleDecompressReader<TL1, TL2, TL3>;

    // test with (int, double, string) needed

    std::fstream ddr0("tests/reader/data/ddr0.txt", std::ios_base::in);
    std::tuple<int, double, int> r = DDR::readTypes(ddr0, f0, f1, f2);

    ASSERT_EQ(std::get<0>(r), 8);
    ASSERT_EQ(std::get<1>(r), 10);
    ASSERT_EQ(std::get<2>(r), 6);

}
