#include <gtest/gtest.h>

#include <iostream>
#include <map>

#include "my_map.h"

TEST(test_constructor_map, t1) {
  std::map<int, int> mp({{1, 2}, {2, 5}, {23, 345}});
  my::Map<int, int> Mp({{1, 2}, {2, 5}, {23, 345}});
  auto it1 = mp.begin();
  for (auto it2 = Mp.Begin(); it2 != Mp.End(); ++it2, ++it1)
    ASSERT_TRUE((*it1).first == (*it2).first && (*it1).second == (*it2).second);
}

TEST(test_At_map, t1) {
  std::map<int, int> mp({{1, 2}, {2, 5}, {23, 345}});
  my::Map<int, int> Mp({{1, 2}, {2, 5}, {23, 345}});
  int result1 = mp.at(1);
  int result2 = Mp.At(1);
  ASSERT_TRUE(result1 == result2);
}

TEST(test_operator_brackets_map, t1) {
  std::map<int, int> mp({{1, 2}, {2, 5}, {23, 345}});
  my::Map<int, int> Mp({{1, 2}, {2, 5}, {23, 345}});
  int result1 = mp[1];
  int result2 = Mp[1];
  ASSERT_TRUE(result1 == result2);
}

TEST(test_empty_map, t1) {
  my::Map<int, int> mp({{1, 2}, {2, 5}, {23, 345}});
  ASSERT_TRUE(mp.Empty() == 0);
}

TEST(test_empty_map, t2) {
  my::Map<int, int> mp;
  ASSERT_TRUE(mp.Empty() == 1);
}

TEST(test_insert_map, t1) {
  std::map<int, int> mp({{1, 2}, {2, 5}, {23, 345}});
  my::Map<int, int> Mp({{1, 2}, {2, 5}});
  Mp.Insert({23, 345});
  auto it1 = mp.begin();
  for (auto it2 = Mp.Begin(); it2 != Mp.End(); ++it2, ++it1)
    ASSERT_TRUE((*it1).first == (*it2).first && (*it1).second == (*it2).second);
}

TEST(test_insert_map, t2) {
  std::map<int, int> mp({{1, 2}, {2, 5}, {23, 345}});
  my::Map<int, int> Mp({{1, 2}, {2, 5}});
  Mp.Insert(23, 345);
  auto it1 = mp.begin();
  for (auto it2 = Mp.Begin(); it2 != Mp.End(); ++it2, ++it1)
    ASSERT_TRUE((*it1).first == (*it2).first && (*it1).second == (*it2).second);
}

TEST(test_insert_map, t3) {
  std::map<int, int> mp({{1, 2}, {2, 5}, {23, 345}});
  my::Map<int, int> Mp({{1, 2}, {2, 5}});
  Mp.Insert_or_assign(23, 345);
  auto it1 = mp.begin();
  for (auto it2 = Mp.Begin(); it2 != Mp.End(); ++it2, ++it1)
    ASSERT_TRUE((*it1).first == (*it2).first && (*it1).second == (*it2).second);
}

TEST(test_insert_map, t4) {
  std::map<int, int> mp({{1, 2}, {2, 5}, {23, 345}});
  my::Map<int, int> Mp({{1, 2}, {2, 5}, {23, 344}});
  Mp.Insert_or_assign(23, 345);
  auto it1 = mp.begin();
  for (auto it2 = Mp.Begin(); it2 != Mp.End(); ++it2, ++it1)
    ASSERT_TRUE((*it1).first == (*it2).first && (*it1).second == (*it2).second);
}

TEST(test_merge_set, t1) {
  my::Map<int, int> Mp1({{1, 2}, {2, 5}, {23, 345}});
  my::Map<int, int> Mp2({{1, 2}});
  std::map<int, int> mp1({{1, 2}, {2, 5}, {23, 345}});
  std::map<int, int> mp2({{1, 2}});

  Mp2.Merge(Mp1);
  mp2.merge(mp1);

  auto itMap = mp1.begin();
  for (auto itMp = Mp1.Begin(); itMp != Mp1.End(); ++itMp, ++itMap)
    ASSERT_TRUE((*itMap).first == (*itMp).first &&
                (*itMap).second == (*itMp).second);

  ASSERT_TRUE(mp1.size() == Mp1.Size());

  itMap = mp2.begin();
  for (auto itMp = Mp2.Begin(); itMp != Mp2.End(); ++itMp, ++itMap)
    ASSERT_TRUE((*itMap).first == (*itMp).first &&
                (*itMap).second == (*itMp).second);

  ASSERT_TRUE(mp2.size() == Mp2.Size());
}

TEST(test_swap_set, t1) {
  my::Map<int, int> Mp1({{1, 2}, {2, 5}, {23, 345}});
  my::Map<int, int> Mp2({{1, 2}});
  std::map<int, int> mp1({{1, 2}, {2, 5}, {23, 345}});
  std::map<int, int> mp2({{1, 2}});

  Mp2.Swap(Mp1);
  mp2.swap(mp1);

  auto itMap = mp1.begin();
  for (auto itMp = Mp1.Begin(); itMp != Mp1.End(); ++itMp, ++itMap)
    ASSERT_TRUE((*itMap).first == (*itMp).first &&
                (*itMap).second == (*itMp).second);

  ASSERT_TRUE(mp1.size() == Mp1.Size());

  itMap = mp2.begin();
  for (auto itMp = Mp2.Begin(); itMp != Mp2.End(); ++itMp, ++itMap)
    ASSERT_TRUE((*itMap).first == (*itMp).first &&
                (*itMap).second == (*itMp).second);

  ASSERT_TRUE(mp2.size() == Mp2.Size());
}

TEST(test_contains_map, t2) {
  my::Map<int, int> mp({{1, 2}, {2, 5}, {23, 345}});
  ASSERT_TRUE(mp.Contains(24) == 0);
}

TEST(test_contains_map, t1) {
  my::Map<int, int> mp({{1, 2}, {2, 5}, {23, 345}});
  ASSERT_TRUE(mp.Contains(2) == 1);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}