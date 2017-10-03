//
// Created by avk on 26.09.17.
//

#ifndef TYPELIST_OBJECTLIST_H
#define TYPELIST_OBJECTLIST_H

#include <vector>
#include "typelist.hpp"



namespace objectlist {

    template <typename ... Args>
    class ObjectList {
    public:
        inline ObjectList() {};
        inline ObjectList(const ObjectList<Args ...>&) = delete;

        inline ObjectList(ObjectList<Args ...> &&t): _data(t._data) { }
        inline ObjectList(std::vector<void*>&& data): _data(data) { }

        size_t size() const;


    private:
        typedef typelist::TypeList<Args...> _types;

        template <typename T, typename ... Args_>
        friend ObjectList<Args_..., T> push_back(ObjectList<Args_...>& ol, T* obj);

        template <typename T, typename ... Args_>
        friend ObjectList<Args_...> pop_front(ObjectList<T, Args_...>& ol);

        template <typename T, typename ... Args_>
        friend T* front(ObjectList<T, Args_...>& ol);

        template <std::size_t N, typename ... Args_>
        friend typename typelist::At<N, Args_...>::valueType* at(const ObjectList<Args_...>& ol);

        std::vector<void *> _data;
    };


    template <std::size_t N, typename ... Args>
    typename typelist::At<N, Args...>::valueType* at(const ObjectList<Args...>& ol) {
        return static_cast<typename typelist::At<N, Args...>::valueType*>(ol._data[N]);
    };

    template<typename T, typename ... Args>
    ObjectList<Args ..., T> push_back(ObjectList<Args ...>& ol, T *obj) {
        ol._data.push_back(obj);
        return ObjectList<Args ..., T>(std::move(ol._data));
    }

    template <typename T, typename ... Args>
    ObjectList<Args ...> pop_front(ObjectList<T, Args...>& ol) {
        ol._data.erase(ol._data.begin());
        return ObjectList<Args ...>(std::move(ol._data));
    }

    template <typename T, typename ... Args>
    T* front(ObjectList<T, Args...>& ol) {
        return ol._data[0];
    }

    template <typename ... Args>
    size_t objectlist::ObjectList<Args...>::size() const {
        return typelist::ArgsLen<Args...>::value;
    };

//    template <std::size_t N, typename ... Args>
//    typename typelist::At<N, Args...>::valueType* ObjectList<Args...>::at() const {
//        return static_cast<typename typelist::At<N, Args...>::valueType*>(_data[N]);
//    }



}

#endif //TYPELIST_OBJECTLIST_H
