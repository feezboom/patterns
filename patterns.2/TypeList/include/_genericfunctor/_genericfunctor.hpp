//
// Created by avk on 16.11.17.
//

#ifndef TYPELIST_GENERICFUNCTOR_HPP
#define TYPELIST_GENERICFUNCTOR_HPP

#include <memory>
#include <typelist.h>

template<typename Result, typename TL>
class _ICallableHandler;

template<typename Result, typename ...Args>
class _ICallableHandler<Result, TypeList<Args...>> {
public:
    virtual Result operator()(Args... args) = 0;

    virtual ~_ICallableHandler() = default;
};

template<typename Callable, typename R, typename ...Args>
class _CallableHandler : public _ICallableHandler<R, TypeList<Args...>> {
public:
    explicit _CallableHandler(const Callable &callable) : _callable(callable) {};

    R operator()(Args... args) {
        return _callable(args...);
    }

private:
    Callable _callable;
};


template<typename R, typename TL>
class GenericFunctor;

template<typename _Result, typename... _ArgTypes>
class GenericFunctor<_Result, TypeList<_ArgTypes...>> {
    using ArgsTL = TypeList<_ArgTypes...>;
    using _IInvokerType = _ICallableHandler<_Result, ArgsTL>;
public:

    // Main constructor from any callable
    template<typename Callable>
    explicit GenericFunctor(const Callable &callable) :
            _invoker(new _CallableHandler<Callable, _Result, _ArgTypes...>(callable)) {}

    _Result operator()(_ArgTypes... args) {
        return _invoker->operator()(args...);
    };

private:
    std::shared_ptr<_IInvokerType> _invoker;
};



#endif //TYPELIST_GENERICFUNCTOR_HPP
