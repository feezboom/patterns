//
// Created by avk on 14.11.17.
//

#ifndef READER_READER_H
#define READER_READER_H

#include <typelist.h>

#include <fstream>
#include <cassert>
#include <memory>

#include <typelist.h>

#include "_allocsize.hpp"


template<typename TypeList_Type>
class DumbReader {
public:
    static void *nextLine(std::istream &is) {
        void *ptr = malloc(alloc_size);
        _DumbReaderInternal<TypeList_Type, 0>::readObjects(is, ptr);
        return ptr;
    }

    static void deleteLine(void *ptr) {

    }

private:
    constexpr static std::size_t alloc_size = AllocSize<TypeList_Type>::value;

private:
    template<typename TL_, std::size_t shift>
    struct DestructorCaller {
        static void destructObjects(void *ptr) {
            assert(false);
        }
    };

    template<typename Head, typename ...Args, std::size_t shift>
    struct DestructorCaller<TypeList<Head, Args...>, shift> {
        static void destructObjects(void *ptr) {
            DestructorCaller<TypeList<Head>, shift>::destructObjects(ptr);
            DestructorCaller<TypeList<Args...>, shift>::destructObjects(ptr);
        }
    };

    template<typename Head, typename std::size_t shift>
    struct DestructorCaller<TypeList<Head>, shift> {
        static void destructObjects(void *ptr) {
            Head *objPtr = static_cast<Head *>(ptr + shift);
            objPtr->~Head();
        }
    };

    template<typename TL, std::size_t shift>
    struct _DumbReaderInternal {
        static void readObjects(std::istream &is, void *ptr) {
            assert(false);
        };
    };

    template<typename Head, typename ...Args, std::size_t shift>
    struct _DumbReaderInternal<TypeList<Head, Args...>, shift> {
        static void readObjects(std::istream &is, void *ptr) {
            auto shift_ = shift;
            _DumbReaderInternal<TypeList<Head>, shift>::readObjects(is, ptr);
            _DumbReaderInternal<TypeList<Args...>, shift + sizeof(Head)>::readObjects(is, ptr);
        }
    };

    template<typename Head, std::size_t shift>
    struct _DumbReaderInternal<TypeList<Head>, shift> {
        static void readObjects(std::istream &is, void *ptr) {
            Head *objPtr = static_cast<Head *>(ptr + shift);
            new(objPtr) Head();
            is >> *objPtr;

        }
    };
};

#endif //READER_READER_H
