//
// Created by Karyamin_A on 06.12.2017.
//
#include <gtest/gtest.h>
#include "_aux/_aux.h"


TEST(DecompressReader, main) {

    auto half = [](int x) -> double {
        return x / 2.0;
    };

    auto triple = [](double x) -> int {
        return (int) (x * 3);
    };

    auto quadruple = [](double x) -> double {
        return x * 4;
    };


    using transformers::SuperDoubleInt;
    using transformers::SuperIntDouble;
    using transformers::SuperIntString;

    using DoubleToDouble = GenericFunctor<double, TypeList<double>>;

    using TL1 = TypeList<int, double, std::string>;
    using TL2 = TypeList<SuperDoubleInt, /*SuperIntDouble*/NullType, SuperIntString>;
    using TL3 = TypeList<NullFunctor, /*NullFunctor*/DoubleToDouble, NullFunctor>;

    using DR = DecompressReader<TL1, TL2, TL3>;

    std::fstream source("tests/reader/data/dr0.txt", std::ios_base::in);

    auto t1 = NullType();

    auto nf = NullFunctor();
    auto resTuple = DR::readTypes(source, nf, DoubleToDouble(quadruple), nf);

    ASSERT_EQ(std::get<0>(resTuple), 11);
    ASSERT_EQ(std::get<1>(resTuple), 92);
    ASSERT_EQ(std::get<2>(resTuple), "14");

    source.close();
}
