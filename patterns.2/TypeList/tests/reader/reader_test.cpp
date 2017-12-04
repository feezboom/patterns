//
// Created by avk on 20.11.17.
//

#include <sstream>
#include <string>
#include <gtest/gtest.h>
#include <typelistio.h>
#include <_typelistio/_decompressreader.hpp>

namespace transformers {

    template<typename From, typename To, int _divider>
    struct Divider {
        To operator()(From x) {
            return static_cast<To>(x / _divider);
        }
    };

    template<typename From, typename To, int _multiplier>
    struct Multiplier {
        To operator()(From x) {
            return static_cast<To>(x * _multiplier);
        }
    };

    template<typename R>
    std::string toString(const R &x) {
        std::stringstream sstream;
        sstream << x;
        return sstream.str();
    }

    template<typename Function, typename To, typename ...FromArgs>
    class Functor : public GenericFunctor<To, TypeList<FromArgs...>> {
    public:
        Functor() : GenericFunctor<To, TypeList<FromArgs...>>(Function()) {};
    };

    struct SuperIntInt {
        int decompress() {
            return x*2;
        }
        int x;
    };

    std::istream &operator>>(std::istream &is, SuperIntInt &sii) {
        is >> sii.x;
    }

    struct SuperDoubleInt {
        int decompress() {
            return int(x * 2);
        }

        double x;
    };

    std::istream &operator>>(std::istream &is, SuperDoubleInt &sd) {
        is >> sd.x;
    }


    struct SuperIntDouble {
        double decompress() {
            return x * 2.0;
        }

        int x;
    };

    std::istream &operator>>(std::istream &is, SuperIntDouble &si) {
        is >> si.x;
    }


    struct SuperIntString {
        std::string decompress() {
            std::stringstream ss;
            ss << (x * 2);
            return ss.str();
        }

        int x;
    };

    std::istream &operator>>(std::istream &is, SuperIntString &sis) {
        is >> sis.x;
    }

}


TEST(Reader, main) {

    using ResultTypeList = TypeList<double, int>; // To

    std::fstream test0("tests/reader/data/reader0.txt", std::ios_base::in);

    std::tuple<double, int> readLine = Reader<ResultTypeList>::readTypes(test0);
    ASSERT_EQ((std::get<0>(readLine)), 8.3);
    ASSERT_EQ((std::get<1>(readLine)), 5);

}

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

    source.close();
}

TEST(DoubleDecompressReader, main) {
    // Decompress available types
    using transformers::SuperIntInt;
    using transformers::SuperDoubleInt;
    using transformers::SuperIntDouble;
    using transformers::SuperIntString;

    // Decompress functors
    auto intDouble = [](int x) -> double {
        return x * 2.0;
    };

    auto doubleInt = [](double x) -> int {
        return (int) (x * 2);
    };

    auto intString = [](int x) -> std::string {
        std::stringstream ss;
        ss << (x * 2);
        return ss.str();
    };

    auto stringInt = [](std::string x) -> int {
        return std::stoi(x);
    };


    using IntDoubleFunctor = GenericFunctor<double, TypeList<int>>;
    using DoubleIntFunctor = GenericFunctor<int, TypeList<double>>;
    using IntStringFunctor = GenericFunctor<std::string, TypeList<int>>;
    using StringIntFunctor = GenericFunctor<int, TypeList<std::string>>;

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
    std::tuple<int, double, std::string> r = DDR::readTypes(ddr0, f0, f1, f2);




}