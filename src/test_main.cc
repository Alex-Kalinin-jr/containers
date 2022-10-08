#include <gtest/gtest.h>

#include "node.h"
#include "queue.h"
#include "stack.h"

#ifndef without_leaks
TEST(queue, throw1) {
    s21_Queue<int> a;
    ASSERT_THROW(a.front(), std::out_of_range);
}

TEST(queue, throw2) {
    s21_Queue<int> a;
    ASSERT_THROW(a.back(), std::out_of_range);
}

TEST(stack, top3) {
    s21_Stack<int> a;
    ASSERT_THROW(a.top(), std::out_of_range);
}
#endif

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}