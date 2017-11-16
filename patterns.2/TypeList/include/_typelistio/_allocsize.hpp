//
// Created by avk on 14.11.17.
//

#ifndef READER_ALLOCSIZE_H
#define READER_ALLOCSIZE_H

#include <cassert>
#include <typelist.h>

template <typename TL>
struct AllocSize {};

template <>
struct AllocSize<TypeList<>> {
    constexpr static std::size_t value = 0;
};

template<typename Head, typename ...Args>
struct AllocSize<TypeList<Head, Args...>> {
    constexpr static std::size_t value = sizeof(Head) + AllocSize<TypeList<Args...>>::value;
};

#endif //READER_ALLOCSIZE_H
