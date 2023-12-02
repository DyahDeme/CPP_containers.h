#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "my_set.h"

TEST(test_constructor_set, t1) {
  std::set<int> st({1, 2, 3, 4, 3, 5});
  my::Set<int> St({1, 2, 3, 4, 3, 5});
  auto it1 = st.begin();
  for (auto it2 = St.Begin(); it2 != St.End(); ++it2, ++it1)
    ASSERT_TRUE(*it1 == *it2);
}

TEST(test_constructor_set, t2) {
  my::Set<int> st1({1, 2, 3, 4, 3, 5});
  my::Set<int> st2(st1);

  auto it1 = st1.Begin();
  for (auto it2 = st2.Begin(); it2 != st2.End(); ++it2, ++it1)
    ASSERT_TRUE(*it1 == *it2);
}

TEST(test_empty_set, t1) {
  my::Set<int> st;
  ASSERT_TRUE(st.Empty() == 1);
}

TEST(test_empty_set, t2) {
  my::Set<int> st({1, 2, 3});
  ASSERT_TRUE(st.Empty() == 0);
}

TEST(test_size_set, t1) {
  my::Set<int> st({1, 2, 3});
  ASSERT_TRUE(st.Size() == 3);
}

TEST(test_max_size_set, t1) {
  my::Set<int> st({1, 2, 3});
  ASSERT_TRUE(st.Max_size() == SIZE_MAX / sizeof(int));
}

TEST(test_find_set, t1) {
  my::Set<int> st({1, 2, 3});
  auto it = st.Find(3);
  ASSERT_TRUE(*it == 3);
}

TEST(test_erase_set, test1) {
  my::Set<int> st({8, 10});
  my::Set<int> result({8});
  st.Erase(st.Find(10));
  auto itRes = result.Begin();
  for (auto it = st.Begin(); it != st.End(); ++it, ++itRes)
    EXPECT_EQ(*it, *itRes);
}

TEST(test_erase_set, test2) {
  my::Set<int> st({8, 10});
  my::Set<int> result({10});
  st.Erase(st.Find(8));
  auto itRes = result.Begin();
  for (auto it = st.Begin(); it != st.End(); ++it, ++itRes)
    EXPECT_EQ(*it, *itRes);
}

TEST(test_erase_set, test3) {
  my::Set<int> st({8, 5});
  my::Set<int> result({5});
  st.Erase(st.Find(8));
  auto itRes = result.Begin();
  for (auto it = st.Begin(); it != st.End(); ++it, ++itRes)
    EXPECT_EQ(*it, *itRes);
}

TEST(test_erase_set, test4) {
  my::Set<int> st({8, 5});
  my::Set<int> result({8});
  st.Erase(st.Find(5));
  auto itRes = result.Begin();
  for (auto it = st.Begin(); it != st.End(); ++it, ++itRes)
    EXPECT_EQ(*it, *itRes);
}

TEST(test_erase_set, test5) {
  my::Set<int> st({8, 5, 3});
  my::Set<int> result({8, 3});
  st.Erase(st.Find(5));
  auto itRes = result.Begin();
  for (auto it = st.Begin(); it != st.End(); ++it, ++itRes)
    EXPECT_EQ(*it, *itRes);
}

TEST(test_erase_set, test6) {
  my::Set<int> st({8, 4, 6, 5});
  my::Set<int> result({8, 5, 6});
  st.Erase(st.Find(4));
  auto itRes = result.Begin();
  for (auto it = st.Begin(); it != st.End(); ++it, ++itRes)
    EXPECT_EQ(*it, *itRes);
}

TEST(test_erase_set, test7) {
  my::Set<int> st({8, 10, 11, 12});
  my::Set<int> result({8, 11, 12});
  st.Erase(st.Find(10));
  auto itRes = result.Begin();
  for (auto it = st.Begin(); it != st.End(); ++it, ++itRes)
    EXPECT_EQ(*it, *itRes);
}

TEST(test_erase_set, test8) {
  my::Set<int> st({8, 10, 12, 11});
  my::Set<int> result({8, 11, 12});
  st.Erase(st.Find(10));
  auto itRes = result.Begin();
  for (auto it = st.Begin(); it != st.End(); ++it, ++itRes)
    EXPECT_EQ(*it, *itRes);
}

TEST(test_erase_set, test9) {
  my::Set<int> st({10, 12, 11});
  my::Set<int> result({11, 12});
  st.Erase(st.Find(10));
  auto itRes = result.Begin();
  for (auto it = st.Begin(); it != st.End(); ++it, ++itRes)
    EXPECT_EQ(*it, *itRes);
}

TEST(test_erase_set, test10) {
  my::Set<int> st({8, 3, 6, 5, 7});
  my::Set<int> result({8, 3, 6, 7});
  st.Erase(st.Find(5));
  auto itRes = result.Begin();
  for (auto it = st.Begin(); it != st.End(); ++it, ++itRes)
    EXPECT_EQ(*it, *itRes);
}

TEST(test_merge_set, t1) {
  my::Set<int> st1({1, 2, 3, 4, 5});
  my::Set<int> st2({3, 1});
  std::set<int> set1({1, 2, 3, 4, 5});
  std::set<int> set2({1, 3});

  st2.Merge(st1);
  set2.merge(set1);

  auto itSet = set1.begin();
  for (auto itSt = st1.Begin(); itSt != st1.End(); ++itSt, ++itSet)
    ASSERT_TRUE(*itSt == *itSet);

  ASSERT_TRUE(st1.Size() == set1.size());

  itSet = set2.begin();
  for (auto itSt = st2.Begin(); itSt != st2.End(); ++itSt, ++itSet)
    ASSERT_TRUE(*itSt == *itSet);

  ASSERT_TRUE(st2.Size() == set2.size());
}

TEST(test_swap_set, t1) {
  my::Set<int> st1({1, 2, 3, 4, 5});
  my::Set<int> st2({3, 1});
  std::set<int> set1({1, 2, 3, 4, 5});
  std::set<int> set2({1, 3});

  st2.Swap(st1);
  set2.swap(set1);

  auto itSet = set1.begin();
  for (auto itSt = st1.Begin(); itSt != st1.End(); ++itSt, ++itSet)
    ASSERT_TRUE(*itSt == *itSet);

  ASSERT_TRUE(st1.Size() == set1.size());

  itSet = set2.begin();
  for (auto itSt = st2.Begin(); itSt != st2.End(); ++itSt, ++itSet)
    ASSERT_TRUE(*itSt == *itSet);

  ASSERT_TRUE(st2.Size() == set2.size());
}

TEST(test_contains_set, t1) {
  my::Set<int> st1({1, 2, 3, 4, 5});
  ASSERT_TRUE(st1.Contains(2) == 1);
}

TEST(test_contains_set, t2) {
  my::Set<int> st1({1, 2, 3, 4, 5});
  ASSERT_TRUE(st1.Contains(223) == 0);
}

TEST(test_emplace_set, t1) {
  my::Set<int> st1;
  my::Set<int> st2{1, 2, 3};
  st1.Emplace(1, 2, 3);
  auto it1 = st1.Begin();
  for (auto it2 = st2.Begin(); it2 != st2.End(); ++it1, ++it2)
    ASSERT_TRUE(*it1 == *it2);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}