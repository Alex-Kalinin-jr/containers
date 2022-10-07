#include <gtest/gtest.h>

#include "Stack.h"

TEST(stack, init_1) {
    s21_Stack<int> a;
    s21_Stack<double> b;
    s21_Stack<std::string> c;
    ASSERT_EQ(sizeof(a), sizeof(b));
    ASSERT_EQ(sizeof(a), sizeof(c));
    ASSERT_EQ(sizeof(b), sizeof(c));
}

TEST(stack, init_2) {
    s21_Stack<int> a {3};
    s21_Stack<double> b {1, 2};
    s21_Stack<std::string> c {"abc", "def", ""};
    ASSERT_EQ(sizeof(a), sizeof(b));
    ASSERT_EQ(sizeof(a), sizeof(c));
    ASSERT_EQ(sizeof(b), sizeof(c));
}

TEST(stack, init_3) {
    s21_Stack<int> a {3, 4, 5, 6, 7, 8};
    s21_Stack<int> b(a);
    ASSERT_EQ(sizeof(a), sizeof(b));
}

TEST(stack, init_4) {
    s21_Stack<int> a {3, 4, 5, 6, 7, 8};
    s21_Stack<int> b = a;
    ASSERT_EQ(sizeof(a), sizeof(b));
}

TEST(stack, init_5) {

    s21_Stack<int> b = s21_Stack<int> {3, 4, 5, 6, 7, 8};
    s21_Stack<int> a {3, 4, 5, 6, 7, 8};
    s21_Node<int> c(5);
    ASSERT_NE(sizeof(b), sizeof(c));
    ASSERT_EQ(sizeof(b), sizeof(a));
}

TEST(stack, top1) {
    s21_Stack<int> b = s21_Stack<int> {3, 4, 5, 6, 7, 8};
    s21_Stack<int> a {3, 4, 5, 6, 7, 8};
    ASSERT_EQ(a.top(), b.top());
}

TEST(stack, top2) {
    s21_Stack<int> b = s21_Stack<int> {3, 4, 5, 6, 7, 8};
    s21_Stack<int> a{5};
    ASSERT_NE(a.top(), b.top());
}

#ifndef without_leaks
TEST(stack, top3) {
    s21_Stack<int> a;
    ASSERT_THROW(a.top(), std::out_of_range);
}
#endif

TEST(stack, empty1) {
    s21_Stack<int> b = s21_Stack<int> {3, 4, 5, 6, 7, 8};
    s21_Stack<int> a(b);
    ASSERT_FALSE(a.empty());
    s21_Stack<int> c;
    s21_Stack<int> d = c;
    ASSERT_TRUE(c.empty());
    ASSERT_TRUE(d.empty());
}

TEST(stack, empty2) {
    s21_Stack<int> b = s21_Stack<int> {3, 4};
    ASSERT_FALSE(b.empty());
    b.pop();
    ASSERT_FALSE(b.empty());
    b.pop();
    ASSERT_TRUE(b.empty());
}

TEST(stack, size1) {
    s21_Stack<int> b = s21_Stack<int> {3, 4, 6, 7, 8, 14};
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

TEST(stack, size2) {
    s21_Stack<int> b = s21_Stack<int> {3, 4, 6, 7, 8, 14};
    s21_Stack<int> c = b;
    ASSERT_EQ(c.size(), 6);
}

TEST(stack, size3) {
    s21_Stack<int> b = s21_Stack<int> {3, 4, 6, 7, 8, 14};
    s21_Stack<int> c(b);
    ASSERT_EQ(c.size(), 6);
}

TEST(stack, size4) {
    s21_Stack<int> c(s21_Stack<int> {3, 4, 6, 7, 8, 14});
    ASSERT_EQ(c.size(), 6);
}

TEST(stack, size5) {
    s21_Stack<int> c;
    ASSERT_EQ(c.size(), 0);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
