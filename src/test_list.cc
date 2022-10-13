#include <gtest/gtest.h>

#include "s21_list.h"

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

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}