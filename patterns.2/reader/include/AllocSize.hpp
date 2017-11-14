//
// Created by avk on 14.11.17.
//

#ifndef READER_ALLOCSIZE_H
#define READER_ALLOCSIZE_H

#include <cassert>
#include "typelist.h"

using std::string;
using std::cin;
using std::cout;
using Loki::Typelist;
using NullType = Loki::NullType;

template <typename TL>
struct AllocSize {};

template <>
struct AllocSize<Loki::NullType> {
    constexpr static std::size_t value = 0;
};

template <typename Head, typename Tail>
struct AllocSize<Loki::Typelist<Head, Tail>> {
    constexpr static std::size_t value = sizeof(Head) + AllocSize<Tail>::value;
};


#endif //READER_ALLOCSIZE_H
