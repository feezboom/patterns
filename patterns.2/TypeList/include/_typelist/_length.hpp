//
// Created by avk on 15.11.17.
//

#ifndef TYPELIST_LENGTH_H
#define TYPELIST_LENGTH_H

#include "_typelist.hpp"

template<typename TL>
struct [[deprecated]] TLLength;

template<typename ZeroType, typename ...Args>
struct [[deprecated]] TLLength<TypeList<ZeroType, Args...>> {
    constexpr static std::size_t value = TLLength<TypeList<Args...>>::value + 1;
};

template<>
struct [[deprecated]] TLLength<TypeList<>> {
    constexpr static std::size_t value = 0;
};

template<typename TL>
struct Length;

template<typename ...Args>
struct Length<TypeList<Args...>> {
    constexpr static std::size_t value = sizeof... (Args);
};


template<typename ...TLs>
struct SameLength {
    constexpr static bool value = true;
};

template<typename TL0, typename TL1, typename ... TLs>
struct SameLength<TL0, TL1, TLs...> {
    constexpr static bool value = (Length<TL0>::value == Length<TL1>::value) && SameLength<TL1, TLs...>::value;
};

#endif //TYPELIST_LENGTH_H
