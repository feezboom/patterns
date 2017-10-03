//
// Created by avk on 26.09.17.
//

#ifndef TYPELIST_TYPELIST_H
#define TYPELIST_TYPELIST_H

#include <type_traits>

using std::is_same;
using std::integral_constant;
using std::true_type;
using std::false_type;

namespace typelist {

    // Defining empty node.
    struct EmptyNode {
    };

    // Definition
    template<typename ... Args>
    struct TypeList {
        typedef EmptyNode _head;
        typedef EmptyNode _tail;
    };

    typedef TypeList<> EmptyTypeList;

    template<typename H, typename ...Args>
    struct TypeList<H, Args...> {
        typedef H _head;
        typedef TypeList<Args...> _tail;
    };


    // Is empty
    template<typename ... Args>
    struct IsEmpty : true_type {
    };

    template<>
    struct IsEmpty<EmptyTypeList> : true_type {
    };

    template<typename ... Args>
    struct IsEmpty<TypeList<Args...>> :
            std::integral_constant<bool, is_same<typename TypeList<Args...>::_head, EmptyNode>::value
                                         && IsEmpty<typename TypeList<Args...>::_tail>::value> {
    };


    // Add
    template <typename T, typename TypeList>
    struct Add {};

    template <typename T, typename ... Args>
    struct Add<T, TypeList<Args ...>> {
        typedef TypeList<Args ..., T> newType;
    };

    // Append
    template <typename T, typename TypeList>
    struct Append {};

    template <typename ... Args1, typename ... Args2>
    struct Append<TypeList<Args1 ...>, TypeList<Args2 ...>> {
        typedef TypeList<Args1 ..., Args2 ...> newType;
    };

    // Getting last type : GetLast
    template <typename ... Args>
    struct GetLast {};

    template <>
    struct GetLast<> {
        typedef EmptyNode type;
    };

    template<typename T>
    struct GetLast<TypeList<T>> {
        typedef T type;
    };

    template <typename T, typename ... Args>
    struct GetLast<TypeList<T, Args ...>> {
        typedef GetLast<TypeList<Args ...>> type;
    };

    template <std::size_t N, typename ... Args>
    struct At {};

    template <std::size_t N>
    struct At<N> {
        typedef EmptyNode valueType;
    };

    template <std::size_t N, typename T, typename ... Args>
    struct At<N, T, Args...> {
        typedef typename At<N-1, Args...>::valueType valueType;
    };


    template <typename T, typename ... Args>
    struct At<0, T, Args...> {
        typedef T valueType;
    };

    template <typename ... Args>
    struct ArgsLen {};

    template <typename T, typename ... Args>
    struct ArgsLen<T, Args...> {
        static constexpr size_t value = ArgsLen<Args...>::value + 1;
    };

    template <>
    struct ArgsLen<> {
        static constexpr size_t value = 0;
    };
}

#endif //TYPELIST_TYPELIST_H
