#include <gtest/gtest.h>

#include "s21_list.h"

struct two_ints {
    int a;
    double b;
} two_ints;

TEST(list, init_1) {
    s21_List<int> a;
    ASSERT_TRUE(a.empty());

    s21_List<int> b(5, 4);
    ASSERT_EQ(b.size(), 5);
}

TEST(list, init_2) {
    s21_List<int> b({5, 4});
    ASSERT_EQ(b.size(), 2);

    s21_List<int> d{5, 4};
    ASSERT_EQ(d.size(), 2);
}

TEST(list, init_3) {
    s21_List<std::string> c({"afdfdf", "dfdh", "djfhd", "dkfjd", "dhfd"});
    ASSERT_EQ(c.size(), 5);

    s21_List<double> e{5, 4, 3, 2, 1};
    ASSERT_EQ(e.size(), 5);

    s21_List<double> f{{5, 4, 3, 2, 1}};
    ASSERT_EQ(f.size(), 5);

    s21_List<double> g({5, 4, 3, 2, 1});
    ASSERT_EQ(f.size(), 5);

    s21_List<double> h({{5, 4, 3, 2, 1}});
    ASSERT_EQ(h.size(), 5);
}

TEST(list, copy) {
    s21_List<std::string> c({"afdfdf", "dfdh", "djfhd", "dkfjd", "dhfd"});
    ASSERT_EQ(c.size(), 5);

    s21_List<std::string> e{c};
    ASSERT_EQ(e.size(), 5);

    s21_List<struct two_ints> f{{5,3}, {6, 4.0}, {-456, 2}};
    s21_List<struct two_ints> g(f);

    ASSERT_EQ(f.size(), 3);
    ASSERT_EQ(g.size(), 3);
}

TEST(list, assignmnt) {
    s21_List<double> e{5, 4, 3, 2, 1};
    s21_List<double> f{5, 4, 3};
    e = f;

    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(f.size(), 3);
}

TEST(list, front_back) {
    s21_List<double> e{5, 4, 3, 2, 1};
    ASSERT_EQ(e.front(), 5);
    ASSERT_EQ(e.back(), 1);
}

TEST(list, front_back_2) {
    s21_List<char> e{5, 4, 3, 2, 1};
    s21_List<char> f = e;
    ASSERT_EQ(f.front(), 5);
    ASSERT_EQ(f.back(), 1);
}

TEST(list, front_back_3) {
    s21_List<char> g{5, 4, 3, 2, 1};
    s21_List<char> h(g);
    ASSERT_EQ(h.front(), 5);
    ASSERT_EQ(h.back(), 1);

}

TEST(list, begin_end) {
    s21_List<char> g{5, 4, 3, 2, 1};
    s21_List<char> h(g);
    node_iterator<char> a1(h.begin());
    node_iterator<char> a2(g.begin());
    ASSERT_EQ(a1.node_iterator::get_elem()->s21_Node<char>::get_elem(), 5);
    ASSERT_EQ(a2.node_iterator::get_elem()->s21_Node<char>::get_elem(), 5);

    a1 = h.end();
    a2 = g.end();
    ASSERT_EQ(a1.node_iterator::get_elem()->s21_Node<char>::get_elem(), 1);
    ASSERT_EQ(a2.node_iterator::get_elem()->s21_Node<char>::get_elem(), 1);
}

TEST(list, insert_1) {
    s21_List<char> g{5, 4, 3, 2, 1};
    node_iterator<char> a1;
    a1 = g.begin();
    ++a1;
    a1++;
    g.insert(a1, 35);
    g.insert(a1, 43);
    ASSERT_EQ(g.size(), 7);

    a1 = g.end();
    g.insert(a1,24);
    g.insert(a1,234);
    ASSERT_EQ(g.size(), 9);
}
TEST(list, insert_2) {
    s21_List<char> g;
    node_iterator<char> a1;
    a1 = g.begin();
    ++a1;
    a1++;
    // g.insert(a1, 35);
    // g.insert(a1, 43);
    // ASSERT_EQ(g.size(), 2);

    // a1 = g.end();
    // g.insert(a1,24);
    // g.insert(a1,234);
    // ASSERT_EQ(g.size(), 4);
}

// TEST(list, erase) {
//     s21_List<char> g{5, 4, 3, 2, 1};
//     s21_Node<char> * a1 = g.begin();
//     g.erase(a1);
//     a1 = g.begin();
//     g.erase(a1);
//     ASSERT_EQ(g.size(), 3);

//     a1 = g.end();
//     g.erase(a1);
//     a1 = g.end();
//     g.erase(a1);
//     ASSERT_EQ(g.size(), 1);

// }

// TEST(list, back1) {
//     s21_List<char> g{5, 4, 3, 2, 1};
//     s21_List<char> g2(g);
//     g.erase(g.end());
//     g2.pop_back();
//     ASSERT_EQ(g.size(), 4);
//     ASSERT_EQ(g.size(), g2.size());

// }

// TEST(list, back2) {
//     s21_List<char> g{5, 4, 3, 2, 1};
//     s21_List<char> g2(g);
//     g.insert(g.end(), 3);
//     g2.push_back(3);
//     ASSERT_EQ(g.size(), 6);
//     ASSERT_EQ(g.size(), g2.size());

// }

// TEST(list, front1) {
//     s21_List<char> g{5, 4, 3, 2, 1};
//     s21_List<char> g2(g);
//     g.insert(g.begin(), 3);
//     g2.push_front(3);
//     ASSERT_EQ(g.size(), 6);
//     ASSERT_EQ(g.size(), g2.size());
// }

// TEST(list, front2) {
//     s21_List<char> g{5, 4, 3, 2, 1};
//     s21_List<char> g2(g);
//     node_iterator<char> itr(g.begin());
//     ++itr;
//     ++itr;

//     g.erase(g.begin());
//     g2.pop_front();
//     ASSERT_EQ(g.size(), 4);
//     ASSERT_EQ(g.size(), g2.size());
// }

// TEST(list, front2) {
//     s21_List<char> g{5, 4, 3, 2, 1};
//     s21_List<char> g2(g);
//     g.erase(g.begin());
//     g2.pop_front();
//     ASSERT_EQ(g.size(), 4);
//     ASSERT_EQ(g.size(), g2.size());
// }
