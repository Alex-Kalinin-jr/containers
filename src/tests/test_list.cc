#include <gtest/gtest.h>

#include "../s21_containers.h"
using namespace s21;

struct two_ints {
    int a;
    double b;
} two_ints;

TEST(list, init_1) {
    List<int> a;
    ASSERT_TRUE(a.empty());

    List<int> b(5, 4);
    ASSERT_EQ(b.size(), 5);
}

TEST(list, init_2) {
    List<int> b({5, 4});
    ASSERT_EQ(b.size(), 2);
}

TEST(list, init_3) {
    List<std::string> c({"afdfdf", "dfdh", "djfhd", "dkfjd", "dhfd"});
    ASSERT_EQ(c.size(), 5);

    List<double> e{5, 4, 3, 2, 1};
    ASSERT_EQ(e.size(), 5);
}

TEST(list, copy) {
    List<std::string> c({"afdfdf", "dfdh", "djfhd", "dkfjd", "dhfd"});
    ASSERT_EQ(c.size(), 5);

    List<std::string> e{c};
    ASSERT_EQ(e.size(), 5);

    List<struct two_ints> f{{5, 3}, {6, 4.0}, {-456, 2}};
    List<struct two_ints> g(f);

    ASSERT_EQ(f.size(), 3);
    ASSERT_EQ(g.size(), 3);
}

TEST(list, assignmnt) {
    List<double> e{5, 4, 3, 2, 1};
    List<double> f{5, 4, 3};
    e = f;

    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(f.size(), 3);
}

TEST(list, front_back) {
    List<double> e{5, 4, 3, 2, 1};
    ASSERT_EQ(e.front(), 5);
    ASSERT_EQ(e.back(), 1);
}

TEST(list, front_back_2) {
    List<char> e{5, 4, 3, 2, 1};
    List<char> f = e;
    ASSERT_EQ(f.front(), 5);
    ASSERT_EQ(f.back(), 1);
}

TEST(list, front_back_3) {
    List<char> g{5, 4, 3, 2, 1};
    List<char> h(g);
    ASSERT_EQ(h.front(), 5);
    ASSERT_EQ(h.back(), 1);
}

TEST(list, begin_end) {
    List<char> g{5, 4, 3, 2, 1};
    List<char> h(g);
    node_iterator<char> a1(h.begin());
    node_iterator<char> a2(g.begin());
    ASSERT_EQ(*a1, 5);
    ASSERT_EQ(*a2, 5);

    a1 = h.end();
    a1--;
    a2 = g.end();
    --a2;
    ASSERT_EQ(*a1, 1);
    ASSERT_EQ(*a2, 1);
}

TEST(list, insert_1) {
    List<char> g{5, 4, 3, 2, 1};
    node_iterator<char> a1;
    a1 = g.begin();
    ++a1;
    a1++;
    g.insert(a1, 35);
    g.insert(a1, 43);
    ASSERT_EQ(g.size(), 7);

    a1 = g.end();
    g.insert(a1, 24);
    g.insert(a1, 234);
    ASSERT_EQ(g.size(), 9);
}
TEST(list, insert_2) {
    List<char> g;
    node_iterator<char> a1;
    a1 = g.end();
    g.insert(a1, 35);
    g.insert(a1, 43);
    ASSERT_EQ(g.size(), 2);

    a1 = g.end();
    g.insert(a1, 24);
    g.insert(a1, 234);
    ASSERT_EQ(g.size(), 4);
}

TEST(list, erase_1) {
    List<char> g{5, 4, 3, 2, 1};
    node_iterator<char> a1 = g.begin();
    ASSERT_EQ(g.size(), 5);
    g.erase(a1);
    ASSERT_EQ(g.size(), 4);
    a1 = g.begin();
    g.erase(a1);
    ASSERT_EQ(g.size(), 3);

    a1 = g.end();
    g.erase(a1);
    a1 = g.end();
    --a1;
    g.erase(a1);
    ASSERT_EQ(g.size(), 2);
}

TEST(list, erase_2) {
    List<char> g;
    node_iterator<char> a1 = g.begin();
    g.erase(a1);
    a1 = g.begin();
    g.erase(a1);
    ASSERT_EQ(g.size(), 0);

    a1 = g.end();
    g.erase(a1);
    a1 = g.end();
    g.erase(a1);
    ASSERT_EQ(g.size(), 0);
}

TEST(list, back1) {
    List<char> g{5, 4, 3, 2, 1};
    g.pop_back();
    ASSERT_EQ(g.size(), 4);
}

TEST(list, back2) {
    List<char> g{5, 4, 3, 2, 1};
    List<char> g2(g);
    g.insert(g.end(), 3);
    g2.push_back(3);
    ASSERT_EQ(g.size(), 6);
    ASSERT_EQ(g.size(), g2.size());
}

TEST(list, front1) {
    List<char> g{5, 4, 3, 2, 1};
    List<char> g2(g);
    g.insert(g.begin(), 3);
    g2.push_front(3);
    ASSERT_EQ(g.size(), 6);
    ASSERT_EQ(g.size(), g2.size());
}

TEST(list, front2) {
    List<char> g{5, 4, 3, 2, 1};
    List<char> g2(g);
    node_iterator<char> itr(g.begin());
    ++itr;
    ++itr;

    g.erase(g.begin());
    g2.pop_front();
    ASSERT_EQ(g.size(), 4);
    ASSERT_EQ(g.size(), g2.size());
}

TEST(list, front3) {
    List<char> g{5, 4, 3, 2, 1};
    List<char> g2(g);
    g.erase(g.begin());
    g2.pop_front();
    ASSERT_EQ(g.size(), 4);
    ASSERT_EQ(g.size(), g2.size());
}

TEST(list, main_add_del_test) {
    std::string a1 = "{1, 1}";
    std::string a2 = "{2, 2}";
    std::string a3 = "{3, 3}";
    std::string a4 = "{4, 4}";
    std::string a5 = "{5, 5}";
    List<std::string> g;
    node_iterator<std::string> itr(g.begin());
    itr = g.insert(itr, a1);
    node_iterator<std::string> itr2(g.begin());
    g.push_front(a2);
    g.push_back(a3);
    --itr;
    ASSERT_EQ(*itr, a2);
    g.insert(itr2, a4);
    g.insert(itr2, a5);
    ASSERT_EQ(*itr, a2);
    ASSERT_EQ(g.back(), a3);
    ASSERT_EQ(g.front(), a2);
    itr = g.begin();
    itr++;
    itr++;
    itr++;
    itr++;
    ASSERT_EQ(*itr, a3);
}

TEST(list, swap) {
    List<char> a{5, 4, 3, 2, 1};
    char fl1 = a.front();
    List<char> b{1, 2, 3, 4, 5};
    char fl2 = b.front();
    a.swap(b);
    char fl22 = a.front();
    char fl11 = b.front();
    ASSERT_EQ(fl1, fl11);
    ASSERT_EQ(fl2, fl22);
}

TEST(list, splice) {
    List<char> a{5, 4, 3, 2, 1};
    List<char> b{1, 2, 3, 4, 5};
    node_iterator<char> itrA(a.begin());
    a.splice(itrA, b);
    ASSERT_EQ(a.size(), 10);
    ASSERT_EQ(*itrA, 5);
}

TEST(list, reverse) {
    List<char> a{5, 4, 3, 2, 1};
    List<char> b{};
    a.reverse();
    ASSERT_EQ(a.front(), 1);
    ASSERT_EQ(a.back(), 5);
}

TEST(list, reverse_splice) {
    List<char> a{5, 4, 3, 2, 51};
    List<char> b{1, 2, 3, 4, 5};
    node_iterator<char> itrA(a.begin());
    a.splice(itrA, b);
    a.reverse();
    ASSERT_EQ(a.front(), 51);
    ASSERT_EQ(a.back(), 1);
}

TEST(list, unique) {
    List<char> a{5, 4, 4, 4, 3, 2, 51};
    a.unique();
    ASSERT_EQ(a.size(), 5);
    ASSERT_EQ(a.front(), 5);
    ASSERT_EQ(a.back(), 51);
}

TEST(list, merge) {
    List<char> a{1, 2, 3, 4};
    List<char> b{1, 3, 6};
    a.merge(b);
    ASSERT_EQ(a.size(), 7);
    node_iterator<char> itrA(a.end());
    itrA--;
    ASSERT_EQ(*itrA, 6);
    --itrA;
    --itrA;
    --itrA;
    --itrA;
    ASSERT_EQ(*itrA, 2);
}

TEST(list, merge2) {
    List<char> a;
    List<char> b{1, 3, 6};
    a.merge(b);
    ASSERT_EQ(a.size(), 3);
    node_iterator<char> itrA(a.end());
    itrA--;
    ASSERT_EQ(*itrA, 6);
    itrA = a.begin();
    ASSERT_EQ(*itrA, 1);
}

TEST(list, merge3) {
    List<char> b;
    List<char> a{1, 3, 6};
    List<char> c{0, 2, 8};
    a.merge(b);
    ASSERT_EQ(a.size(), 3);
    node_iterator<char> itrA(a.end());
    itrA--;
    ASSERT_EQ(*itrA, 6);
    itrA = a.begin();
    ASSERT_EQ(*itrA, 1);
    a.merge(c);
    itrA = a.end();
    itrA--;
    ASSERT_EQ(*itrA, 8);
    ASSERT_EQ(a.size(), 6);
}

TEST(list, sort) {
    List<char> a{1, 6, 3};
    a.sort();
    node_iterator<char> itrA(a.end());
    --itrA;
    ASSERT_EQ(*itrA, 6);
    ASSERT_EQ(a.size(), 3);
}

TEST(list, sort2) {
    List<char> a{1, 6, 3, 4, -5, 3, 3, 6, 1, 6, 2};
    a.sort();
    node_iterator<char> itrA(a.end());
    --itrA;
    ASSERT_EQ(*itrA, 6);
    --itrA;
    ASSERT_EQ(*itrA, 6);
    --itrA;
    ASSERT_EQ(*itrA, 6);
    --itrA;
    ASSERT_EQ(*itrA, 4);
    itrA = a.begin();
    itrA = itrA + 1;
    ASSERT_EQ(*itrA, 1);
    itrA = itrA - 1;
    ASSERT_EQ(*itrA, -5);
    ASSERT_EQ(a.size(), 11);
}

TEST(list, sort3_runtime) {
    List<int> a;
    node_iterator<int> itrA(a.end());
    int* k = new int[10000];
    for (int i = 10001; i > 1; --i) {
        k[10001 - i] = i - 1;
    }
    for (int i = 0; i < 10000; ++i) {
        a.insert(itrA, k[i]);
    }
    itrA--;
    ASSERT_EQ(*itrA, 1);
    itrA = a.begin();
    ASSERT_EQ(*itrA, 10000);
    a.sort();
    itrA = a.begin();
    ASSERT_EQ(*itrA, 1);
    itrA = a.end();
    --itrA;
    itrA = itrA - 60;
    ASSERT_EQ(*itrA, 9940);
    delete[] k;
}