//
// Created by avk on 20.11.17.
//

#ifndef TYPELIST__READER_HPP
#define TYPELIST__READER_HPP

#include <typelist.h>
#include <genericfunctor.h>
#include <tuple>

#include <_typelistio/_nulltypes.hpp>
#include <_typelistio/_readerutils.hpp>


template<typename ResTL>
class Reader {
};


template<typename ResHead, typename ...ResArgs>
class Reader<TypeList<ResHead, ResArgs...>> {
public:
    // Reader for one template argument
    template<typename T1>
    using OneArgReader = Reader<TypeList<T1>>;

    // Arguments tails typeLists
    using ResTail = TypeList<ResArgs...>;

    // Reader parametrized by head & tail
    using HeadReader = OneArgReader<ResHead>;
    using TailReader = Reader<ResTail>;

public:

    static std::tuple<ResHead, ResArgs...> readTypes(std::istream &is) {
        std::tuple < ResHead > head = std::make_tuple(ReaderUtils::readType<ResHead>(is));
        std::tuple<ResArgs...> tailTuple = TailReader::readTypes(is);
        return std::tuple_cat(head, tailTuple);
    }

};

template<>
class Reader<TypeList<>> {
public:
    constexpr static bool everythingCorrect = true;

    static std::tuple<> readTypes(std::istream &is) {
        return std::make_tuple<>();
    }

};


#endif //TYPELIST__READER_HPP
