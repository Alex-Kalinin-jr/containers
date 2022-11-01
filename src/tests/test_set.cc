#include <gtest/gtest.h>
#include "../s21_containers.h"
#include <cmath>
using namespace s21;

TEST(Constructors, Test_01) {
    set<int> a;
    set<int> b = {1, 2, 3, 4, 5};
    set<int> g{1, 2, 3, 4, 5};
    set<int> c(b);
    auto it1 = b.begin();
    auto it2 = c.begin();
    bool res = (*it1 == *it2);
    ASSERT_TRUE(res);
    it1++;
    it2++;
    res = (*it1 == *it2);
    ASSERT_TRUE(res);
    it1 = b.end();
    it2 = c.end();
    it1--;
    it2--;
    res = (*it1 == *it2);
    ASSERT_TRUE(res);

    set<int> d(std::move(b));
    auto it3 = d.begin();

    it2 = c.begin();
    ASSERT_TRUE(*it2 == *it3);
    it2++;
    it3++;
    ASSERT_TRUE(*it2 == *it3);
    it2 = c.end();
    it3 = d.end();
    it2--;
    it3--;
    ASSERT_TRUE(*it2 == *it3);
}

TEST(Capacity, Test_01) {
    set<int> a;
    bool res = a.empty();
    ASSERT_TRUE(res);
    a.insert(1);
    res = a.empty();
    ASSERT_FALSE(res);
    ASSERT_EQ(1, a.size());
    ASSERT_EQ((LLONG_MAX / sizeof(int)), a.max_size());
}

TEST(Modifiers, Test_01) {
    set<int> a = {1, 2, 3, 4, 5};
    a.erase(a.begin());
    ASSERT_EQ(*(a.begin()), 2);
    auto it = a.end();
    it--;
    ASSERT_EQ(*it, 5);
    a.erase(it);
    it = a.end();
    it--;
    ASSERT_EQ(*it, 4);
}

TEST(Modifiers, Test_02) {
    set<int> a = {1, 2, 3, 4, 5};
    set<int> b = {5, 4, 30, 3, 2, 1, 20};
    a.merge(b);
    auto it = a.end();
    it--;
    ASSERT_TRUE(*it = 30);
    auto itb = b.begin();
    itb++;
    itb++;
    ASSERT_TRUE(*itb == 3);
}

TEST(Lookup, Test_01) {
    set<int> a = {1, 2, 3, 8, 4, 5};
    auto it = a.find(3);
    it++;
    ASSERT_TRUE(*it == 4);

    bool res = a.contains(3);
    ASSERT_TRUE(res);
}


/*THESE TESTS ARE FOR CHECK OF INTERNAL BEHAVIOUR
FOR THEIR PERFOMING YOU SHOULD CHANGE THE STATUS OF SERVICE FUNCTIONS
ONTO PUBLIC*/

// TEST(balancing, Test_01) {
//     set<int> a = {11, 9, 5, 6, 7, 10, 4, 3, 8, 16, 15};
//     SetIterator<int> itr1 = a.begin();
//     SetIterator<int> itr2 = a.end();
//     a.set_balance_for_all();
//     while (itr1.get_node() != itr2.get_node()) {
//         if (itr1.get_node() != a.get_root()) {
//             ASSERT_LT(abs(itr1.get_node()->balance), 2);
//         }
//         ++itr1;
//     }
// }

// TEST(balancing, Test_02) {
//     set<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
//     SetIterator<int> itr1 = a.begin();
//     SetIterator<int> itr2 = a.end();
//     a.set_balance_for_all();
//     while (itr1.get_node() != itr2.get_node()) {
//         if (itr1.get_node() != a.get_root()) {
//             ASSERT_LT(abs(itr1.get_node()->balance), 2);
//         }
//         ++itr1;
//     }
// }

// TEST(balancing, Test_03) {
//     set<int> a = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
//     SetIterator<int> itr1 = a.begin();
//     SetIterator<int> itr2 = a.end();
//     a.set_balance_for_all();
//     while (itr1.get_node() != itr2.get_node()) {
//         if (itr1.get_node() != a.get_root()) {
//             ASSERT_LT(abs(itr1.get_node()->balance), 2);
//         }
//         ++itr1;
//     }
// }