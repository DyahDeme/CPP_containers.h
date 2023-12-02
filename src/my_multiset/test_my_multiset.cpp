#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "my_multiset.h"

TEST(test_constructor_multiset, t1) {
  std::multiset<int> st({1, 2, 3, 4, 3, 5});
  my::Multiset<int> St({1, 2, 3, 4, 3, 5});
  auto it1 = st.begin();
  for (auto it2 = St.Begin(); it2 != St.End(); ++it2, ++it1)
    ASSERT_TRUE(*it1 == *it2);
}

TEST(test_constructor_multiset, t2) {
  my::Multiset<int> st({1, 2, 3, 4, 3, 5});
  my::Multiset<int> St(st);
  auto it1 = st.Begin();
  for (auto it2 = St.Begin(); it2 != St.End(); ++it2, ++it1)
    ASSERT_TRUE(*it1 == *it2);
}

TEST(test_equal_range_multiset, t1) {
  my::Multiset<int> st({1, 2, 3, 4, 3, 5});
  auto answer = st.Equal_range(3);
  ASSERT_TRUE(*answer.first == 3 && *answer.second == 4);
}

TEST(test_lower_bound_multiset, t1) {
  my::Multiset<int> st({1, 2, 3, 4, 3, 5});
  auto answer = st.Lower_bound(3);
  ASSERT_TRUE(*answer == 3);
}

TEST(test_upper_bound_multiset, t1) {
  my::Multiset<int> st({1, 2, 3, 4, 3, 5});
  auto answer = st.Upper_bound(3);
  ASSERT_TRUE(*answer == 4);
}

TEST(test_swap_multiset, t1) {
  my::Multiset<int> st1({1, 2, 3, 4, 5});
  my::Multiset<int> st2({3, 1});
  std::multiset<int> set1({1, 2, 3, 4, 5});
  std::multiset<int> set2({1, 3});

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

TEST(test_merge_multiset, t1) {
  my::Multiset<int> st1({1, 2, 3, 4, 5});
  my::Multiset<int> st2({3, 1});
  std::multiset<int> set1({1, 2, 3, 4, 5});
  std::multiset<int> set2({1, 3});

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

TEST(test_emplace_multiset, t1) {
  my::Multiset<int> st1;
  my::Multiset<int> st2{1, 2, 3};
  st1.Emplace(1, 2, 3);
  auto it1 = st1.Begin();
  for (auto it2 = st2.Begin(); it2 != st2.End(); ++it1, ++it2)
    ASSERT_TRUE(*it1 == *it2);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}