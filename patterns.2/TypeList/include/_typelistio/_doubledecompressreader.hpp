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
        typename ReadHead, typename ...ReadArgs,
        typename FHead, typename ...FArgs>
class DoubleDecompressReader
        <
                TypeList<ResHead, ResArgs...>,
                TypeList<ReadHead, ReadArgs...>,
                TypeList<FHead, FArgs...>
        > {
    // ReadHead is NullType
    constexpr static bool readHeadIsNull = std::is_same<ReadHead, NullType>::value;
    constexpr static bool fHeadIsNull = std::is_same<FHead, NullFunctor>::value;

// Reader for one template argument
    template<typename T1, typename T2, typename T3>
    using OneArgReader = DoubleDecompressReader<TypeList<T1>, TypeList<T2>, TypeList<T3>>;

// Reader parametrized by head & tail
    using DDHeadReader = OneArgReader<ResHead, ReadHead, FHead>;
    using DDTailReader = DoubleDecompressReader<
            TypeList<ResArgs...>,
            TypeList<ReadArgs...>,
            TypeList<FArgs...>>;
//    using NullFunc = NullFunctor<ResHead, ReadHead>;

public:
    static std::tuple<ResHead, ResArgs...> readTypes(std::istream &is, FHead fHead, FArgs... fArgs) {

        std::tuple <ResHead> head = DDHeadReader::_readFirstType(is, fHead);
        std::tuple<ResArgs...> tail = DDTailReader::readTypes(is, fArgs...);

        return std::tuple_cat(head, tail);
    };

    static std::tuple<ResHead> _readFirstType(std::istream &is, FHead f) {


        ResHead res;
        ReadHead readHead;

        // the same as in the decompressReader, just compiler trick.
        // ReadHead cases:
        // 1) ReadHead can be null
        using ReadHeadForNullCase = FTIT<ResHead, ResHead>;
        // 2) ReadHead can be decompressable Type
        // nothing special

        // FHead cases:
        // 1) FHead can be NullFunctor
        using TypeDecompressionResult = decltype(readHead.decompress());
        using FHeadForNullCase = FTIF<TypeDecompressionResult, ResHead>;



        TypeDecompressionResult r0;

        if (!readHeadIsNull) {
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
