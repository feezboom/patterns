//
// Created by avk on 30.11.17.
//

#ifndef TYPELIST_NULLTYPES_HPP
#define TYPELIST_NULLTYPES_HPP

template<typename R, typename T>
class SingleArgNullFunc {
public:

    R operator()(T &arg) {
        assert(false);
        return R();
    }
};

class NullType {
};

#endif //TYPELIST_NULLTYPES_HPP
