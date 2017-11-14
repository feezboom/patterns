#include <iostream>
#include "include/typelist.h"

int main() {

    using myTypeList = TypeList<int, double, float, char>;
    std::cout << typeid(TypeAt<0, myTypeList>::Result).name() << std::endl;
    std::cout << Length<myTypeList>::Result;
    return 0;
}