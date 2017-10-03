#include <iostream>
#include <typeinfo>
#include <ObjectList.hpp>

int main() {

    typelist::TypeList<> l0;

    objectlist::ObjectList<> ol;

    int a = 5;
    double b = 6.6;
    long c = 1;
    long long d = 2;


    auto list = objectlist::push_back(ol, &a);
    auto list1 = objectlist::push_back(ol, &b);
    auto list2 = objectlist::push_back(ol, &c);
    auto list3 = objectlist::push_back(ol, &d);

    std::cout << list3.size() << std::endl;

    auto list4 = objectlist::pop_front(list3);

    auto x = objectlist::at<1>(list4);

    std::cout << typeid(decltype(x)).name() << std::endl;

    std::cout << list4.size() << std::endl;
    std::cout << std::endl;
    return 0;
}