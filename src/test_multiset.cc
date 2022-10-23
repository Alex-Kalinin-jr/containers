#include <gtest/gtest.h>

#include "s21_set.h"

// TEST(multiset, init_1) {
//     s21::s21_Multiset<int> a;
//     s21::s21_Multiset<int> a1(a);
//     s21::s21_Multiset<int> b1{1, 2, 3, 4, 5};
//     s21::set<int> b2{1, 2, 3, 4, 5};
//     s21::s21_Multiset<int> e = a;
//     s21::s21_Multiset<int> c = s21::s21_Multiset<int>();
// }

TEST(multiset, begin_end) {
    s21::s21_Multiset<int> b1{1, 1, 3, 4, 5};
    s21::SetIterator<int> itr1 = b1.begin();
    ASSERT_EQ(*itr1, 1);
    itr1++;
    ASSERT_EQ(*itr1, 1);
    itr1++;
    ASSERT_EQ(*itr1, 3);
    itr1++;
    ASSERT_EQ(*itr1, 4);
    itr1++;
    ASSERT_EQ(*itr1, 5);
}