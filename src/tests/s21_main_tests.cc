#include "s21_vector_test.cc"
#include "test_multiset.cc"
#include "test_queue.cc"
#include "test_list.cc"
#include "test_stack.cc"
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
  
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
