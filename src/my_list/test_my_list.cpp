#include <gtest/gtest.h>

#include <iostream>
#include <list>

#include "my_list.h"

template <typename T>
void check_lists(my::list<T> &l, std::list<T> &sl) {
  ASSERT_EQ(l.size(), sl.size());
  ASSERT_EQ(l.front(), sl.front());
  ASSERT_EQ(l.back(), sl.back());
  auto i = l.begin();
  auto j = sl.begin();
  for (; i != l.end() && j != sl.end(); ++i, ++j) {
    ASSERT_EQ(*i, *j);
  }
  i = l.end();
  j = sl.end();
  --i;
  --j;
  for (; i != l.begin() && j != sl.begin(); --i, --j) {
    ASSERT_EQ(*i, *j);
  }
  if (!l.empty() && !sl.empty()) {
    ASSERT_EQ(*i, *j);
  }
}

template <typename T>
void show(const std::list<T> &l) {
  for (auto i = l.begin(); i != l.end(); ++i) std::cout << *i << ' ';
  std::cout << std::endl;
}

template <typename T>
void showback(const std::list<T> &l) {
  auto i = l.end();
  for (--i; i != l.begin(); --i) std::cout << *i << ' ';
  std::cout << *i << '\n';
}

TEST(init, def) {
  my::list<int> l;
  std::list<int> ll;
  ASSERT_EQ(l.front(), ll.front());
  ASSERT_EQ(l.back(), ll.back());
}

TEST(init, init_list) {
  my::list<int> l({1, 2, 3, 4, 5, 6});
  std::list<int> ll({1, 2, 3, 4, 5, 6});
  ASSERT_EQ(l.size(), ll.size());
  while (!l.empty()) {
    check_lists(l, ll);
    l.pop_front();
    ll.pop_front();
  }
}

TEST(init, copy) {
  my::list<int> l({1, 2});
  my::list<int> l_copy(l);
  std::list<int> sl({1, 2});
  std::list<int> sl_copy(sl);
  check_lists(l, sl);
  check_lists(l_copy, sl_copy);
}

TEST(iterator, begin_eq) {
  my::list<int> l({1, 2, 3, 4, 5});
  ASSERT_FALSE(l.begin() != l.begin());
}

TEST(iterator, begin_eq_eq) {
  my::list<int> l({1, 2, 3, 4, 5});
  ASSERT_TRUE(l.begin() == l.begin());
}

TEST(iterator, begin) {
  my::list<int> l({1, 2, 3, 4, 5});
  std::list<int> ll({1, 2, 3, 4, 5});
  ASSERT_EQ(*l.begin(), *ll.begin());
}

TEST(iterator, end_prev) {
  my::list<int> l({1, 2, 3, 4, 5});
  std::list<int> ll({1, 2, 3, 4, 5});
  auto i = l.end();
  auto j = ll.end();
  --i;
  --j;
  ASSERT_EQ(*i, *j);
}

TEST(iterator, minus) {
  my::list<int> l({1, 2, 3, 4, 5});
  std::list<int> ll({1, 2, 3, 4, 5});
  auto i = l.end();
  auto j = ll.end();
  i--;
  j--;
  ASSERT_EQ(*i, *j);
}

TEST(iterator, plus) {
  my::list<int> l({1, 2, 3, 4, 5});
  std::list<int> ll({1, 2, 3, 4, 5});
  auto i = l.begin();
  auto j = ll.begin();
  i++;
  j++;
  ASSERT_EQ(*i, *j);
}

TEST(iterator, const_dereference) {
  my::list<int> l({1, 2, 3, 4, 5});
  std::list<int> ll({1, 2, 3, 4, 5});
  my::list<int>::const_iterator i(l.begin());
  std::list<int>::const_iterator j = ll.begin();
  i++;
  j++;
  ASSERT_EQ(*i, *j);
}

TEST(init, same_lists) {
  my::list<int> l({1, 7, 6, 5, 4, 3, 2, 1});
  std::list<int> ll({1, 7, 6, 5, 4, 3, 2, 1});
  auto i = l.begin();
  auto j = ll.begin();
  for (; i != l.end() && j != ll.end(); ++i, ++j) {
    ASSERT_EQ(*i, *j);
  }
}

TEST(init, same_lists_backwards) {
  my::list<int> l({1, 7, 6, 5, 4, 3, 2, 1});
  std::list<int> ll({1, 7, 6, 5, 4, 3, 2, 1});
  auto i = l.end();
  auto j = ll.end();
  --i;
  --j;
  for (; i != l.begin() && j != ll.begin(); --i, --j) ASSERT_EQ(*i, *j);
  ASSERT_EQ(*i, *j);
}

TEST(init, move) {
  std::cout << "HERE\n";
  my::list<int> l({1, 6, 5, 2, 3, 5, 1});
  my::list<int> l_move(std::move(l));
  std::list<int> sl({1, 6, 5, 2, 3, 5, 1});
  std::list<int> sl_move(std::move(sl));
  ASSERT_EQ(l_move.size(), sl_move.size());
  ASSERT_EQ(l.size(), sl.size());
  check_lists(l_move, sl_move);
  check_lists(l, sl);
}

TEST(operator, move) {
  my::list<int> l({1, 6, 5, 2, 3, 5, 1});
  my::list<int> l_move;
  l_move = std::move(l);
  std::list<int> sl({1, 6, 5, 2, 3, 5, 1});
  std::list<int> sl_move;
  sl_move = std::move(sl);
  check_lists(l, sl);
  check_lists(l_move, sl_move);
}

TEST(push, back) {
  my::list<int> l;
  std::list<int> sl;
  l.push_back(5);
  sl.push_back(5);
  check_lists(l, sl);
  l.push_back(10);
  sl.push_back(10);
  check_lists(l, sl);
}

TEST(push, front) {
  my::list<int> l;
  std::list<int> sl;
  l.push_front(5);
  sl.push_front(5);
  check_lists(l, sl);
  l.push_front(10);
  sl.push_front(10);
  check_lists(l, sl);
}

TEST(push, for_front) {
  my::list<int> l;
  std::list<int> sl;
  for (int i = 0; i < 100; ++i) {
    l.push_front(i);
    sl.push_front(i);
    check_lists(l, sl);
  }
}

TEST(push, for_back) {
  my::list<int> l;
  std::list<int> sl;
  for (int i = 0; i < 100; ++i) {
    l.push_back(i);
    sl.push_back(i);
    check_lists(l, sl);
  }
}

TEST(pop, front) {
  my::list<int> l({1, 2, 4, 5, 2, 1});
  std::list<int> sl({1, 2, 4, 5, 2, 1});
  check_lists(l, sl);
  l.pop_front();
  sl.pop_front();
  check_lists(l, sl);
}

TEST(pop, back) {
  my::list<int> l({1, 2, 4, 5, 2, 1});
  std::list<int> sl({1, 2, 4, 5, 2, 1});
  check_lists(l, sl);
  l.pop_back();
  sl.pop_back();
  check_lists(l, sl);
}

TEST(pop, back_one) {
  my::list<int> l{2};
  std::list<int> sl{2};
  check_lists(l, sl);
  l.pop_back();
  sl.pop_back();
  check_lists(l, sl);
}

TEST(pop, for_front) {
  my::list<int> l({1, 2, 4, 5, 2, 1});
  std::list<int> sl({1, 2, 4, 5, 2, 1});
  for (size_t i = 0; i < l.size(); --i) {
    l.pop_front();
    sl.pop_front();
    check_lists(l, sl);
  }
}

TEST(pop, for_back) {
  my::list<int> l({1, 2, 4, 5, 2, 1});
  std::list<int> sl({1, 2, 4, 5, 2, 1});
  for (size_t i = 0; i < l.size(); --i) {
    l.pop_back();
    sl.pop_back();
    check_lists(l, sl);
  }
}

TEST(funcs, clear) {
  my::list<int> l({1, 5, 3, 5, 6, 2, 623, 31, 56});
  std::list<int> sl({1, 16, 12, 6, 123, 2, 6, 7});
  l.clear();
  sl.clear();
  ASSERT_EQ(l.size(), sl.size());
  ASSERT_EQ(l.empty(), sl.empty());
}

TEST(funcs, max_size) {
  std::list<int> sl;
  my::list<int> l;
  std::list<std::string> ssl;
  my::list<std::string> ll;
  ASSERT_EQ(sl.max_size(), l.max_size());
  ASSERT_EQ(ssl.max_size(), ll.max_size());
}

TEST(funcs, swap) {
  my::list<int> l({1, 5, 6, 3, 2, 6});
  my::list<int> l_swap({9, 7, 5, 4, 3, 3, 3, 2, 1, 2, 5});
  std::list<int> sl({1, 5, 6, 3, 2, 6});
  std::list<int> sl_swap({9, 7, 5, 4, 3, 3, 3, 2, 1, 2, 5});
  check_lists(l, sl);
  check_lists(l_swap, sl_swap);
  l.swap(l_swap);
  sl.swap(sl_swap);
  check_lists(l, sl);
  check_lists(l_swap, sl_swap);
}

TEST(funcs, swap_empty) {
  my::list<int> l;
  my::list<int> l_swap;
  std::list<int> ll;
  std::list<int> ll_swap;
  check_lists(l, ll);
  l.swap(l_swap);
  ll.swap(ll_swap);
  check_lists(l_swap, ll_swap);
  check_lists(l, ll);
}

TEST(funcs, merge) {
  my::list<int> l({1, 5, 7, 11, 55});
  my::list<int> l_merge({1, 7, 9, 22, 54, 55, 56});
  std::list<int> sl({1, 5, 7, 11, 55});
  std::list<int> sl_merge({1, 7, 9, 22, 54, 55, 56});
  l.merge(l_merge);
  sl.merge(sl_merge);
  auto i = l.begin();
  auto j = sl.begin();
  for (; i != l.end() && j != sl.end(); ++i, ++j) {
    ASSERT_EQ(*i, *j);
  }
  i = l_merge.begin();
  j = sl_merge.begin();
  for (; i != l_merge.end() && j != sl_merge.end(); ++i, ++j) {
    ASSERT_EQ(*i, *j);
  }
}

TEST(funcs, merge_empty) {
  my::list<int> l;
  my::list<int> ll({1, 2, 3, 4, 5});
  std::list<int> sl;
  std::list<int> ssl({1, 2, 3, 4, 5});
  l.merge(ll);
  sl.merge(ssl);
  auto i = l.begin();
  auto j = sl.begin();
  for (; i != l.end() && j != sl.end(); ++i, ++j) {
    ASSERT_EQ(*i, *j);
  }
  i = ll.begin();
  j = ssl.begin();
  for (; i != ll.end() && j != ssl.end(); ++i, ++j) {
    ASSERT_EQ(*i, *j);
  }
}

TEST(funcs, reverse) {
  my::list<int> l({1, 5, 7, 11, 55});
  std::list<int> sl({1, 5, 7, 11, 55});
  l.reverse();
  sl.reverse();
  check_lists(l, sl);
}

TEST(funcs, reverse_empty) {
  my::list<int> l;
  std::list<int> sl;
  l.reverse();
  sl.reverse();
  check_lists(l, sl);
}

TEST(funcs, unique) {
  my::list<int> l({1, 1, 2, 3, 2, 5, 5, 5, 5, 5, 5, 1, 3, 5, 5});
  std::list<int> sl({1, 1, 2, 3, 2, 5, 5, 5, 5, 5, 5, 1, 3, 5, 5});
  l.unique();
  sl.unique();
  check_lists(l, sl);
}

TEST(funcs, sort) {
  my::list<int> l({1, 6, 7, 42, 5, 6, 2, 5, 67, 7, 1, 2, 4, 2, 11});
  std::list<int> sl({1, 6, 7, 42, 5, 6, 2, 5, 67, 7, 1, 2, 4, 2, 11});
  l.sort();
  sl.sort();
  check_lists(l, sl);
}

TEST(funcs, sort_small) {
  my::list<int> l({2, 1});
  std::list<int> sl({2, 1});
  l.sort();
  sl.sort();
  check_lists(l, sl);
}

TEST(funcs, sort_empty) {
  my::list<int> l;
  std::list<int> sl;
  l.sort();
  sl.sort();
  check_lists(l, sl);
}

TEST(funcs, splice_empty) {
  my::list<int> l({});
  my::list<int> ll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  std::list<int> sl({});
  std::list<int> sll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  auto i = l.end();
  auto j = sl.end();
  l.splice(my::list<int>::const_iterator(i), ll);
  sl.splice(j, sll);
  check_lists(l, sl);
}

TEST(funcs, splice_end) {
  my::list<int> l({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  my::list<int> ll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  std::list<int> sl({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  std::list<int> sll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  auto i = l.end();
  auto j = sl.end();
  l.splice(my::list<int>::const_iterator(i), ll);
  sl.splice(j, sll);
  check_lists(l, sl);
}
TEST(funcs, splice_start) {
  my::list<int> l({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  my::list<int> ll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  std::list<int> sl({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  std::list<int> sll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  auto i = l.begin();
  auto j = sl.begin();
  l.splice(my::list<int>::const_iterator(i), ll);
  sl.splice(j, sll);
  check_lists(l, sl);
}

TEST(funcs, splice_middle) {
  my::list<int> l({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  my::list<int> ll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  std::list<int> sl({1, 6, 5, 3, 2, 7, 8, 2, 1, 1, 5, 6});
  std::list<int> sll({5, 6, 3, 1, 6, 78, 8, 2, 2, 1, 6, 7, 1});
  auto i = l.begin();
  auto j = sl.begin();
  ++i;
  ++j;
  ++i;
  ++j;
  l.splice(my::list<int>::const_iterator(i), ll);
  sl.splice(j, sll);
  check_lists(l, sl);
}

TEST(funcs, insert_start) {
  my::list<int> l({1, 2});
  std::list<int> sl({1, 2});
  auto i = l.begin();
  auto j = sl.begin();
  l.insert(i, 5);
  sl.insert(j, 5);
  check_lists(l, sl);
}

TEST(funcs, insert_middle) {
  my::list<int> l({1, 2, 3});
  std::list<int> sl({1, 2, 3});
  auto i = l.begin();
  auto j = sl.begin();
  ++i;
  ++j;
  l.insert(i, 5);
  sl.insert(j, 5);
  check_lists(l, sl);
}

TEST(funcs, insert_end) {
  my::list<int> l({1, 2, 3});
  std::list<int> sl({1, 2, 3});
  auto i = l.end();
  auto j = sl.end();
  l.insert(i, 5);
  sl.insert(j, 5);
  check_lists(l, sl);
}

TEST(funcs, insert_empty) {
  my::list<int> l;
  std::list<int> sl;
  auto i = l.begin();
  auto j = sl.begin();
  l.insert(i, 5);
  sl.insert(j, 5);
  check_lists(l, sl);
}

TEST(funcs, erase_start) {
  my::list<int> l({1, 2});
  std::list<int> sl({1, 2});
  auto i = l.begin();
  auto j = sl.begin();
  l.erase(i);
  sl.erase(j);
  check_lists(l, sl);
}

TEST(funcs, erase_middle) {
  my::list<int> l({1, 2, 3});
  std::list<int> sl({1, 2, 3});
  auto i = l.begin();
  auto j = sl.begin();
  ++i;
  ++j;
  l.erase(i);
  sl.erase(j);
  check_lists(l, sl);
}

TEST(funcs, emplace_normal_value) {
  my::list<int> l({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  std::list<int> sl({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  auto i = l.begin();
  auto j = sl.begin();
  ++(++(++(++i)));
  ++(++(++(++j)));
  l.emplace(my::list<int>::const_iterator(i), 1, -2, 3, 4, 5);
  for (auto k : {1, -2, 3, 4, 5}) sl.insert(j, k);
  check_lists(l, sl);
}

TEST(funcs, emplace_empty) {
  my::list<int> l({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  std::list<int> sl({1, 5, 6, 2, 3, 4, 5, 22, 11, 5});
  auto i = l.begin();
  auto j = sl.begin();
  ++(++(++(++i)));
  ++(++(++(++j)));
  l.emplace(my::list<int>::const_iterator(i));
  check_lists(l, sl);
}

TEST(funcs, emplace_empty_list) {
  my::list<int> l({});
  std::list<int> sl({});
  auto i = l.begin();
  auto j = sl.begin();
  l.emplace(my::list<int>::const_iterator(i), 1, 2, 3, 4, 5);
  for (auto k : {1, 2, 3, 4, 5}) sl.insert(j, k);
  check_lists(l, sl);
}

TEST(funcs, emplace_empty_all) {
  my::list<int> l({});
  std::list<int> sl({});
  auto i = l.begin();
  l.emplace(my::list<int>::const_iterator(i));
  check_lists(l, sl);
}

TEST(funcs, emplace_minus) {
  my::list<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::list<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  auto i = l.end();
  auto j = sl.end();
  --(--(--(--i)));
  --(--(--(--j)));
  l.emplace(my::list<int>::const_iterator(i), 1, 2, 33);
  for (auto k : {1, 2, 33}) sl.insert(j, k);
  check_lists(l, sl);
}

TEST(funcs, emplace_back_normal_value) {
  my::list<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::list<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_back(-1, 2, 33);

  auto j = sl.end();
  for (auto k : {-1, 2, 33}) sl.insert(j, k);

  check_lists(l, sl);
}

TEST(funcs, emplace_back_empty) {
  my::list<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::list<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_back();
  check_lists(l, sl);
}

TEST(funcs, emplace_back_empty_list) {
  my::list<int> l({});
  std::list<int> sl({});
  l.emplace_back(1, 2, 3, 4, 5);

  auto j = sl.end();
  for (auto k : {1, 2, 3, 4, 5}) sl.insert(j, k);

  check_lists(l, sl);
}

TEST(funcs, emplace_back_empty_all) {
  my::list<int> l({});
  std::list<int> sl({});
  l.emplace_back();

  check_lists(l, sl);
}

TEST(funcs, emplace_front_normal_value) {
  my::list<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::list<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_front(-1, 2, 33);

  auto j = sl.begin();
  for (auto k : {-1, 2, 33}) sl.insert(j, k);

  check_lists(l, sl);
}

TEST(funcs, emplace_front_empty) {
  my::list<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::list<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_front();
  check_lists(l, sl);
}

TEST(funcs, emplace_front_empty_list) {
  my::list<int> l({});
  std::list<int> sl({});
  l.emplace_front(1, 2, 3, 4, 5);

  auto j = sl.begin();
  for (auto k : {1, 2, 3, 4, 5}) sl.insert(j, k);

  check_lists(l, sl);
}

TEST(funcs, emplace_front_empty_all) {
  my::list<int> l({});
  std::list<int> sl({});
  l.emplace_front();

  check_lists(l, sl);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
