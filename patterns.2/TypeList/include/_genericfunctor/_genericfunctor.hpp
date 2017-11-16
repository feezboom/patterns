//
// Created by avk on 16.11.17.
//

#ifndef TYPELIST_GENERICFUNCTOR_HPP
#define TYPELIST_GENERICFUNCTOR_HPP


#include <typelist.h>

template<typename FunctorType, typename ReturnType, typename TL>
struct _GenericFunctor {
};


template<typename FunctorType, typename ReturnType, typename ...FunctorArgs>
struct _GenericFunctor<FunctorType, ReturnType, TypeList<FunctorArgs...>> {

    explicit _GenericFunctor(FunctorType functor, FunctorArgs... args) : _functor(functor), _arguments(args) {}

    ReturnType apply(FunctorArgs args) {
        return _functor();
    }

    FunctorType _functor;
    FunctorArgs... _arguments{};

};


#endif //TYPELIST_GENERICFUNCTOR_HPP
