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
    s21_Stack<int> a {3, 4, 5, 6, 7, 8};
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

#ifndef without_leaks

#endif

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
