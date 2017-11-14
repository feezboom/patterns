//
// Created by avk on 15.11.17.
//

#ifndef TYPELIST_LENGTH_H
#define TYPELIST_LENGTH_H

#include "_typelist.hpp"

template <typename TL>
struct Length { };

template <typename ZeroType, typename ...Args>
struct Length<TypeList<ZeroType, Args...>> {
    constexpr static std::size_t Result = Length<TypeList<Args...>>::Result + 1;
};

template <>
struct Length<TypeList<>> {
    constexpr static std::size_t Result = 0;
};

#endif //TYPELIST_LENGTH_H
