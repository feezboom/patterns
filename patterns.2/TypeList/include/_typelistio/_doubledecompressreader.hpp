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

    // todo: add static_assert() checks.

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

        // Compiler will always need decompress method from ReadHead.
        // Such type will always have decompress
        using NullT = NTIDM<ResHead>;
        using ReadHeadFixed = typename std::conditional<readHeadIsNull, NullT, ReadHead>::type;
        ReadHeadFixed readHeadFixed;

        // Decompression result will be ResHead if NullType was passed due to ReadHeadFixed
        using DecompressionResultType = decltype(readHeadFixed.decompress());
        DecompressionResultType r0;

        // Needs decompression
        if (readHeadIsNull) {
            // that means that we don't have decompressable type
            is >> (*reinterpret_cast<ResHead*>(&r0));
        } else {
            // If decompressor type is Null (actually during runtime this won't happen)
            // it was substituted with type having decompress method.
            // This is just for compiler

            is >> readHeadFixed;
            /* DecompressionResultType */ r0 = readHeadFixed.decompress();
        }


        // Needs to apply functor
        if (fHeadIsNull) {
            // Means that decompress gives ResHead (in case when FHead is NullFunctor)
            constexpr static bool x = std::is_same<decltype(readHeadFixed.decompress()), ResHead>::value;
            static_assert(readHeadIsNull || !fHeadIsNull || x);

            res = *reinterpret_cast<ResHead *>(&r0);
        } else {
            // If functor is Null (actually during runtime this won't happen).
            // This is just for compiler
            using NullF = SAIF<ResHead>;
            using FType = typename std::conditional<fHeadIsNull, NullF, FHead>::type;

            FType *fFictive = reinterpret_cast<FType *>(&f);
            res = (*fFictive)(r0);
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
