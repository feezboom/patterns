//
// Created by avk on 14.11.17.
//

#ifndef READER_PRINTER_H
#define READER_PRINTER_H

#include <istream>
#include <cassert>

#include <typelist.h>

template<typename TypeList_type>
class DumbPrinter {
public:

    template<typename SeparatorType>
    static void printObjects(std::ostream &os, const void *ptr, SeparatorType sep) {
        _DumbPrintInternal<TypeList_type, 0>::_printObjects(os, ptr, sep);
        os << std::flush;
    };
private:
    template<typename TL, std::size_t shift>
    struct _DumbPrintInternal {

        template<typename SeparatorType>
        static void _printObjects(std::ostream &os, const void *ptr, SeparatorType sep) {
            assert(false);
        }
    };

    template<typename Head, typename ...Args, std::size_t shift>
    struct _DumbPrintInternal<TypeList<Head, Args...>, shift> {

        template<typename SeparatorType>
        static void _printObjects(std::ostream &os, const void *ptr, SeparatorType sep) {
            _DumbPrintInternal<TypeList<Head>, shift>::_printObjects(os, ptr, sep);
            _DumbPrintInternal<TypeList<Args...>, shift + sizeof(Head)>::_printObjects(os, ptr, sep);
        }
    };

    template<typename Head, std::size_t shift>
    struct _DumbPrintInternal<TypeList<Head>, shift> {

        template<typename SeparatorType>
        static void _printObjects(std::ostream &os, const void *ptr, SeparatorType sep) {
            const Head *objPtr = static_cast<const Head *>(ptr + shift);
            os << *objPtr << sep;
        }
    };

};

#endif //READER_PRINTER_H
