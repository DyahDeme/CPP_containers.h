#include <gtest/gtest.h>

#include <array>

#include "my_array.h"

TEST(test_constructor_array, t1) {
  std::array<int, 5> a;
  my::array<int, 5> A;
  ASSERT_TRUE(a.size() == A.size());
}

TEST(test_constructor_array, t2) {
  std::array<int, 5> a({1, 2, 3, 4, 5});
  my::array<int, 5> A({1, 2, 3, 4, 5});
  ASSERT_TRUE(a.size() == A.size());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == A.at(i));
  }
}

TEST(test_constructor_array, t3) {
  my::array<int, 5> *a = new my::array<int, 5>({1, 19, 4, 5, 6});
  my::array<int, 5> b(*a);
  ASSERT_TRUE(a->size() == b.size());
  for (size_t i = 0; i < a->size(); ++i) {
    ASSERT_TRUE(a->at(i) == b.at(i));
  }
  delete a;
}

TEST(test_constructor_array, t4) {
  my::array<int, 5> a({61, 23, 32, 53, 74});
  my::array<int, 5> c({61, 23, 32, 53, 74});
  my::array<int, 5> b(std::move(a));
  ASSERT_TRUE(b.size() == 5);
  for (size_t i = 0; i < b.size(); ++i) {
    ASSERT_TRUE(b.at(i) == c.at(i));
  }
}

TEST(test_operators_array, t1) {
  my::array<int, 5> *a = new my::array<int, 5>({1, 19, 4, 5, 6});
  my::array<int, 5> b;
  b = *a;
  ASSERT_TRUE(a->size() == b.size());
  for (size_t i = 0; i < a->size(); ++i) {
    ASSERT_TRUE(a->at(i) == b.at(i));
  }
  delete a;
}

TEST(test_operators_array, t2) {
  my::array<int, 5> a({1, 2, 3, 4, 5});
  my::array<int, 5> b;
  b = std::move(a);
  ASSERT_TRUE(b.size() == 5);
  for (size_t i = 0; i < b.size(); ++i) {
    ASSERT_TRUE(b.at(i) == (int)(i + 1));
  }
}

TEST(test_operators_array, t3) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a[i] == A[i]);
  }
}

TEST(test_access_array, t1) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(a.front() == A.front());
}

TEST(test_access_array, t2) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(a.back() == A.back());
}

TEST(test_access_array, t3) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(*a.data() == *A.data());
}

TEST(test_iterator_array, t1) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(*a.begin() == *A.begin());
}

TEST(test_iterator_array, t2) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(*(a.end() - 1) == *(A.end() - 1));
}

TEST(test_capacity_array, t1) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(a.empty() == A.empty());
  std::array<int, 9> b;
  my::array<int, 9> B;
  ASSERT_TRUE(b.empty() == B.empty());
}

TEST(test_capacity_array, t2) {
  std::array<int, 9> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE(a.size() == A.size());
  std::array<int, 15> b;
  my::array<int, 15> B;
  ASSERT_TRUE(b.size() == B.size());
}

TEST(test_capacity_array, t3) {
  std::array<int, 15> a;
  my::array<int, 15> A;
  ASSERT_TRUE(a.max_size() == A.max_size());
  std::array<double, 6> b;
  my::array<double, 6> B;
  ASSERT_TRUE(b.max_size() == B.max_size());
  std::array<std::array<int, 100>, 6> c;
  my::array<std::array<int, 100>, 6> C;
  ASSERT_TRUE(c.max_size() == C.max_size());
}

TEST(test_modifiers_array, t1) {
  my::array<int, 9> a({1, 2, 5, 5, 5, 5, 5, 5, 9});
  my::array<int, 9> A({1, 2, 3, 4, 5, 6, 7, 8, 9});
  my::array<int, 9> b({1, 2, 3, 4, 5, 6, 7, 8, 9});
  a.swap(A);
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(b.at(i) == a.at(i));
  }
}

TEST(test_modifiers_array, t2) {
  my::array<int, 9> a({1, 2, 5, 5, 5, 5, 5, 5, 9});
  a.fill(16);
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_TRUE(a.at(i) == 16);
  }
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}