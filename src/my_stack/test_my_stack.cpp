#include <gtest/gtest.h>

#include <iostream>
#include <stack>

#include "my_stack.h"

TEST(constructor_1, test_1) {
  my::stack<int> s;

  EXPECT_EQ(s.empty(), true);
}

TEST(constructor_2, test_1) {
  my::stack<int> s({1, 2, 3});

  EXPECT_EQ(s.top(), 3);
  EXPECT_EQ(s.size(), 3);
}

TEST(push_1, test_2) {
  my::stack<int> s;

  s.push(1);
  s.push(2);

  EXPECT_EQ(s.empty(), false);
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), 2);
}

TEST(push_2, test_2) {
  my::stack<int> s;

  s.push(1239128);
  s.push(-123193);

  EXPECT_EQ(s.empty(), false);
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), -123193);
}

TEST(pop_1, test_3) {
  my::stack<int> s({1, 2, 3});

  s.pop();
  s.pop();

  EXPECT_EQ(s.empty(), false);
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), 1);
}

TEST(swap_1, test_4) {
  my::stack<int> s1({1, 2, 3});
  my::stack<int> s2({1});

  s1.swap(s2);

  EXPECT_EQ(s1.size(), 1);
  EXPECT_EQ(s1.top(), 1);

  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}

TEST(empty_1, test_5) {
  my::stack<int> s1;

  EXPECT_EQ(s1.empty(), true);
}

TEST(empty_2, test_5) {
  my::stack<int> s1({1, 2, 3});

  EXPECT_EQ(s1.empty(), false);
}

TEST(size_1, test_6) {
  my::stack<int> s1;

  EXPECT_EQ(s1.size(), 0);
}

TEST(size_2, test_7) {
  my::stack<int> s1({1, 2, 3});

  EXPECT_EQ(s1.size(), 3);
}

TEST(top_1, test_8) {
  my::stack<int> s1({1, 2, 3});

  EXPECT_EQ(s1.top(), 3);
}

TEST(emplace_1, test_10) {
  my::stack<int> s1({1, 2, 3});
  s1.emplace_front(4, 5, 6);
  EXPECT_EQ(s1.size(), 6);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}