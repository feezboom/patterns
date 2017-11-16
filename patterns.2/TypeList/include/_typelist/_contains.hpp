//
// Created by avk on 16.11.17.
//

#ifndef TYPELIST_CONTAINS_HPP
#define TYPELIST_CONTAINS_HPP

#include <type_traits>
#include "_typelist.hpp"

template<typename T, typename TL>
struct Contains {
};


template<typename T, typename Head, typename ...Args>
struct Contains<T, TypeList<Head, Args...>> {
    constexpr static bool value =
            std::is_same<T, Head>::value ||
            Contains<T, TypeList<Args...>>::value;
};


template<typename T, typename Head>
struct Contains<T, TypeList<Head>> {
    constexpr static bool value = std::is_same<T, Head>::value;
};


template<typename T>
struct Contains<T, TypeList<>> {
    constexpr static bool value = false;
};

#endif //TYPELIST_CONTAINS_HPP
