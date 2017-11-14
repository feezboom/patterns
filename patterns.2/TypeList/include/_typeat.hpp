//
// Created by avk on 15.11.17.
//

#ifndef TYPELIST_TYPEAT_H
#define TYPELIST_TYPEAT_H

#include "_typelist.hpp"

template <std::size_t n, typename TL>
struct TypeAt {};

template <typename ZeroType, typename ...Args, std::size_t n>
struct TypeAt <n, TypeList<ZeroType, Args...>> {
using Result = typename TypeAt<n-1, TypeList<Args...>>::Result;
};

template <typename ZeroType, typename ...Args>
struct TypeAt<0, TypeList<ZeroType, Args...>> {
using Result = ZeroType;
};

template <std::size_t n>
struct TypeAt<n, TypeList<>> {
    using Result = EmptyType;
};

#endif //TYPELIST_TYPEAT_H
