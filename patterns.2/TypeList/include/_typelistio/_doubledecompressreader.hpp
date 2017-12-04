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


        // FHead cases:
        // 1) FHead can be NullFunctor
        using TypeDecompressionResult =
        typename std::conditional<!readHeadIsNull, decltype(readHead.decompress()), NullType>::type;
        using FHeadForNullCase = FTIF<TypeDecompressionResult, ResHead>;

        // actual type of r0, which will appear
        using TName = typename std::conditional<!readHeadIsNull, TypeDecompressionResult, ResHead>::type;
        TName r0;

        if (!readHeadIsNull) {
            // that means that readHead.decompress returns TypeDecompressionResult.
            // actually r0 has such type. But compiler needs cast for other cases.

            // Fictive cast
            TName* fictive = reinterpret_cast<TName*>(&r0);
            is >> readHead;
            *fictive = readHead.decompress();
        } else {
            // that means that we don't have decompressable type
            is >> res;
        }

        if (!fHeadIsNull) {
//            if (!readHeadIsNull) {
//                // that means that f takes TypeDecompression result
//                // actually r0 has such type. But compiler needs cast for other cases.
//                TName* fictive = reinterpret_cast<TName*>(&r0);
//                res = f(*fictive);
//            } else {
//                // that means than f takes ResHead and gives ResHead
//                // actually r0 has ResHead type but compiler needs ca
//                TName* fictive = reinterpret_cast<TName*>(&r0);
//                res = f(*fictive);
//            }
            TName* fictive = reinterpret_cast<TName*>(&r0);
            res = f(*fictive);
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
