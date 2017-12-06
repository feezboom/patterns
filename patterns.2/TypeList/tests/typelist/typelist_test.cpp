//
// Created by avk on 15.11.17.
//

#include <gtest/gtest.h>

#include <typelist.h>

using list0 = TypeList<>;
using list1 = TypeList<int>;
using list2 = TypeList<int, double>;
using list3 = TypeList<int, double, float>;
using list4 = TypeList<int, double, float, char>;
using list5 = TypeList<int, double, float, char, std::string>;


TEST(TypeList, Main) {
    ASSERT_EQ(typeid(TypeAt<0, list4>::Result).name(), typeid(int).name());
}

TEST(TypeList, Length) {
    ASSERT_TRUE(TLLength<list0>::value == 0);
    ASSERT_TRUE(TLLength<list1>::value == 1);
    ASSERT_TRUE(TLLength<list2>::value == 2);
    ASSERT_TRUE(TLLength<list3>::value == 3);
    ASSERT_TRUE(TLLength<list4>::value == 4);
    ASSERT_TRUE(TLLength<list5>::value == 5);

    ASSERT_TRUE(Length<list0>::value == 0);
    ASSERT_TRUE(Length<list1>::value == 1);
    ASSERT_TRUE(Length<list2>::value == 2);
    ASSERT_TRUE(Length<list3>::value == 3);
    ASSERT_TRUE(Length<list4>::value == 4);
    ASSERT_TRUE(Length<list5>::value == 5);
}

TEST(TypeList, IsEmpty) {
    ASSERT_FALSE(!IsEmpty<list0>::value);
    ASSERT_FALSE(IsEmpty<list1>::value);
    ASSERT_FALSE(IsEmpty<list2>::value);
    ASSERT_FALSE(IsEmpty<list3>::value);
    ASSERT_FALSE(IsEmpty<list4>::value);
    ASSERT_FALSE(IsEmpty<list5>::value);
}

TEST(TypeList, Contains) {
    ASSERT_FALSE((Contains<int, list0>::value));
    ASSERT_FALSE(!(Contains<int, list1>::value));
    ASSERT_FALSE(!(Contains<int, list2>::value));
    ASSERT_FALSE(!(Contains<int, list3>::value));
    ASSERT_FALSE(!(Contains<int, list4>::value));
    ASSERT_FALSE(!(Contains<int, list5>::value));

    ASSERT_FALSE((Contains<bool, list0>::value));
    ASSERT_FALSE((Contains<bool, list1>::value));
    ASSERT_FALSE((Contains<bool, list2>::value));
    ASSERT_FALSE((Contains<bool, list3>::value));
    ASSERT_FALSE((Contains<bool, list4>::value));
    ASSERT_FALSE((Contains<bool, list5>::value));

    ASSERT_FALSE(!(Contains<int, list5>::value));
    ASSERT_FALSE(!(Contains<double, list5>::value));
    ASSERT_FALSE(!(Contains<float, list5>::value));
    ASSERT_FALSE(!(Contains<char, list5>::value));
    ASSERT_FALSE(!(Contains<std::string, list5>::value));
}

TEST(TypeList, Equal) {
    ASSERT_FALSE(!(Equal<list0, list0>::value));
    ASSERT_FALSE(!(Equal<list1, list1>::value));
    ASSERT_FALSE(!(Equal<list2, list2>::value));
    ASSERT_FALSE(!(Equal<list3, list3>::value));
    ASSERT_FALSE(!(Equal<list4, list4>::value));
    ASSERT_FALSE(!(Equal<list5, list5>::value));

    ASSERT_FALSE((Equal<list1, list2>::value));
    ASSERT_FALSE((Equal<list2, list3>::value));
    ASSERT_FALSE((Equal<list3, list4>::value));
    ASSERT_FALSE((Equal<list4, list5>::value));
    ASSERT_FALSE((Equal<list5, list0>::value));
    ASSERT_FALSE((Equal<list0, list2>::value));
    ASSERT_FALSE((Equal<list1, list3>::value));
}