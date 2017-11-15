//
// Created by avk on 14.11.17.
//

#ifndef READER_PRINTER_H
#define READER_PRINTER_H

#include <istream>
#include <cassert>

#include <typelist.h>

template <typename TL, std::size_t shift>
struct _PrintInternal {

    template <typename SeparatorType>
    static void _printObjects(std::ostream &os, const void *ptr, SeparatorType sep) {
        assert(false);
    }
};

template<typename Head, typename ...Args, std::size_t shift>
struct _PrintInternal<TypeList<Head, Args...>, shift> {

    template <typename SeparatorType>
    static void _printObjects(std::ostream &os, const void *ptr, SeparatorType sep) {
        _PrintInternal<TypeList<Head>, shift>::_printObjects(os, ptr, sep);
        _PrintInternal<TypeList<Args...>, shift + sizeof(Head)>::_printObjects(os, ptr, sep);
    }
};

template <typename Head, std::size_t shift>
struct _PrintInternal<TypeList<Head>, shift> {

    template <typename SeparatorType>
    static void _printObjects(std::ostream &os, const void *ptr, SeparatorType sep) {
        const Head* objPtr = static_cast<const Head*>(ptr+shift);
        os << *objPtr << sep;
    }
};


template <typename TL>
class Printer {
public:

    template<typename SeparatorType>
    static void printObjects(std::ostream &os, const void *ptr, SeparatorType sep) {
        _PrintInternal<TL, 0>::_printObjects(os, ptr, sep);
    };
};

#endif //READER_PRINTER_H
