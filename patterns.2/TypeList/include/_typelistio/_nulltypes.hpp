//
// Created by avk on 30.11.17.
//

#ifndef TYPELIST_NULLTYPES_HPP
#define TYPELIST_NULLTYPES_HPP

#include <istream>
#include <cassert>

class NullFunctor {
};

template <typename From, typename To>
class FTIF {
    To operator()(const From&) const {
        assert(false);
        return To();
    }
};

template <typename From, typename To>
class FTIT {
    To decompress(const From&) const {
        assert(false);
        return To();
    }
};

// Single argument id functor
template<typename ArgType>
class SAIF {
public:
    ArgType operator()(const ArgType &arg) const {
        assert(false);
        return arg;
    }
};

// Null type id decompress method
template<typename ResType>
class NTIDM {
public:
    ResType decompress() const {
        assert(false);
        return ResType();
    }
};

template <typename ResType>
std::istream& operator>>(std::istream&, NTIDM<ResType>) {
    assert(false);
}

class NullType {
};

#endif //TYPELIST_NULLTYPES_HPP
