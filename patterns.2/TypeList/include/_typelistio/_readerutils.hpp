//
// Created by avk on 30.11.17.
//

#ifndef TYPELIST_READERUTILS_HPP
#define TYPELIST_READERUTILS_HPP

#include <istream>

class ReaderUtils {
public:
    template<typename R>
    static R readType(std::istream &is) {
        R res;
        is >> res;
        return res;
    }
};

#endif //TYPELIST_READERUTILS_HPP
