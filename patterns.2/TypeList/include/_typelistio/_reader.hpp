//
// Created by avk on 20.11.17.
//

#ifndef TYPELIST__READER_HPP
#define TYPELIST__READER_HPP

#include <typelist.h>
#include <genericfunctor.h>
#include <tuple>

class NullFunc {
};

class NullType {
};

template<typename ResTL, typename GivenTL, typename FuncTL>
class Reader {
    static_assert(SameLength<ResTL, GivenTL, FuncTL>::value);
};


template<typename ResHead, typename ...ResArgs,
        typename ToReadHead, typename ...ToReadArgs,
        typename FuncHead, typename ...FuncArgs>
class Reader
        <
                TypeList<ResHead, ResArgs...>,
                TypeList<ToReadHead, ToReadArgs...>,
                TypeList<FuncHead, FuncArgs...>
        > {
public:
    // Arguments tails typelists
    using ResTail = TypeList<ResArgs...>;
    using ToReadTail = TypeList<ToReadArgs...>;
    using FuncTail = TypeList<FuncArgs...>;

    // Reader parametrized by head & tail
    using TailReader = Reader<ResTail, ToReadTail, FuncTail>;

    using ExpectedHeadFunctor = GenericFunctor<ResHead, TypeList<ToReadHead>>;

    constexpr static bool headFunctorCorrect =
            (std::is_base_of<FuncHead, ExpectedHeadFunctor>::value ||
             std::is_base_of<ExpectedHeadFunctor, FuncHead>::value ||
             std::is_same<FuncHead, NullFunc>::value);
    static_assert(headFunctorCorrect, "wrong template functor given");

    constexpr static bool headResIsNotNullType = !std::is_same<ResHead, NullType>::value;
    static_assert(headResIsNotNullType, "resulting type can not be NullType");

    constexpr static bool headCorrect = headFunctorCorrect && headResIsNotNullType;
    constexpr static bool everythingCorrect = headCorrect && TailReader::everythingCorrect;

public:
    static std::shared_ptr<void> nextLine(std::istream &is) {
        static constexpr std::size_t allocSize = sizeof(ResHead) + sizeof... (ResArgs);
    }

public:
    static std::tuple<ResHead, ResArgs...> _readObjects(std::istream &is, void *ptr) {

        ToReadHead obj;
        is >> obj;

        ResHead objRes = FuncHead()(obj);
        return std::tuple_cat(std::make_tuple(obj), TailReader::_readObjects(is, ptr));
    }

};

template<>
class Reader<TypeList<>, TypeList<>, TypeList<>> {
public:
    constexpr static bool everythingCorrect = true;

    static std::tuple<> _readObjects(std::istream &is, void *ptr) {
        return std::make_tuple<>();
    }

};

#endif //TYPELIST__READER_HPP
