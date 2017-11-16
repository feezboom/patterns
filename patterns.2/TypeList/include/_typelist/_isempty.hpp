//
// Created by avk on 16.11.17.
//

#ifndef TYPELIST_ISEMPTY_HPP
#define TYPELIST_ISEMPTY_HPP

#include <type_traits>
#include "_typelist.hpp"

template<typename TL>
struct IsEmpty {
    constexpr static bool value = true;
};

template<typename Head, typename ...Args>
struct IsEmpty<TypeList<Head, Args...>> {
    constexpr static bool value = false;
};

#endif //TYPELIST_ISEMPTY_HPP
