#include <gtest/gtest.h>

#include "s21_list.h"

TEST(list, init_1) {
    s21_List<int> a;
    ASSERT_TRUE(&a);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}