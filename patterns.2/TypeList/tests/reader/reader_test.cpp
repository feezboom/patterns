//
// Created by avk on 20.11.17.
//

#include <sstream>
#include <gtest/gtest.h>
#include <typelistio.h>

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

    namespace int_ {

        typedef Divider<int, double, 1> toDouble;
        typedef Divider<int, long, 1> toLong;
        typedef Divider<int, int, 1> toInt;

        typedef Multiplier<int, double, 3> toDoubleTriple;
        typedef Multiplier<int, long, 3> toLongTriple;
        typedef Multiplier<int, int, 3> toIntTriple;

        typedef Divider<int, double, 3> toDoubleDivide3;
        typedef Divider<int, long, 3> toLongDivide3;
        typedef Divider<int, int, 3> toIntDivide3;

    }

    namespace double_ {

        typedef Divider<double, double, 1> toDouble;
        typedef Divider<double, long, 1> toLong;
        typedef Divider<double, int, 1> toInt;

        typedef Multiplier<double, double, 3> toDoubleTriple;
        typedef Multiplier<double, long, 3> toLongTriple;
        typedef Multiplier<double, int, 3> toIntTriple;

        typedef Divider<double, double, 3> toDoubleDivide3;
        typedef Divider<double, long, 3> toLongDivide3;
        typedef Divider<double, int, 3> toIntDivide3;

    }

    namespace long_ {

        typedef Divider<long, double, 1> toDouble;
        typedef Divider<long, long, 1> toLong;
        typedef Divider<long, int, 1> toInt;

        typedef Multiplier<long, double, 3> toDoubleTriple;
        typedef Multiplier<long, long, 3> toLongTriple;
        typedef Multiplier<long, int, 3> toIntTriple;

        typedef Divider<long, double, 3> toDoubleDivide3;
        typedef Divider<long, long, 3> toLongDivide3;
        typedef Divider<long, int, 3> toIntDivide3;
    }


}

// Implication for 2 booleans.
template<bool x, bool y>
struct Implication {
    constexpr static bool value = !x || y;
};

TEST(Reader, Main) {

    // use the list of generalized functions
    using F0 = transformers::Functor<transformers::int_::toIntDivide3, /*To*/int, /*From*/double>;
    using F1 = transformers::Functor<transformers::double_::toDoubleDivide3, /*To*/double, /*From*/int>;

    using ResultTypeList = TypeList<int, double>; // To
    using ReadTypeList = TypeList<double, int>; // From
    using DecompressorsTypeList = TypeList<F0, F1>;

    using reader = Reader<ResultTypeList, ReadTypeList, DecompressorsTypeList>;
//    reader();

    std::fstream test0("tests/reader/data/reader0.txt", std::ios_base::in);

    std::tuple<double, int> readLine = reader::readTypes(test0);
    ASSERT_EQ(std::get<0>(readLine), 8.3);
    ASSERT_EQ(std::get<1>(readLine), 5);


    std::tuple<int, double> decompressedLine = reader::readDecompressTypes(test0);
    ASSERT_EQ(std::get<0>(decompressedLine), int(4.1 / 3));
    ASSERT_EQ(std::get<1>(decompressedLine), 7 / 3.0);

}