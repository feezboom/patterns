//
// Created by avk on 30.11.17.
//

#ifndef TYPELIST_DOUBLEDECOMPRESSREADER_HPP
#define TYPELIST_DOUBLEDECOMPRESSREADER_HPP

#include <istream>
#include <tuple>

#include <typelist.h>
#include <_typelistio/_nulltypes.hpp>

template<typename TL1, typename TL2, typename TL3>
class DoubleDecompressReader;

template<typename ResHead, typename ...ResArgs,
        typename ToReadHead, typename ...ToReadArgs,
        typename FuncHead, typename ...FuncArgs>
class DoubleDecompressReader
        <
                TypeList<ResHead, ResArgs...>,
                TypeList<ToReadHead, ToReadArgs...>,
                TypeList<FuncHead, FuncArgs...>
        > {
// Reader for one template argument
    template<typename T1, typename T2, typename T3>
    using OneArgReader = DoubleDecompressReader<TypeList<T1>, TypeList<T2>, TypeList<T3>>;

// Reader parametrized by head & tail
    using DDHeadReader = OneArgReader<ResHead, ToReadHead, FuncHead>;
    using DDTailReader = DoubleDecompressReader<
            TypeList<ResArgs...>,
            TypeList<ToReadArgs...>,
            TypeList<FuncArgs...>>;
//    using NullFunc = NullFunctor<ResHead, ToReadHead>;

public:
    static std::tuple<ResHead, ResArgs...> readTypes(std::istream &is, FuncHead fHead, FuncArgs &&... fArgs) {

        std::tuple < ResHead > head = DDHeadReader::_readFirstType(is, fHead);
        std::tuple<ResArgs...> tail = DDTailReader::readTypes(is, fArgs...);

        return std::tuple_cat(head, tail);
    };

private:
    static std::tuple<ResHead> _readFirstType(std::istream &is, FuncHead &&f) {

        bool doTypeDecompression = std::is_same<ToReadHead, NullType>::value;
        bool doFunctorDecompression = std::is_same<FuncHead, NullFunctor>::value;

        ResHead res;
        ToReadHead readHead;

        using TypeDecompressionResult = decltype(readHead.decompress());
        TypeDecompressionResult r0;

        if (doTypeDecompression) {
            is >> readHead;
            r0 = readHead.decompress();
        } else {
            is >> res;
        }

        if (doFunctorDecompression) {
            if (doTypeDecompression) {
                res = f(r0);
            } else {
                res = f(res);
            }
        }

        return std::make_tuple(res);
    }

};

template<>
class DoubleDecompressReader<TypeList<>, TypeList<>, TypeList<>> {
public:
    static std::tuple<> readTypes(std::istream &is) {
        return std::make_tuple();
    };
};

#endif //TYPELIST_DOUBLEDECOMPRESSREADER_HPP
