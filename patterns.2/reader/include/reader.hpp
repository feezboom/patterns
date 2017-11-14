//
// Created by avk on 14.11.17.
//

#ifndef READER_READER_H
#define READER_READER_H

#include "typelist.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

#include "AllocSize.hpp"




template <typename TL, std::size_t shift>
struct _ReaderInternal {
    static void readObjects(std::istream &is, void *ptr) {
        assert(false);
    };
};

template <typename Head, typename Tail, std::size_t shift>
struct _ReaderInternal<Typelist<Head, Tail>, shift> {
    static void readObjects(std::istream &is, void *ptr) {
        constexpr std::size_t shift_ = shift;

        _ReaderInternal<Typelist<Head, NullType>, shift>::readObjects(is, ptr);
        _ReaderInternal<Tail, shift + sizeof(Head)>::readObjects(is, ptr);
    }
};

template <typename Head, std::size_t shift>
struct _ReaderInternal<Typelist<Head, NullType>, shift> {
    static void readObjects(std::istream &is, void *ptr) {
        Head tempObj;
        is >> tempObj;

        Head* objPtr = static_cast<Head*>(ptr + shift);
        *objPtr = tempObj;
    }
};

template <typename TL>
class Reader {
public:
    static void* nextLine(std::istream& is) {
        constexpr std::size_t alloc_size = AllocSize<TL>::value;
        void* ptr = malloc(alloc_size);
        _ReaderInternal<TL, 0>::readObjects(is, ptr);
        return ptr;
    }
};
#endif //READER_READER_H
