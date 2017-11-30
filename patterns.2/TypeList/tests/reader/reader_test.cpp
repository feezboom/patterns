//
// Created by avk on 20.11.17.
//

#include <sstream>
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
            return double(x / 2.0);
        }

        int x;
    };

    std::istream &operator>>(std::istream &is, SuperIntDouble &si) {
        is >> si.x;
    }


    struct SuperIntString {
        std::string decompress() {
            std::stringstream ss;
            ss >> x;
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


    using HALF = decltype(half);
    using TRIPLE = decltype(triple);
    using TOSTRING = decltype(transformers::toString<int>);

    using transformers::SuperDoubleInt;
    using transformers::SuperIntDouble;
    using transformers::SuperIntString;

    using TL1 = TypeList<int, double, std::string>;
    using TL2 = TypeList<SuperDoubleInt, SuperIntDouble, SuperIntString>;
    using TL3 = TypeList<SingleArgNullFunc, SingleArgNullFunc, SingleArgNullFunc>;

    using DR = DecompressReader<TL1, TL2, TL3>;

    std::fstream source("tests/reader/data/dr0.txt", std::ios_base::in);

    auto f1 = SingleArgNullFunc < int, SuperDoubleInt>();
    auto f2 = SingleArgNullFunc < double, SuperIntDouble>();
    auto f3 = SingleArgNullFunc<std::string, SuperIntString>();
    auto resTuple = DR::readTypes(source, f1, f2, f3);

    source.close();

//    using DDR = DoubleDecompressReader<
}

TEST(DoubleDecompressReader, main) {

}