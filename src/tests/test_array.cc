#include <gtest/gtest.h>
#include "../s21_containersplus.h"
using namespace s21;

TEST(array_Constructors, Test_01) {
  array<int, 5> a;
  array<int, 5> b = {1, 2, 3, 4, 5};
  array<int, 5> c{1, 2, 3, 4, 5};
  array<int, 5> g(c);

  auto it = b.begin();
  auto it2 = c.begin();
  ASSERT_EQ(*it, *it2);
  ASSERT_EQ(*(g.begin()), *it2);
  ASSERT_EQ(*(g.begin() + 3), *(it2+3));

  array<int, 5> d = {std::move(b)};

  ASSERT_FALSE(b.empty());
  ASSERT_EQ(*(d.begin()), 1);
}

TEST(array, copy_construct) {
  array<int, 4> myArr = {1, 2, 3, 4};
  array<int, 4> other = myArr;
  ASSERT_EQ(other[0], 1);
  ASSERT_EQ(other[1], 2);
  ASSERT_EQ(other[2], 3);
  ASSERT_EQ(other[3], 4);
}

TEST(Element_access, Test_01) {
  array<int, 5> a = {1, 2, 3, 4, 5};
  ASSERT_EQ(*(a.data()), 1);
  ASSERT_EQ(a.at(0), 1);
  ASSERT_EQ(a[0], 1);
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 5);
}

TEST(array_Iterators, Test_01) {
  array<int, 5> a = {1, 2, 3, 4, 5};
  ASSERT_EQ(*(a.begin()), 1);
  ASSERT_EQ(*(a.end() - 1), 5);
}

TEST(array_Capacity, Test_01) {
  array<int, 5> a = {1, 2, 3, 4, 5};
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.max_size(), 5);
}

TEST(array_Modifiers, Test_01) {
  array<int, 5> a = {1, 2, 3, 4, 5};
  array<int, 5> b = {5, 4, 3, 2, 1};
  array<int, 5> b2 = {1, 2, 3, 4, 5};
  array<int, 5> a2 = {5, 4, 3, 2, 1};

  a.swap(b);
  
  ASSERT_TRUE(a == a2);
  ASSERT_TRUE(b == b2);

  array<int, 5> f;
  array<int, 5> f2 = {5, 5, 5, 5, 5};
  f.fill(5);
  ASSERT_TRUE(f == f2);
}


TEST(array, front_back) {
  array<int, 4> myArr = {1, 2, 3, 4};
  ASSERT_EQ(1, myArr.front());
  ASSERT_EQ(4, myArr.back());
}

TEST(array, at) {
  array<int, 4> myArr = {1, 2, 3, 4};
  ASSERT_EQ(1, myArr.at(0));
  ASSERT_EQ(2, myArr.at(1));
  ASSERT_EQ(3, myArr.at(2));
  ASSERT_EQ(4, myArr.at(3));
}
