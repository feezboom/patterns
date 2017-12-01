//
// Created by avk on 30.11.17.
//

#ifndef TYPELIST_NULLTYPES_HPP
#define TYPELIST_NULLTYPES_HPP

class NullFunctor {
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
    ResType &decompress() const {
        return ResType();
        assert(false);
    }
};

class NullType {
};

#endif //TYPELIST_NULLTYPES_HPP
