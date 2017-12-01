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
    // FHead is NullFunctor
    constexpr static bool fHeadIsNull = std::is_same<FHead, /*SAIF<ResHead>*/NullFunctor>::value;
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
    // fHeadCorrectness (1)
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

    // todo : may be pass as argument std::tuple<FHead, FArgs...>?
    static std::tuple<ResHead, ResArgs...> readTypes(std::istream &is, FHead fHead, FArgs ... funcs) {
        // Final result
        ResHead r;

        if (!readHeadIsNull) {

            // Typed read results
            // Trick for compiler.
            // Substituting user NullType with NTIDM<ResHead> instead just for compiler
            // cause it has method ->decompress() implemented.
            // In fact it will be never called.
            using NullT = NTIDM<ResHead>;
            using ToApplyTD = typename std::conditional<readHeadIsNull, NullT, ReadHead>::type;

            // Create needed. In fact NTIDM will be never created. It is just for compiler.
            ToApplyTD *rdh = new ToApplyTD();

            // Read, call decompress and then delete it.
            is >> *rdh;
            r = rdh->decompress();

            delete rdh;

        } else {

            // Trick just for compiler.
            // Substituting NullFunctor with SAIF<ResHead> cause it
            // has operator()(...) implemented.
            // In fact it will never be used.
            using NullF = SAIF<ResHead>;
            using Functor = GenericFunctor<ResHead, TypeList<ResHead>>;
            using ToApplyF = typename std::conditional<readHeadIsNull, Functor, NullF>::type;
            using FheadFictive = typename std::conditional<readHeadIsNull, FHead, NullF>::type;

            // Replace NullFunc with SAIF<ResHead>
            // And creating generic functor - what compiler wants to see
            FheadFictive *_fHead = reinterpret_cast<FheadFictive *>(&fHead);
            Functor _f(*_fHead);

            ResHead rsh;
            is >> rsh;
            r = _f(rsh);
        }

        std::tuple < ResHead > head = std::make_tuple(r);
        std::tuple<ResArgs...> tail = TailReader::readTypes(is, funcs...);

        return std::tuple_cat(head, tail);
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
