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

class ReaderUtils {
public:

    template<typename R>
    static R readType(std::istream &is) {
        R res;
        is >> res;
        return res;
    }
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
    // Arguments tails typeLists
    using ResTail = TypeList<ResArgs...>;
    using ToReadTail = TypeList<ToReadArgs...>;
    using FuncTail = TypeList<FuncArgs...>;

    // Reader for one template argument
    template<typename T1, typename T2, typename T3>
    using OneArgReader = Reader<TypeList<T1>, TypeList<T2>, TypeList<T3>>;

    // Reader parametrized by head & tail
    using HeadReader = OneArgReader<ResHead, ToReadHead, FuncHead>;
    using TailReader = Reader<ResTail, ToReadTail, FuncTail>;

    // The FuncHead type we expect according to ResHead and ToReadHead.
    using ExpectedHeadFunctor = GenericFunctor<ResHead, TypeList<ToReadHead>>;

    // Derived from GenericFunctor
    constexpr static bool derivedFromGeneric = std::is_base_of<ExpectedHeadFunctor, FuncHead>::value;
    // ToReadHead is NullType
    constexpr static bool toReadIsNull = std::is_same<ToReadHead, NullType>::value;
    // FuncHead is NullFunc
    constexpr static bool funcIsNull = std::is_same<FuncHead, NullFunc>::value;

    // Implication for 2 booleans.
    template<bool x, bool y>
    struct Implication {
        constexpr static bool value = !x || y;
    };

    // Check that Functor takes ResHead type and transforms it into ResHead type
    using IdFunctor = GenericFunctor<ResHead, TypeList<ResHead>>;
    constexpr static bool functorIsId = std::is_same<FuncHead, IdFunctor>::value ||
                                        std::is_base_of<IdFunctor, FuncHead>::value;

    // (Check if ToRead type is Null Type && FuncHead is not NullFunc)
    // means that
    // (FuncHead is GenericFunctor transforming from ResHead to ResHead)
    constexpr static bool ifToReadIsNullThen = Implication<(!funcIsNull) && (toReadIsNull), functorIsId>::value;

    // Total FuncHead correctness.
    // Check during execution appropriate methods.
    constexpr static bool headFunctorCorrect = (derivedFromGeneric || funcIsNull) && ifToReadIsNullThen;


    // Check if ResType is Null
    constexpr static bool headResIsNotNullType = !std::is_same<ResHead, NullType>::value;
    static_assert(headResIsNotNullType, "resulting type can not be NullType");

    // Check that everything is correct
    constexpr static bool headCorrect = headFunctorCorrect && headResIsNotNullType;
    constexpr static bool everythingCorrect = headCorrect && TailReader::everythingCorrect;

public:

    static std::tuple<ToReadHead, ToReadArgs...> readTypes(std::istream &is) {
        assert(headFunctorCorrect && "wrong template functor given");

        std::tuple < ToReadHead > head = std::make_tuple(ReaderUtils::readType<ToReadHead>(is));
        std::tuple<ToReadArgs...> tailTuple = TailReader::readTypes(is);
        return std::tuple_cat(head, tailTuple);
    }

    static std::tuple<ResHead, ResArgs...> readDecompressTypes(std::istream &is) {
        assert(headFunctorCorrect && "wrong template functor given");

        FuncHead decompressor = FuncHead();

        if (std::is_same<ToReadHead, NullType>::value) {
            // NullType in the second list.
            // Using just resulting type

            ResHead resObj;
            is >> resObj;

            std::tuple < ResHead > head = std::make_tuple(decompressor(resObj));
            std::tuple<ResArgs...> tail = TailReader::readDecompressTypes(is);

            return std::tuple_cat(head, tail);
        } else {
            // Not NullType in the second list

            ToReadHead readObj;
            is >> readObj;

            std::tuple < ResHead > head = std::make_tuple(decompressor(readObj));
            std::tuple<ResArgs...> tail = TailReader::readDecompressTypes(is);

            return std::tuple_cat(head, tail);
        }


    }




};

template<>
class Reader<TypeList<>, TypeList<>, TypeList<>> {
public:
    constexpr static bool everythingCorrect = true;

    static std::tuple<> readTypes(std::istream &is) {
        return std::make_tuple<>();
    }

    static std::tuple<> readDecompressTypes(std::istream &is) {
        return std::make_tuple<>();
    }

};


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
        >
        : public Reader
                <
                        TypeList<ResHead, ResArgs...>,
                        TypeList<ToReadHead, ToReadArgs...>,
                        TypeList<FuncHead, FuncArgs...>
                > {
    // Reader for one template argument
    template<typename T1, typename T2, typename T3>
    using OneArgReader = Reader<TypeList<T1>, TypeList<T2>, TypeList<T3>>;

    using BaseReader = Reader<
            TypeList<ResHead, ResArgs...>,
            TypeList<ToReadHead, ToReadArgs...>,
            TypeList<FuncHead, FuncArgs...>>;

    // Reader parametrized by head & tail
    using DDHeadReader = OneArgReader<ResHead, ToReadHead, FuncHead>;
    using DDTailReader = DoubleDecompressReader<
            typename BaseReader::ResTail,
            typename BaseReader::ToReadTail,
            typename BaseReader::FuncTail>;

public:

    static std::tuple<ResHead> readTypeFirst(std::istream &is) {
        bool doTypeDecompression = std::is_same<ToReadHead, NullType>::value;
        bool doFunctorDecompression = std::is_same<FuncHead, NullFunc>::value;

        ResHead res;
        ToReadHead readHead;
        FuncHead f;

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


    static std::tuple<ResHead, ResArgs...> readTypes(std::istream &is) {

        std::tuple < ResHead > head = DDHeadReader::readTypeFirst(is);
        std::tuple<ResArgs...> tail = DDTailReader::readTypes(is);

        return std::tuple_cat(head, tail);
    };

};

template<>
class DoubleDecompressReader<TypeList<>, TypeList<>, TypeList<>> {
public:
    static std::tuple<> readTypes(std::istream &is) {
        return std::make_tuple();
    };

};

#endif //TYPELIST__READER_HPP
