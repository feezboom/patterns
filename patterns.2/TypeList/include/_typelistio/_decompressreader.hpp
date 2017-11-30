//
// Created by avk on 30.11.17.
//

#ifndef TYPELIST__DECOMPRESSREADER_HPP
#define TYPELIST__DECOMPRESSREADER_HPP


#include <typelist.h>
#include <genericfunctor.h>
#include <tuple>

#include <_typelistio/_nulltypes.hpp>
#include <_typelistio/_readerutils.hpp>
#include <cassert>

// DecompressReader
template<typename ResTL, typename GivenTL, typename FuncTL>
class DecompressReader {
    static_assert(SameLength<ResTL, GivenTL, FuncTL>::value);
};

template<typename ResHead, typename ...ResArgs,
        typename ReadHead, typename ...ReadArgs,
        typename FHead, typename ...FArgs>
class DecompressReader
        <
                TypeList<ResHead, ResArgs...>,
                TypeList<ReadHead, ReadArgs...>,
                TypeList<FHead, FArgs...>
        > {
public:

    // Useful substitutions.

    // DecompressReader for one template argument
    template<typename T1, typename T2, typename T3>
    using OneArgReader = DecompressReader<TypeList<T1>, TypeList<T2>, TypeList<T3>>;

    // Arguments tails typeLists
    using ResTail = TypeList<ResArgs...>;
    using ReadTail = TypeList<ReadArgs...>;
    using FTail = TypeList<FArgs...>;

    // DecompressReader parametrized by head & tail
    using HeadReader = OneArgReader<ResHead, ReadHead, FHead>;
    using TailReader = DecompressReader<ResTail, ReadTail, FTail>;
    using IdFunctor = GenericFunctor<ResHead, TypeList<ResHead>>;
    // The FHead type we expect according to ResHead and ReadHead.
    using ExpectedHeadFunctor = GenericFunctor<ResHead, TypeList<ReadHead>>;


    // Needed constants to check correctness of given template parameters

    // ResHead is NullType
    constexpr static bool headResIsNullType = std::is_same<ResHead, NullType>::value;
    // ReadHead is NullType
    constexpr static bool readHeadIsNull = std::is_same<ReadHead, NullType>::value;
    // Derived from GenericFunctor
    constexpr static bool fHeadDerivedFromGeneric = std::is_base_of<ExpectedHeadFunctor, FHead>::value;
    // FHead is SingleArgNullFunc
    constexpr static bool fHeadIsNull = std::is_same<FHead, SingleArgNullFunc>::value;
    // Check that Functor takes ResHead type and transforms it into ResHead type
    constexpr static bool fHeadIsId = std::is_base_of<IdFunctor, FHead>::value;


    // Implication for 2 booleans.
    template<bool x, bool y>
    struct Implication {
        constexpr static bool value = !x || y;
    };

    // Needed checks for given template parameters correctness.

    // fHead correctness
    constexpr static bool c0 = fHeadDerivedFromGeneric || fHeadIsNull;
    static_assert(c0, "c0 fails");
    constexpr static bool c1 = Implication<(!fHeadIsNull) && (readHeadIsNull), fHeadIsId>::value;
    static_assert(c1, "c1 fails");
    // One of readHead & fHead must be Null
    constexpr static bool c2 = readHeadIsNull ^fHeadIsNull;
    static_assert(c2, "c2 fails");
    // Resulting type is not null
    constexpr static bool c3 = !headResIsNullType;
    static_assert(c3, "c3 fails");

    constexpr static bool allCorrect = c0 && c1 && c2 && c3 && TailReader::allCorrect;
    static_assert(allCorrect, "template checks failed");

public:
    static std::tuple<ResHead, ResArgs...> readTypes(std::istream &is, FHead fHead, FArgs ... funcs) {
        if (readHeadIsNull) {
            // NullType in the second list.
            // Decompress by fHead
            assert(!fHeadIsNull);

            // read as it is and decompress by fHead
            ResHead resObj;
            is >> resObj;

            using ToApply = std::conditional<fHeadIsNull, NullType, FHead>::type;

            // put it in the resulting tuple
            std::tuple < ResHead > head = std::make_tuple((resObj));
            std::tuple<ResArgs...> tail = TailReader::readTypes(is, funcs...);

            return std::tuple_cat(head, tail);
        } else {
            // Not NullType in the second list
            // Then use .decompress from that type
            assert(!readHeadIsNull);

            ReadHead readObj;
            is >> readObj;

            // decompress it by method
            ResHead resHead = readObj.decompress();

            // put it in the resulting tuple
            std::tuple < ResHead > head = std::make_tuple(resHead);
            std::tuple<ResArgs...> tail = TailReader::readTypes(is, funcs...);

            return std::tuple_cat(head, tail);
        }
    };

};

template<>
class DecompressReader<TypeList<>, TypeList<>, TypeList<>> {
public:
    constexpr static bool allCorrect = true;

    static std::tuple<> readTypes(std::istream &is) {
        return std::make_tuple<>();
    }

};


#endif //TYPELIST__DECOMPRESSREADER_HPP
