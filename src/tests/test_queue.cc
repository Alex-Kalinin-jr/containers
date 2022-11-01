#include <gtest/gtest.h>
#include "../s21_containers.h"
using namespace s21;

TEST(queue, init_1) {
    Queue<int> a;
    Queue<double> b;
    Queue<std::string> c;
    ASSERT_EQ(sizeof(a), sizeof(b));
    ASSERT_EQ(sizeof(a), sizeof(c));
    ASSERT_EQ(sizeof(b), sizeof(c));
}

TEST(queue, init_2) {
    Queue<int> a{3};
    Queue<double> b{1, 2};
    Queue<std::string> c{"abc", "def", ""};
    ASSERT_EQ(sizeof(a), sizeof(b));
    ASSERT_EQ(sizeof(a), sizeof(c));
    ASSERT_EQ(sizeof(b), sizeof(c));
}

TEST(queue, init_3) {
    Queue<int> a{3, 4, 5, 6, 7, 8};
    Queue<int> b(a);
    ASSERT_EQ(sizeof(a), sizeof(b));
}

TEST(queue, init_4) {
    Queue<int> a{3, 4, 5, 6, 7, 8};
    Queue<int> b = a;
    ASSERT_EQ(sizeof(a), sizeof(b));
}

TEST(queue, init_5) {
    Queue<int> b = Queue<int>{3, 4, 5, 6, 7, 8};
    Queue<int> a{3, 4, 5, 6, 7, 8};
    list_Node<int> c(5);
    ASSERT_EQ(sizeof(b), sizeof(c));
    ASSERT_EQ(sizeof(b), sizeof(a));
}

TEST(queue, front1) {
    Queue<int> b = Queue<int>{3, 4, 5, 6, 7, 8};
    Queue<int> a{3, 4, 5, 6, 7, 8};
    ASSERT_EQ(a.front(), b.front());
}

TEST(queue, front2) {
    Queue<int> b = Queue<int>{3, 4, 5, 6, 7, 8};
    Queue<int> a{5};
    ASSERT_NE(a.front(), b.front());
}

TEST(queue, back1) {
    Queue<int> b = Queue<int>{3, 4, 5, 6, 7, 8};
    Queue<int> a{3, 4, 5, 6, 7, 8};
    ASSERT_EQ(a.back(), b.back());
}

TEST(queue, back2) {
    Queue<int> b = Queue<int>{3, 4, 5, 6, 7, 8};
    Queue<int> a{5};
    ASSERT_NE(a.back(), b.back());
}

TEST(queue, empty1) {
    Queue<int> b = Queue<int>{3, 4, 5, 6, 7, 8};
    Queue<int> a(b);
    ASSERT_FALSE(a.empty());
    Queue<int> c;
    Queue<int> d = c;
    ASSERT_TRUE(c.empty());
    ASSERT_TRUE(d.empty());
}

TEST(queue, empty2) {
    Queue<int> b = Queue<int>{3, 4};
    ASSERT_FALSE(b.empty());
    b.pop();
    ASSERT_FALSE(b.empty());
    b.pop();
    ASSERT_TRUE(b.empty());  //  wtf WTF WTF WTF WTF WTF WTF
}

TEST(queue, size1) {
    Queue<int> b = Queue<int>{3, 4, 6, 7, 8, 14};
    ASSERT_EQ(b.size(), 6);
    b.pop();
    ASSERT_EQ(b.size(), 5);
    b.pop();
    b.pop();
    ASSERT_EQ(b.size(), 3);
    b.pop();
    b.pop();
    b.pop();
    ASSERT_EQ(b.size(), 0);
}

TEST(queue, size2) {
    Queue<int> b = Queue<int>{3, 4, 6, 7, 8, 14};
    Queue<int> c = b;
    ASSERT_EQ(c.size(), 6);
}

TEST(queue, size3) {
    Queue<int> b = Queue<int>{3, 4, 6, 7, 8, 14};
    Queue<int> c(b);
    ASSERT_EQ(c.size(), 6);
}

TEST(queue, size4) {
    Queue<int> c(Queue<int>{3, 4, 6, 7, 8, 14});
    ASSERT_EQ(c.size(), 6);
}

TEST(queue, size5) {
    Queue<int> c;
    ASSERT_EQ(c.size(), 0);
}

TEST(queue, push1) {
    Queue<int> c;
    c.push(34);
    ASSERT_EQ(c.size(), 1);
    ASSERT_EQ(c.back(), 34);
}

TEST(queue, push2) {
    Queue<int> c(Queue<int>{3, 4, 6, 7, 8, 14});
    c.push(34);
    ASSERT_EQ(c.size(), 7);
    ASSERT_EQ(c.back(), 34);
    c.pop();
    ASSERT_EQ(c.size(), 6);
    ASSERT_EQ(c.back(), 34);
}

TEST(queue, push3) {
    int a = 3;
    Queue<int> c;
    c.push(a);
    c.pop();  //  WTF WTF WTF WTF WTF WTF (if climb on 1 line)
    c.push(35);
    c.push(36);
    c.push(37);
    ASSERT_EQ(c.size(), 3);
    ASSERT_EQ(c.back(), 37);
    c.pop();
    c.pop();
    ASSERT_EQ(c.size(), 1);
    ASSERT_EQ(c.back(), 37);
    ASSERT_EQ(c.front(), 37);
}

TEST(queue, runtime1) {
    Queue<int> c;
    int d = 0;
    while (++d != 10000000) c.push(d);
    ASSERT_EQ(c.size(), 9999999);
    ASSERT_EQ(c.back(), 10000000);
}

TEST(queue, runtime2) {
    Queue<int> c;
    int d = 0;
    while (++d != 10000000) c.push(d);
    ASSERT_EQ(c.size(), 9999999);
    ASSERT_EQ(c.back(), 10000000);
    while (--d != 0) c.pop();
    ASSERT_EQ(c.size(), 0);
}

TEST(queue, swap1) {
    Queue<int> b = Queue<int>{3, 4, 6, 7, 8, 14};
    Queue<int> d = Queue<int>{3, 4, 6};
    b.swap(d);
    ASSERT_EQ(b.size(), 3);
    ASSERT_EQ(d.size(), 6);
}

TEST(queue, swap2) {
    Queue<int> b = Queue<int>{3, 4, 6, 7, 8, 14};
    Queue<int> d;
    Queue<int> e(d);
    b.swap(e);
    ASSERT_EQ(b.size(), 0);
    ASSERT_EQ(e.size(), 6);
    ASSERT_EQ(e.back(), 14);
}
