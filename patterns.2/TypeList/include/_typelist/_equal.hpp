//
// Created by avk on 16.11.17.
//

#ifndef TYPELIST_EQUAL_HPP
#define TYPELIST_EQUAL_HPP

#include <type_traits>
#include "typelist.h"

template<typename TL1, typename TL2>
struct Equal {
    constexpr static bool value = false;
};

template<typename Head2, typename ...Args2>
struct Equal<TypeList<>, TypeList<Head2, Args2...>> {
    constexpr static bool value = false;
};

template<typename Head1, typename ...Args1>
struct Equal<TypeList<Head1, Args1...>, TypeList<>> {
    constexpr static bool value = false;
};

template<>
struct Equal<TypeList<>, TypeList<>> {
    constexpr static bool value = true;
};


template<typename Head1, typename Head2, typename ...Args1, typename ...Args2>
struct Equal<TypeList<Head1, Args1...>, TypeList<Head2, Args2...>> {
    constexpr static bool value =
            std::is_same<Head1, Head2>::value &&
            Equal<TypeList<Args1...>, TypeList<Args2...>>::value;
};


#endif //TYPELIST_EQUAL_HPP
