//
// Created by Karyamin_A on 06.12.2017.
//

#ifndef TYPELIST_AUX_H
#define TYPELIST_AUX_H

#include <istream>
#include <string>
#include <sstream>

#include <typelist.h>
#include <typelistio.h>

namespace transformers {

    struct SuperIntInt {
        int decompress();
        int x;
    };

    std::istream &operator>>(std::istream &is, SuperIntInt &sii);

    struct SuperDoubleInt {
        int decompress();

        double x;
    };

    std::istream &operator>>(std::istream &is, SuperDoubleInt &sd);


    struct SuperIntDouble {
        double decompress();

        int x;
    };

    std::istream &operator>>(std::istream &is, SuperIntDouble &si);


    struct SuperIntString {
        std::string decompress();

        int x;
    };

    std::istream &operator>>(std::istream &is, SuperIntString &sis);

}


// Decompress available types
using transformers::SuperIntInt;
using transformers::SuperDoubleInt;
using transformers::SuperIntDouble;
using transformers::SuperIntString;

// Decompress functors
static auto intDouble = [](int x) -> double {
    return x * 2.0;
};

static auto doubleInt = [](double x) -> int {
    return (int) (x * 2);
};

static auto intString = [](int x) -> std::string {
    std::stringstream ss;
    ss << (x * 2);
    return ss.str();
};

static auto stringInt = [](std::string x) -> int {
    int r = std::stoi(x) * 2;
    return r;
};

static auto intInt = [](int x) -> int {
    return x*2;
};


using IntDoubleFunctor = GenericFunctor<double, TypeList<int>>;
using DoubleIntFunctor = GenericFunctor<int, TypeList<double>>;
using IntStringFunctor = GenericFunctor<std::string, TypeList<int>>;
using StringIntFunctor = GenericFunctor<int, TypeList<std::string>>;
using IntIntFunctor    = GenericFunctor<int, TypeList<int>>;

#endif //TYPELIST_AUX_H
