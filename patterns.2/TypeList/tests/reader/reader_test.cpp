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

    template<typename F, typename R, typename ...Args>
    class Functor : public GenericFunctor<R, TypeList<Args...>> {
    public:
        Functor() : GenericFunctor<R, TypeList<Args...>>(F()) {};
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


TEST(Reader, Main) {

    // use the list of generalized functions
    using F1 = transformers::Functor<transformers::int_::toDoubleDivide3, double, int>;
    using F2 = transformers::Functor<transformers::double_::toIntDivide3, int, double>;

    using ReadTypeList = TypeList<int, double>;
    using ResultTypeList = TypeList<double, int>;
    using DecompressorsTypeList = TypeList<F1, F2>;

    Reader<ResultTypeList, ReadTypeList, DecompressorsTypeList> reader;

}