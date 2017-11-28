//
// Created by avk on 16.11.17.
//

#ifndef TYPELIST_GENERICFUNCTOR_HPP
#define TYPELIST_GENERICFUNCTOR_HPP

#include <memory>
#include <typelist.h>

template<typename R, typename TL>
class GenericFunctor;


template<typename _Result, typename... _ArgTypes>
class GenericFunctor<_Result, TypeList<_ArgTypes...>> {
public:

    // Main constructor from any callable
    template<typename Callable>
    explicit GenericFunctor(const Callable &callable) : _invoker(callable) {}

    _Result operator()(_ArgTypes... args) {
        return _invoker(args...);
    };

private:
    using _InvokerType = _Result (*)(_ArgTypes ...);
    _InvokerType _invoker;
};


//template<typename R, typename Callable>
//class Functor_ {
//public:
//
//    // Main constructor from any callable
//    explicit Functor_(const Callable &callable) : _invoker(callable) {}
//
//    template <typename ..._ArgTypes>
//    R operator()(_ArgTypes... args) {
//        return _invoker(args...);
//    };
//
//private:
//    Callable _invoker;
//};



//template <typename Result, typename TL>
//class _ICallableHandler;
//
//template <typename Result, typename ...Args>
//class _ICallableHandler<Result, TypeList<Args...>> {
//public:
//    virtual Result operator()(Args... args) = 0;
//    virtual _ICallableHandler* clone() const = 0;
//    virtual ~_ICallableHandler() = default;
//};
//
//template <typename ParentFunctor, typename Callable>
//class _CallableHandler :
//        public _ICallableHandler
//        <
//                typename ParentFunctor::ResultType,
//                typename ParentFunctor::ArgsTL
//        >
//{
//public:
//    using ResultType = typename ParentFunctor::ResultType;
//    using ArgsTL = typename ParentFunctor::ArgsTL;
//
//    explicit _CallableHandler(const Callable& callable) : _callable(callable) {};
//
//    _CallableHandler* clone() const {
//        return new _CallableHandler(*this);
//    };
//
//    template <typename ...Args>
//    ResultType operator()(Args... args) {
//        _callable(args...);
//    }
//
//private:
//    Callable _callable;
//};
//
//
//template<typename ReturnType, typename TL>
//class GenericFunctor {
//private:
//    using Impl = _ICallableHandler<ReturnType, TL>;
//public:
//    using ResultType = ReturnType;
//    using ArgsTL = TL;
//
//    // Main constructor from any callable
//    template <typename Callable>
//    explicit GenericFunctor(const Callable& callable) :
//            _invoker(new _CallableHandler<GenericFunctor, Callable>(callable)) {
////        auto* ptr = new _CallableHandler<GenericFunctor, Callable>(callable);
////        _invoker = ptr;
//    }
//
////    GenericFunctor() = default;
////
////    GenericFunctor(const GenericFunctor& otherFunctor) {
////        // todo
////    };
////
////    GenericFunctor& operator=(const GenericFunctor& otherFunctor) {
////        // todo
////    };
////
////    explicit GenericFunctor(std::shared_ptr<Impl> otherFunctor) : _invoker(otherFunctor) {};
//
//
////    ReturnType operator()(CallableArgs... args) {
////        return _invoker->operator()(args...);
////    };
//
//private:
//    std::shared_ptr<Impl> _invoker;
//};
////
////template<typename ReturnType, typename ...CallableArgs>
////class GenericFunctor<ReturnType, TypeList<CallableArgs...>> {
////
////};

#endif //TYPELIST_GENERICFUNCTOR_HPP
